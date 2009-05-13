#include "sensor_network.h"

SensorNetwork::SensorNetwork()
{
    noNodes=100;
    createNodes(100,100);
    init();
}

SensorNetwork::SensorNetwork(int xRangeIn, int yRangeIn, int noNodesIn)
{

    noNodes = noNodesIn;
    createNodes(xRangeIn,yRangeIn);

    init();
    //cout<<"pac from node 97 is in cluster: "<<nodes[97].getCluster()<<endl;
    route();

}

void SensorNetwork::route()
{
    Node * curNode = &nodes[97];
    while (curNode != &BS)
    {

    curNode = nextHop(curNode);
    cout<<"pac from node 97 is in cluster: "<<curNode->getCluster()<<endl;
    }

}
int SensorNetwork::determineCluster(Node * in)
{
        int x = in->x;
        int y = in->y;

        double dist = getDistFromBS(in);
        int degreesOutward = (int)dist/(int)threshDegree;

        int relSlice = getSlice(x , y);

        int output = degreesOutward*360/scanAngle + relSlice;

        ///global degreesOutputMax used as a reference later as to how far the web goes
        if (clusterMax < output)
            clusterMax = output;
        ///
        return degreesOutward*360/scanAngle + relSlice;
}

int SensorNetwork::getSlice(int x , int y)
{

  double angle=0 ;
        if  (x*y > 0)
        {
            angle = atan((abs(y)+0.0)/(abs(x)+0.0));
            if (y<0)
                angle = angle + pi;
        }
        else if (x*y < 0)
        {
            angle = atan((y+0.0)/(-x+0.0));
            if (y>0)
                angle = pi - angle;
            else
                angle = 2*pi - angle;
        }
        else if (x==0)
            if (y>0)
                angle = pi/2;
            else if (y < 0)
                angle = 3*pi/2;
            else angle = -1;
        else
        {
            if (x>0)
                angle = 0;
            else if (x < 0)
                angle = -1*pi;
            else angle = -1;
        }
        angle = angle *180/pi;

        int relivantSlice = 0;
        while (angle >= scanAngle)
        {
            relivantSlice++;
            angle -= scanAngle;

        }

        return relivantSlice;

}

Node * SensorNetwork::nextHop (Node * source)
{
        if (source == &BS)
            return source;
        else if (source->isHead()) ///route to next cluster head
        {
            ///Get the next nearest head node: contenders are [0][0], [0][1] and [0][2] if they exist

            int nextClusterNo = source->getRT(0)[1];//ur here




            if (nextClusterNo == -1)
                return &BS;
            else return clusterHead[nextClusterNo];

        }
        else ///route to head node of cluster
        {
            return clusterHead[source->getCluster()];
        }
}


SensorNetwork::~SensorNetwork()
{

}


std::vector <const Node *> SensorNetwork::getNodePointers() const
{
  std::vector <const Node *> out;
  for (int a = 0 ; a < noNodes ; a++)
    out.push_back(&nodes[a]);
  return out;
}

void SensorNetwork::init()
{
        BS = Node(0,0);
        scanAngle = 45;//*PI/180;
        threshDegree=25;
        clusterMax=0;

        ///determine all nodes clusters
        for (int a = 0 ; a < noNodes ; a++)
        {
            nodes[a].cluster = determineCluster(&nodes[a]);
            cout<<"node: "<<a<<" x: "<<nodes[a].x<<" y: "<<nodes[a].y<<" cluster "<<nodes[a].cluster<<endl;

        }

        ///set initial cluster heads
        for (int b = 0 ; b <= clusterMax ; b++)
        {
            vector <Node*> cluster = getCluster(b);
            cout <<"\nsize: "<< cluster.size()<< endl;

            int lowestRemEnergy = MAX_NODE_ENGERGY+1;
            Node * newHead = NULL;
            for (int c = 0 ; c < cluster.size(); c++)
            {
                cout << "there are actual nodes in this cluster: "<< " current node in cluster: "<<cluster[c]->cluster<<endl;
                if (cluster[c]->energyRemaining < lowestRemEnergy)
                {
                        lowestRemEnergy = cluster[c]->energyRemaining;
                        newHead = cluster[c];
                        cluster[c]->setHead(true);
                }
            }
            clusterHead.push_back(newHead);
            cout<<"cluster "<<b<<" headnode "<<newHead;

        }
        for (int hnC = 0 ; hnC < clusterHead.size() ; hnC++)
            cout<<"clust no: "<<hnC<<" CH: "<<getCluster(hnC).size()<<" - "<<clusterHead[hnC]<<endl;

        ///since head nodes have been determined
        ///create routing tables
        for (int c = 0 ; c < noNodes ; c++)
        {
            double dist = getDistFromBS(&nodes[c]);
            int degreesOutward = (int)dist/(int)threshDegree;

            int noClustersInASector = 360/scanAngle;

            int relCluster = nodes[c].getCluster();
            ///[2][2]:
            int c22 = (relCluster+1)%noClustersInASector + (degreesOutward+1)*noClustersInASector;
            ///[2][1]:
            int c21 = relCluster+noClustersInASector;
            ///[2][0]:
            int c20 = (relCluster-1)%noClustersInASector + (degreesOutward+1)*noClustersInASector;

            ///[1][2]:
            int c12 = (relCluster +1)%noClustersInASector + degreesOutward*noClustersInASector;
            ///[1][0]:
            int c10 = (relCluster -1)%noClustersInASector + degreesOutward*noClustersInASector;

            ///[0][*]
            int c02,c01,c00 = 0;
            if (relCluster < noClustersInASector)
            {
                ///[0][2]:
                c02 = -1;///-1 = base station
                ///[0][1]:
                c01 = -1;///-1 = base station
                ///[0][0]:
                c00 = -1;///-1 = base station
            }
            else
            {
                ///[0][2]:
                c02 = (relCluster+1)%noClustersInASector + (degreesOutward-1)*noClustersInASector;
                 ///[2][1]:
                c01 = relCluster-noClustersInASector;
                ///[2][0]:
                c00 = (relCluster-1)%noClustersInASector + (degreesOutward-1)*noClustersInASector;
            }

            nodes[c].setRT(c22,c21,c20,c12,c10,c02,c01,c00) ;
            cout<<c<<endl;
            nodes[c].printTable();
            cout<<endl;

        }

}


vector <Node *> SensorNetwork::getCluster(int clustNo)
{
        vector <Node *> out;
        for (int a = 0 ; a < noNodes ; a++)
        {
                if (nodes[a].cluster == clustNo)
                    out.push_back(&nodes[a]);
        }
        return out;
}

void SensorNetwork::createNodes(int x , int y)
{
    cout<<"start of createNodes "<<noNodes<<endl;
    for (int a = 0 ; a < noNodes ; a++)
    {

        int randx = x/2 - rand()%(x+1);
        int randy = y/2 - rand()%(y+1);
        nodes.push_back( Node(randx,randy));

    }
    cout<<"end of createNodes "<<noNodes<<endl;
}

double SensorNetwork::dist(int x1, int y1, int x2, int y2)
{

        return sqrt(pow(x2-x1,2) + pow(y2-y1,2) );
}

double SensorNetwork::getDistFromBS(Node * which)
{

        return dist(which->x,which->y,BS.x,BS.y);
}

int getCluster(int sector, int slice)
{
        return sector*8+slice;
}



