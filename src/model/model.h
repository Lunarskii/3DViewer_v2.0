#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include <QString>

#include "tranformation.h"

#define FILE_HAS_WRONG_EXTENSION 1
#define FAILED_TO_OPEN_FILE 2
#define INCORRECT_ENTRY_OF_THE_VERTEX_COORDINATE 3

class Model 
{
public:
    Model() = default;
    Model(std::string fileName);
    void parser();
    void vertexParser(std::string line);
    void edgesParser(std::string line);

    void setFileName(std::string fileName);
    int getError();
    std::vector<int> getVertexIndex();
    std::vector<double> getVertexCoord();
    void transform(int& strategyType, double& value, int& axis);
    
    static Model& getInstance();
private:
    std::string fileName;
    std::vector<double> vertexCoord{};
    std::vector<int> vertexIndex{};
    int errorCode{};
    Strategy transformationModel;
};
