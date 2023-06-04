#ifndef CPP4_3DVIEWER_V2_0_MODEL_MODEL_H_
#define CPP4_3DVIEWER_V2_0_MODEL_MODEL_H_

#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "tranformation.h"

enum error_list {
  FILE_HAS_WRONG_EXTENSION = 1,
  FAILED_TO_OPEN_FILE = 2,
  INCORRECT_ENTRY_OF_THE_VERTEX_COORDINATE = 3,
};

class Model {
 public:
  void Parser();

  void SetFileName(const std::string& fileName);
  int GetError();
  std::vector<int>& GetVertexIndex();
  std::vector<double>& GetVertexCoord();
  void Transform(int& strategyType, double& value, transformation_t& axis);

  static Model& GetInstance();

 private:
  Model() = default;

  void VertexParser_(const std::string& line);
  void EdgesParser_(const std::string& line);

  std::string filename_;
  std::vector<double> vertex_coord_{};
  std::vector<int> vertex_index_{};
  int error_code_{};
  Strategy TransformationModel_;
};

#endif  // CPP4_3DVIEWER_V2_0_MODEL_MODEL_H_
