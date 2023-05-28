#include "controller.h"

void Controller::setFileName(QString fileName)
{
    model->setFileName(fileName.toStdString());
    model->parser();

    if (getError() == 0)
    {
        emit solutionReady(&getVertexIndex(), &getVertexCoord());
    }
    else
    {
        // отправка ошибки
    }
}

int Controller::getError()
{
    return model->getError();
}

std::vector<int>& Controller::getVertexIndex()
{
    return model->getVertexIndex();
}

std::vector<double>& Controller::getVertexCoord()
{
    return model->getVertexCoord();
}

void Controller::transform(int strategyType, double value, int axis)
{
    transformation_t tempAxis = static_cast<transformation_t>(axis);
    model->transform(strategyType, value, tempAxis);
}