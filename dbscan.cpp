#include "dbscan.h"

void DBScan(int minpts,int e,int Line_num,int*** DistanceMatrix,std::vector<int> &ClassifyReslt)
{
    int Number = Line_num;
    if (!ClassifyReslt.empty())
        ClassifyReslt.erase(ClassifyReslt.begin(),ClassifyReslt.end());
    for (int index=0;index<Number;index++)
        ClassifyReslt.push_back(0);
    int cur_classify_no = 1;
    int cur_ptr = 0;
    for (cur_ptr = 0; cur_ptr<Number;cur_ptr++){
        if (ClassifyReslt[cur_ptr]==0){
            if (ExpandCluster(Number,DistanceMatrix,cur_ptr,cur_classify_no,ClassifyReslt,e,minpts))
                cur_classify_no++;       
        }
    }
}
std::queue<int> RegionQuery(int cur_ptr,int e,int Number,int*** DiMatrix)
{
    std::queue<int> Seeds;
    Seeds.push(cur_ptr);
   /* int **TempDisMatrix = new int*[Number];
    for (int i1=0; i1<Number;i1++){
        TempDisMatrix[i1] = new int[Number];
    }
    for (int j1=0;j1<Number;j1++){
        for (int k1=0;k1<Number;k1++){
            TempDisMatrix[j1][k1] = *((*(DiMatrix+j1))+k1);
        }
    }*/
    for (int i=0;i<Number;i++){
        if (i==cur_ptr)
            continue;
        if (i<cur_ptr){
            //std::cout<<(*(*(DiMatrix+i))+cur_ptr)<<std::endl;
            //if ( (*(*(DiMatrix+i))+cur_ptr)<=e )
            if (*(*((*DiMatrix)+i)+cur_ptr)<=e)
                Seeds.push(i);
        }
        else {
            //std::cout<<(*(*(DiMatrix+cur_ptr))+i)<<std::endl;
            if (*(*((*DiMatrix)+cur_ptr)+i)<=e)
                Seeds.push(i);
        }
    }
    /*
    for (int D1=0;D1<Number;D1++){
        delete [] TempDisMatrix[D1];
    }
    delete [] TempDisMatrix;*/
    return Seeds;
}
bool ExpandCluster(int Number,int*** DiMatrix, int cur_ptr, int cur_classify_no, 
std::vector<int> &ClassifyReslt,int e, int minpts){
    std::queue<int> seeds = RegionQuery(cur_ptr,e,Number,DiMatrix);
    if (seeds.size()<minpts){
        ClassifyReslt[cur_ptr]=-1;
        return false;
    }
    ClassifyReslt[cur_ptr]=cur_classify_no;
    seeds.pop();
    while (!seeds.empty()){
        int travesal_ptr = seeds.front();
        seeds.pop();
        ClassifyReslt[travesal_ptr] = cur_classify_no;
        std::queue<int> TempQueue = RegionQuery(travesal_ptr,e,Number,DiMatrix);
        if (TempQueue.size()>=minpts){
            TempQueue.pop();
            while (!TempQueue.empty()){
                int resultP = TempQueue.front();
                TempQueue.pop();
                if ((ClassifyReslt[resultP]==0) || (ClassifyReslt[resultP]==-1)){
                    if (ClassifyReslt[resultP]==0)
                        seeds.push(resultP);
                    ClassifyReslt[resultP] = cur_classify_no;
                }
            } 
        }
    }
    return true;
}