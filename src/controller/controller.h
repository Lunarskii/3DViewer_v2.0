#include "../model/model.h"

class Controller 
{
public:
    Controller(Model* m) : model(m) {}

    void setFileName(std::string fileName);
    int getError();
    long getCountVertex();
    long getCountIndex();
    std::vector<int> getVertexIndex();
    std::vector<double> getVertexCoord();
private:
    Model* model;
};
