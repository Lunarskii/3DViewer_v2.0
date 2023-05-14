#include "controller.h"

void Controller::setFileName(std::string fileName)
{
    model->setFileName(fileName);
    model->parser();
}

int Controller::getError()
{
    return model->getError();
}

long Controller::getCountVertex()
{
    return model->getCountVertex();
}

long Controller::getCountIndex()
{
    return model->getCountIndex();
}

std::vector<int> Controller::getVertexIndex()
{
    return model->getVertexIndex();
}

std::vector<double> Controller::getVertexCoord()
{
    return model->getVertexCoord();
}