#include "editing_distance.h"
#include <codecvt>
#include <locale>
#include <string>
#include <vector>

int EditingDistance(const std::string str1,const std::string str2){
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> cvt;
    std::u16string s1 = cvt.from_bytes(str1);
    std::u16string s2 = cvt.from_bytes(str2);
    int len1,len2,cost,distance;
    len1 = s1.length();
    len2 = s2.length();
    int** Mat =new int*[len1+1];
    for (int i=0;i<len1+1;i++)
        Mat[i]=new int[len2+1];
    for (int i=0;i<len1+1;i++)
        Mat[i][0]=i;
    for (int j=1;j<len2+1;j++)
        Mat[0][j]=j;
    for (int i1=1;i1<len1+1;i1++){
        for (int j1=1;j1<len2+1;j1++){
            if (s1[i1-1]==s2[j1-1])
                cost=0;
            else
                cost=1;
            Mat[i1][j1] = std::min(std::min(Mat[i1][j1-1]+1,Mat[i1-1][j1]+1),Mat[i1-1][j1-1]+cost);
        }
    }
    distance = Mat[len1][len2];
    for (int i2=0;i2<len1+1;i2++){
        delete [] Mat[i2];
    }
    delete [] Mat;
    return distance;
};

int ** CreateDistanceMatrix(const std::vector<std::string> &Corpus){
    int Line_num = Corpus.size();
    int **DistanceMatrix = new int*[Line_num];
    for (int i=0;i<Line_num;i++){
        DistanceMatrix[i] = new int[Line_num];
    }
    for (int row=0;row<Line_num;row++)
        for (int col=0;col<Line_num;col++){
            if (col<=row)
                DistanceMatrix[row][col]=0;
            else
                DistanceMatrix[row][col]=EditingDistance(Corpus[row], Corpus[col]);
        }
    return DistanceMatrix;
};
void ClearSpace(int**Matrix,int number){
    for (int i = 0; i<number;i++){
        delete[] Matrix[i];
    }
    delete[] Matrix;
}