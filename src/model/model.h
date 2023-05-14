#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

#define FILE_HAS_WRONG_EXTENSION 1
#define FAILED_TO_OPEN_FILE 2

class Model 
{
public:
    Model() = default;
    Model(std::string fileName);
    void parser();
    void vertexParser(std::string line);
    void edgesParser(std::string line);
    int isNum(char c);

    void setFileName(std::string fileName);
    int getError();
    long getCountVertex();
    long getCountIndex();
    std::vector<int> getVertexIndex();
    std::vector<double> getVertexCoord();
private:
    std::string fileName;
    std::vector<double> vertexCoord;
    std::vector<int> vertexIndex;
    long countIndex{};
    long countVertex{};
    int errorCode{};
};
