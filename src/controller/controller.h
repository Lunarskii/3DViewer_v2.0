#ifndef CPP4_3DVIEWER_V2_0_CONTROLLER_CONTROLLER_H_
#define CPP4_3DVIEWER_V2_0_CONTROLLER_CONTROLLER_H_

#include "../model/model.h"
#include "../view/view.h"

class Controller : public QObject {
  Q_OBJECT

public:
  explicit Controller(View* newView)
      : model_(&Model::GetInstance()), view_(newView) {
    QObject::connect(view_, SIGNAL(SetModel(QString)), this,
                     SLOT(SetFileName_(QString)));
    QObject::connect(view_->facade, SIGNAL(SetTransform(int, double, int)),
                     this, SLOT(Transform_(int, double, int)));
  }

  int GetError();
  std::vector<int>& GetVertexIndex();
  std::vector<double>& GetVertexCoord();

signals:
  void SolutionReady(std::vector<int>* vertexIndex,
                     std::vector<double>* vertexCoord);
  void ErrorHasOccured();

private slots:
  void SetFileName_(const QString& fileName);
  void Transform_(int strategyType, double value, int axis = kX);

private:
  Model* model_;
  View* view_;
};

#endif  // CPP4_3DVIEWER_V2_0_CONTROLLER_CONTROLLER_H_
