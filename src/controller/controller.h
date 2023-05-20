#ifndef CPP4_3DVIEWER_V2_0_CONTROLLER_CONTROLLER_H_
#define CPP4_3DVIEWER_V2_0_CONTROLLER_CONTROLLER_H_

#include "../model/model.h"

class Controller 
{
public:
    Controller() : model(&Model::getInstance()) {}

    void setFileName(std::string fileName);
    int getError();
    std::vector<int> getVertexIndex();
    std::vector<double> getVertexCoord();
    void transform(int&& strategyType, double value, int&& axis = 0);
private:
    Model* model;
};

#endif  // CPP4_3DVIEWER_V2_0_CONTROLLER_CONTROLLER_H_
