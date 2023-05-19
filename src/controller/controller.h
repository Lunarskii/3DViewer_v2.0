#include "../model/model.h"

class Controller 
{
public:
    Controller(Model* m) : model(m) {}

    void setFileName(std::string fileName);
    int getError();
    std::vector<int> getVertexIndex();
    std::vector<double> getVertexCoord();
    void transform(int&& strategyType, double value, int&& axis = 0);
private:
    Model* model;
};
