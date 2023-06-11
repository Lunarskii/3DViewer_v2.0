#ifndef CPP4_3DVIEWER_V2_0_CONTROLLER_CONTROLLER_H_
#define CPP4_3DVIEWER_V2_0_CONTROLLER_CONTROLLER_H_

#include <QObject>
#include <QString>

#include "../model/model.h"
#include "../view/view.h"

class Controller : public QObject {
  Q_OBJECT

 signals:
  void SolutionReady(std::vector<int>* vertexIndex,
                     std::vector<double>* vertexCoord);

 public slots:
  void SetFileName(const QString& fileName);
  void Transform(int strategyType, double value, int axis = kX);

 public:
  explicit Controller(View* newView)
      : model_(&Model::GetInstance()), view_(newView) {
    QObject::connect(view_, SIGNAL(SetModel(QString)), this,
                     SLOT(SetFileName(QString)));
    QObject::connect(view_->facade, SIGNAL(SetTransform(int, double, int)),
                     this, SLOT(Transform(int, double, int)));
  }

  int GetError();
  std::vector<int>& GetVertexIndex();
  std::vector<double>& GetVertexCoord();

 private:
  Model* model_;
  View* view_;
};

#endif  // CPP4_3DVIEWER_V2_0_CONTROLLER_CONTROLLER_H_
