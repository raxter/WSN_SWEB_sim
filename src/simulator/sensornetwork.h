#ifndef SENSORNETWORK.H
#define SENSORNETWORK.H
#include "node.h"
#include "constants.h"

#include <vector>
#include <cstdlib>
#include <cmath>
#include <iostream>

using namespace std;


class SensorNetwork {

public:
    ///Constructors & Destructors
    SensorNetwork();
    SensorNetwork(int xRangeIn, int yRangeIn, int noNodesIn);
    ~SensorNetwork();


    ///mem alloaction
    vector <Node*> clusterHead;
    vector <Node> nodes ;

    ///attributes
    Node BS;
    double scanAngle;
    int threshDegree;
    int noNodes;
    int clusterMax;

    ///functions

    Node* nextHop(Node * source);
    vector <Node *> getCluster(int clustNo);

private:
    void init();
    void createNodes(int x,int y);
    int getClusterNo (int sector, int slice);
    int * getClusterCoor(int cluNo);
    int getSlice(int x , int y);
    double dist(int x1, int y1, int x2, int y2);
    double getDistFromBS(Node * which);
    int determineCluster(Node * in);


    ///temp
    void route();
};

#endif

