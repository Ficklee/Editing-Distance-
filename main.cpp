
#include <iostream>
#include <sstream>
#include <locale>
#include <fstream>
#include <codecvt>
#include <cstdio>
#include <string>
using namespace std;

int ReadInSentence(u16string **Storage,const string WriteInFile){
    ifstream instream(WriteInFile);
    std::string c;
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> cvt;
    int LineNum = 0;
    if (instream.bad()){
        cout<<"Read In File Error!"<<endl;
        exit(1);
    }
    while(getline(instream,c)){
        LineNum++;
    }
    if(!instream.eof()){
        cout<<"Error! Read in sentences failed!"<<endl;
        exit(1);
    }
    instream.clear();
    instream.seekg(0,ios::beg);
    *Storage = new u16string[LineNum];
    for (int i=0;i<LineNum;i++){
        //Storage[i] = new u16string;
        if (!getline(instream,c)){
            cout<<"Temporary Storage Failed"<<endl;
            exit(0);
        }
        (*Storage)[i] =cvt.from_bytes(c);
    }
    if (!instream.eof()){
        cout<<"Warning:Did not approach the end of the original file!"<<endl;
    }
    instream.close();
    return LineNum;
}

int EditingDistance(const u16string s1,const u16string s2){
    int len1,len2,cost,distance;
    len1 = s1.length();
    len2 = s2.length();
    int** Mat =new int*[len1+1];
    for (int i=0;i<len1+1;i++)
        Mat[i]=new int[len2+1]{0};
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
            Mat[i1][j1] = min(min(Mat[i1][j1-1]+1,Mat[i1-1][j1]+1),Mat[i1-1][j1-1]+cost);
        }
    }
    distance = Mat[len1][len2];
    for (int i2=0;i2<len1+1;i2++){
        delete [] Mat[i2];
    }
    delete [] Mat;
    return distance;
}


int main() {
    //std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> cvt;
    //int argc, const char * argv[];
    std::string corpusFile="./test.txt";
    int Line_num;
    u16string* CorpusStorage;
    int** DistanceMatrix;
    Line_num = ReadInSentence(&CorpusStorage, corpusFile);
    DistanceMatrix = new int*[Line_num];
    for (int i=0;i<Line_num;i++)
        DistanceMatrix[i] = new int[Line_num];
    //cout<<CorpusStorage[1].length()<<endl;
    for (int row=0;row<Line_num;row++)
        for (int col=0;col<Line_num;col++){
            if (col<=row)
                DistanceMatrix[row][col]=0;
            else
                DistanceMatrix[row][col]=EditingDistance(CorpusStorage[row], CorpusStorage[col]);
        }
    //cout<<DistanceMatrix[0][1]<<endl;
    ofstream Out("./DistanceMatrix.txt");
    for (int w1=0;w1<Line_num;w1++){
        for (int y1=0;y1<Line_num;y1++){
            Out<<DistanceMatrix[w1][y1];
            if (y1!=Line_num-1)
                Out<<"\t";
        }
        Out<<"\n";
    }
    Out.close();
    for (int l1=0;l1<Line_num;l1++){
        delete[] DistanceMatrix[l1];
    }
    delete[] DistanceMatrix;
    delete[] CorpusStorage;
    
    return 0;
}
