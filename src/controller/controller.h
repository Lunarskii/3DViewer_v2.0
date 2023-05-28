#ifndef CPP4_3DVIEWER_V2_0_CONTROLLER_CONTROLLER_H_
#define CPP4_3DVIEWER_V2_0_CONTROLLER_CONTROLLER_H_

#include <QObject>
#include <QString>
#include "../model/model.h"
#include "../view/view.h"

class Controller : public QObject
{
    Q_OBJECT

signals:
    void solutionReady(std::vector<int>* vertexIndex, std::vector<double>* vertexCoord);

public slots:
    void setFileName(QString fileName);
    void transform(int strategyType, double value, int axis = X);

public:
    Controller(View* newView) 
        : model(&Model::getInstance())
        , view(newView)
    {
        QObject::connect(view, SIGNAL(setModel(QString)), this, SLOT(setFileName(QString)));
        QObject::connect(view->facade, SIGNAL(setTransform(int, double, int)), this, SLOT(transform(int, double, int)));
    }

    int getError();
    std::vector<int>& getVertexIndex();
    std::vector<double>& getVertexCoord();
    
private:
    Model* model;
    View* view;
};

#endif  // CPP4_3DVIEWER_V2_0_CONTROLLER_CONTROLLER_H_
