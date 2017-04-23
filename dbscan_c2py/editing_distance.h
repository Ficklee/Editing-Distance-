#ifndef E_DISTANCE_H
#define E_DISTANCE_H

#include <string>
#include <vector>
int EditingDistance(const std::string str1,const std::string str2);
int ** CreateDistanceMatrix(const std::vector<std::string> &Corpus);
void ClearSpace(int**Matrix,int number);
#endif 