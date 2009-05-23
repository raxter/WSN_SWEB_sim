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

DiscreteSimulator::DiscreteSimulator(SensorNetwork * sensorNetwork) : sensorNetwork(sensorNetwork), _currentTime(0),running(false) {


  nodes = QVector<Node::DiscreteSim *>::fromStdVector (sensorNetwork->getSimNodePointers()); /* FIXME, still deciding whether this should be a class variable or not*/ 
  
  Q_FOREACH (Node::BaseNode * node, nodes) {
  
    idToNode[node->id] = node;
    
    sectorIdToNodeList[sensorNetwork->getSlice(node->x(), node->y())].append(node);
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
  emit logEvent(QString("incrementTimeStep()"));

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
      if (bp->type == PacketTypes::Init) {
        const Packet::Init * initPacket = dynamic_cast<const Packet::Init*>(bp);
        emit logEvent(QString("InitPacket send from from node %1 to sector %2").arg(bp->srcId).arg(initPacket->dstSectorId));
        //qDebug() << QString("InitPacket send from from node %1 to sector %2").arg(bp->srcId).arg(initPacket->dstSectorId);
        
        Q_FOREACH(Node::BaseNode * node, sectorIdToNodeList[initPacket->dstSectorId])
          signalList.append(Signal(idToNode[bp->srcId], idToNode[node->id], physicsLayer->bitsOfPacketSent, (physicsLayer->packetSendingFinished?bp:0)));
      }
      if (bp->type == PacketTypes::EnergyReq) {
        const Packet::EnergyReq * energyReqPacket = dynamic_cast<const Packet::EnergyReq*>(bp);
        emit logEvent(QString("EnergyReq send from from node %1 to group %2").arg(bp->srcId).arg(bp->dstGrpId));
        
        
      }
    }
  }
  
  Q_FOREACH (const Signal & signal, signalList) {
    
    Node::PhysicalLayer * physicsLayer = dynamic_cast<Node::PhysicalLayer*>(idToNode[signal.dst->id]);
    Node::DiscreteSim * discreteSim = dynamic_cast<Node::DiscreteSim*>(idToNode[signal.dst->id]);
    physicsLayer->receivingState = Node::PhysicalLayer::Receiving;
    discreteSim->receivedPacketStrength = SensorNetwork::dist(signal.dst->x(), signal.dst->y(), signal.src->x(), signal.src->y());
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
    
  _currentTime++;
  
  control.unlock();
  emit finishedTimeStep ();

}


/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/

const QVector<Signal>& DiscreteSimulator::getSignalList() const {
  return signalList;

}


void DiscreteSimulator::lock()  { control.lock();   }
void DiscreteSimulator::unlock(){ control.unlock(); }

/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/

void DiscreteSimulator::requestStopRunning() {
  running = false;
}

/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/

void DiscreteSimulator::run() {

  control.lock();
  speed = 10; /* ms/s */
  stepsToRun = 10; /* ms */
  running = true;
  while(running) {
  
    control.unlock();
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













