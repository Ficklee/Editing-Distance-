#ifndef DBSCAN_H
#define DBSCAN_H

#include <vector>
#include <queue>
#include <iostream>

void DBScan(int minpts,int e,int Line_num,int*** DistanceMatrix,std::vector<int> &ClassifyReslt);
std::queue<int> RegionQuery(int cur_ptr,int e,int Number,int ***DiMatrix);
bool ExpandCluster(int Number,int*** DiMatrix, int cur_ptr, int cur_classify_no, 
std::vector<int> &ClassifyReslt,int e, int minpts);

#endif /*DBSCAN header*/