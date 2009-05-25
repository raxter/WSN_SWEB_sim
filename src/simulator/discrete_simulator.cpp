#include "discrete_simulator.h"

 
#include <QDebug>

namespace WSN
{

namespace Simulator
{

/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/

DiscreteSimulator::DiscreteSimulator(SensorNetwork * sensorNetwork) : sensorNetwork(sensorNetwork), _currentTime(0),running(false), doSimulation(false) {


  nodes = QVector<Node::DiscreteSim *>::fromStdVector (sensorNetwork->getSimNodePointers()); /* FIXME, still deciding whether this should be a class variable or not*/ 
  
  Q_FOREACH (Node::BaseNode * node, nodes) {
  
    //if (dynamic_cast<Node::DiscreteSim*>(node)->type == Node::DiscreteSim::BaseStation)
      //continue;
    idToNode[node->id] = node;
    
    int sectorId = sensorNetwork->getSlice(node->x(), node->y());
    sectorIdToNodeList[sectorId].append(node);
    
    
    groupIdToNodeList[Node::SensorLayers::Network::calcGroupId(Node::SensorLayers::Network::calcThresh(sensorNetwork->getThreshDegree(), sensorNetwork->dist(node->x(), node->y(), 0,0)), sectorId, sensorNetwork->numberOfSectors)].append(node);
  }
}

/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/

DiscreteSimulator::~DiscreteSimulator() {


}

/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/

unsigned long DiscreteSimulator::currentTime() {
  return _currentTime;
}


/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/

void DiscreteSimulator::incrementTimeStep() {

  control.lock();
  //emit logEvent(QString("incrementTimeStep()"));

  // assuming that the next state will remain unchanged
  //for (int i = 0 ; i < nodes.size() ; i++)
  //  nodes[i]->nextState = nodes[i]->state;
    
  // simulating node hardware
  
  
    
  //case 0: setUpPhase();                 break;
  for (int n = 0 ; n < nodes.size() ; n++)
    nodes[n]->doNextPhaseOfTimeStep();
    
    
  signalList.clear();
  //case 1: physicalLayerSendLogic();     break;
  for (int n = 0 ; n < nodes.size() ; n++) {
    nodes[n]->doNextPhaseOfTimeStep();
    
    Node::PhysicalLayer * physicsLayer = dynamic_cast<Node::PhysicalLayer*>(nodes[n]);
    const BasePacket* bp = physicsLayer->getCurrentSendingPacket();
    if (bp) {
      //const Packet::EnergyReq * energyReqPacket = dynamic_cast<const Packet::EnergyReq*>(bp);
      
      if (bp->dstId != -1) { // single send
      
        emit logEvent(QString("Single send type %1 from node %2 to node %3").arg(bp->type).arg(bp->srcId).arg(bp->dstId));
        //if (bp->srcId != bp->dstId)
          signalList.append(Signal(idToNode[bp->srcId], idToNode[bp->dstId], physicsLayer->bitsOfPacketSent, (physicsLayer->packetSendingFinished?bp:0), bp->type));
      
      }
      else if (bp->dstGrpId != -1) { //group send
        emit logEvent(QString("Group send type %1 from node %2 to group %3").arg(bp->type).arg(bp->srcId).arg(bp->dstGrpId));
        
        //std::vector<int>&  groupNodeIds = dynamic_cast<Node::SensorLayers::Network*>(idToNode[bp->srcId])->groupNodeIds;
        Q_FOREACH(Node::BaseNode * node, groupIdToNodeList[bp->dstGrpId]) {
          if (bp->srcId != node->id)
            signalList.append(Signal(idToNode[bp->srcId], idToNode[node->id], physicsLayer->bitsOfPacketSent, (physicsLayer->packetSendingFinished?bp:0), bp->type));
        }
      }
      else { // other type of send
        if (bp->type == PacketTypes::Init) { // sector send
          const Packet::Init * initPacket = dynamic_cast<const Packet::Init*>(bp);
          emit logEvent(QString("InitPacket send from node %1 to sector %2").arg(bp->srcId).arg(initPacket->dstSectorId));
          //qDebug() << QString("InitPacket send from from node %1 to sector %2").arg(bp->srcId).arg(initPacket->dstSectorId);
          
          Q_FOREACH(Node::BaseNode * node, sectorIdToNodeList[initPacket->dstSectorId]) {
            signalList.append(Signal(idToNode[bp->srcId], idToNode[node->id], physicsLayer->bitsOfPacketSent, (physicsLayer->packetSendingFinished?bp:0), bp->type));
            
            //emit logEvent(QString("signal send from from node %1 to node %2").arg(bp->srcId).arg(node->id));
          }
        }
        else if (bp->type == PacketTypes::HeadReAlloc) {  // send to surrounding groups
          const Packet::HeadReAlloc * reallocPacket = dynamic_cast<const Packet::HeadReAlloc*>(bp);
          emit logEvent(QString("HeadReAlloc send from node %1 its group's (grp %2) surrounding groups").arg(bp->srcId).arg(reallocPacket->srcGrpId));
          
          QVector<int> groups;
          groups.append(reallocPacket->srcGrpId);
          groups.append(reallocPacket->srcGrpId + 1);
          groups.append(reallocPacket->srcGrpId - 1);
          groups.append(reallocPacket->srcGrpId + sensorNetwork->numberOfSectors);
          groups.append(reallocPacket->srcGrpId + sensorNetwork->numberOfSectors + 1);
          groups.append(reallocPacket->srcGrpId + sensorNetwork->numberOfSectors - 1);
          groups.append(reallocPacket->srcGrpId - sensorNetwork->numberOfSectors);
          groups.append(reallocPacket->srcGrpId - sensorNetwork->numberOfSectors + 1);
          groups.append(reallocPacket->srcGrpId - sensorNetwork->numberOfSectors - 1);
          
          Q_FOREACH(int groupId, groups) {
            Q_FOREACH(Node::BaseNode * node, groupIdToNodeList[groupId]) {
            
                
              if (bp->srcId != node->id)
                signalList.append(Signal(idToNode[bp->srcId], idToNode[node->id], physicsLayer->bitsOfPacketSent, (physicsLayer->packetSendingFinished?bp:0), bp->type));
            }
          }
        }
      }
    }
  }
  //qDebug() << endl;
  Q_FOREACH (const Signal & signal, signalList) {
    
    Node::PhysicalLayer * physicsLayer = dynamic_cast<Node::PhysicalLayer*>(idToNode[signal.dst->id]);
    Node::DiscreteSim * discreteSim = dynamic_cast<Node::DiscreteSim*>(idToNode[signal.dst->id]);
    physicsLayer->receivingState = Node::PhysicalLayer::Receiving;
   
    discreteSim->receivedPacketDistance = SensorNetwork::dist(signal.dst->x(), signal.dst->y(), signal.src->x(), signal.src->y());
    
    /*if (signal.dst->id == 1)
      qDebug() << "signal sent to 1";
    if (signal.src->id == 14)
      qDebug() << "signal sent from 14";*/
    if (signal.finishedPacket) {
      discreteSim->receivedPacket = signal.finishedPacket;
    }
  }
    
  //case 2: physicalLayerReceiveLogic();  break;
  for (int n = 0 ; n < nodes.size() ; n++)
    nodes[n]->doNextPhaseOfTimeStep();
  
  //case 3: linkLayerLogic();             break;
  for (int n = 0 ; n < nodes.size() ; n++)
    nodes[n]->doNextPhaseOfTimeStep();
    
  //case 4: networkLayerLogic();          break;
  for (int n = 0 ; n < nodes.size() ; n++)
    nodes[n]->doNextPhaseOfTimeStep();
    
  //case 5: wrapUpPhase();                break;
  for (int n = 0 ; n < nodes.size() ; n++)
    nodes[n]->doNextPhaseOfTimeStep();
    
  
  
  QSet<const BasePacket*> toDelete;
  Q_FOREACH (const Signal & signal, signalList) {
    if (signal.finishedPacket) {
      toDelete.insert(signal.finishedPacket);
    }
  }
  
  Q_FOREACH (const BasePacket* packet, toDelete) {
    delete packet;
  }
    
  _currentTime++;
  
  control.unlock();
  //qDebug() << "about to emit finishedTimeStep";
  emit finishedTimeStep (signalList);
  //qDebug() << "emited finishedTimeStep";

}


/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/

//const QVector<Signal>& DiscreteSimulator::getSignalList() const {
//  return signalList;

//}


//void DiscreteSimulator::lock()  { control.lock();   }
//void DiscreteSimulator::unlock(){ control.unlock(); }

/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/

void DiscreteSimulator::requestStopRunning() {
  running = false;
}


void DiscreteSimulator::setSpeed( int sp) {
  control.lock();
  //doLimitedSimulation = true;
  speed = sp;
  control.unlock();
}

void DiscreteSimulator::limitedTimeSimulation( int ms) {
  control.lock();
  //doLimitedSimulation = true;
  stepsToRun = ms;
  control.unlock();
}

void DiscreteSimulator::startSimulation() {
  control.lock();
  doSimulation = true;
  control.unlock();
}

void DiscreteSimulator::stopSimulation(){
  control.lock();
  doSimulation = false;
  control.unlock();
}

/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/

void DiscreteSimulator::run() {

  control.lock();
  speed = 5; /* ms/s */
  stepsToRun = 4040; /* ms */
  running = true;
  while(running) {
  
    control.unlock();
    
    if (doSimulation || (doLimitedSimulation && stepsToRun > 0)) {
    
      incrementTimeStep();
      
      if((_currentTime-40)%stepsToRun == 0) {
      
        //msleep(10);
        emit clearSignals();
        //doSimulation = false;
      }
      
      if((_currentTime-40)%40 == 0) {
        emit tick();
      }
      msleep(speed);
      emit timeUpdated(_currentTime);
        
      //qDebug() << _currentTime;
      
      /*if (stepsToRun > 0)
        stepsToRun --;
      else
        doLimitedSimulation = false;*/
    }
    //control.lock();
  
    
    /*if (stepsToRun > 0) {
      sleep(1);
      incrementTimeStep();
      stepsToRun--;
    }*/
    
    
    control.lock();
  }
  control.unlock();

}


} /* end of namespace Simulator */


} /* end of namespace WSN */













