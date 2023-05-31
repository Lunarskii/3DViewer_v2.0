#ifndef CPP4_3DVIEWER_V2_0_MODEL_MODEL_H_
#define CPP4_3DVIEWER_V2_0_MODEL_MODEL_H_

#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include <bits/stdc++.h>

#include "tranformation.h"

#define FILE_HAS_WRONG_EXTENSION 1
#define FAILED_TO_OPEN_FILE 2
#define INCORRECT_ENTRY_OF_THE_VERTEX_COORDINATE 3

class Model 
{
public:
    void parser();
    void vertexParser(std::string line);
    void edgesParser(std::string line);

    void setFileName(std::string fileName);
    int getError();
    std::vector<int>& getVertexIndex();
    std::vector<double>& getVertexCoord();
    void transform(int& strategyType, double& value, transformation_t& axis);
    
    static Model& getInstance();
private:
    Model() = default;

    std::string fileName;
    std::vector<double> vertexCoord{};
    std::vector<int> vertexIndex{};
    int errorCode{};
    Strategy transformationModel;
};

#endif  // CPP4_3DVIEWER_V2_0_MODEL_MODEL_H_
