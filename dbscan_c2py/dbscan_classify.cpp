#include "dbscan_classify.h"
#include "editing_distance.h"
#include "dbscan.h"
#include <vector>
#include <string>
std::vector<int> dbscan_classify(std::vector<std::string> CorpusNew){
    int Linenum = CorpusNew.size();
    std::vector<int> classify_result;
    int minpts = 2;
    int e = 3;
    int ** DistanceMatrix = CreateDistanceMatrix(CorpusNew);
    DBScan(minpts, e, Linenum, DistanceMatrix,classify_result);
    ClearSpace(DistanceMatrix,Linenum);
    return classify_result;
}