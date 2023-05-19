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

std::vector<int> Controller::getVertexIndex()
{
    return model->getVertexIndex();
}

std::vector<double> Controller::getVertexCoord()
{
    return model->getVertexCoord();
}

void Controller::transform(int&& strategyType, double value, int&& axis)
{
    model->transform(strategyType, value, axis);
}