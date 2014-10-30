#include <string>
#include <vector>
#include <stdlib.h>
#include <ctype.h>
#include <iostream>
#include <fstream>
#include <algorithm>


using namespace std;
struct CompressTestCase
{
    std::string dataId;
    double scale;
    int chunkSize;
    std::vector<double> data;
    std::string expectedResult;
};


static istream& ReadTestCase(istream&is, CompressTestCase& c)
{
    // Format:
    // DataID
    // Scale
    // ChunkSize
    // [sample1, sample2, ..., samplen]
    // Expected Result
     is >> c.dataId >> c.scale >> c.chunkSize;
    
    char tmp;
    is >> tmp; // read '['
    
    double d;
    c.data.clear();
    while (is >> d)
    {
        c.data.push_back(d);
        char comma;
        is >> comma;
    } 

    is.clear();

    is >> c.expectedResult;
    
    cout << c.dataId << " " << c.scale << " " << c.chunkSize << c.expectedResult << endl;

    for (int i = 0; i < c.data.size(); ++i)
        cout << c.data[i] << " ";
    return is;
}


static vector<CompressTestCase> LoadTestData()
{
    vector<CompressTestCase> vc;

    ifstream infile("CompressSampleData.txt");
    
    CompressTestCase c;

    while (ReadTestCase(infile, c))
        vc.push_back(c);

    return vc;
}



int main()
{
    vector<CompressTestCase> vc = LoadTestData();

    cout << "size is " << vc.size() << endl;
}
