#ifndef CPP4_3DVIEWER_V2_0_MODEL_TRANSFORMATION_H_
#define CPP4_3DVIEWER_V2_0_MODEL_TRANSFORMATION_H_

#include <cmath>
#include <vector>

typedef enum {
  kX = 0,
  kY = 1,
  kZ = 2,
  kMove = 0,
  kRotate = 1,
  kScale = 2
} transformation_t;

class TransformationStrategy {
 public:
  virtual ~TransformationStrategy() {}
  virtual void Transform(std::vector<double>&, double&,
                         transformation_t& axis) {}
};

class MoveStrategy : public TransformationStrategy {
  void Transform(std::vector<double>& vertexCoord, double& step,
                 transformation_t& axis) override;
};

class RotateStrategy : public TransformationStrategy {
  void Transform(std::vector<double>& vertexCoord, double& angle,
                 transformation_t& axis) override;
};

class ScaleStrategy : public TransformationStrategy {
  void Transform(std::vector<double>& vertexCoord, double& scale,
                 transformation_t&) override;
};

class Strategy {
 public:
  Strategy();
  void setStrategy(TransformationStrategy* strategy);
  void performTransformation(std::vector<double>& vertexCoord, double& value,
                             transformation_t& axis);

 private:
  TransformationStrategy* strategy_;
};

#endif  // CPP4_3DVIEWER_V2_0_MODEL_TRANSFORMATION_H_
