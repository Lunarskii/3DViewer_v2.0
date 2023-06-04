#include "test_core.h"

using namespace std;

TEST(Model, CorrectFile) {
  Model *model;
  model = &Model::GetInstance();

  model->SetFileName("tests/models/cub.obj");
  model->Parser();

  EXPECT_EQ(model->GetError(), 0);
  EXPECT_EQ(model->GetVertexCoord().size(), 24);
  EXPECT_EQ(model->GetVertexIndex().size(), 48);
}

TEST(Model, WrongExtension) {
  Model *model;
  model = &Model::GetInstance();

  model->SetFileName("Makefile");
  model->Parser();

  EXPECT_EQ(model->GetError(), FILE_HAS_WRONG_EXTENSION);
  EXPECT_TRUE(model->GetVertexCoord().empty());
  EXPECT_TRUE(model->GetVertexIndex().empty());
}

TEST(Model, FailedToOpen) {
  Model *model;
  model = &Model::GetInstance();

  model->SetFileName("qwerty.obj");
  model->Parser();

  EXPECT_EQ(model->GetError(), FAILED_TO_OPEN_FILE);
  EXPECT_TRUE(model->GetVertexCoord().empty());
  EXPECT_TRUE(model->GetVertexIndex().empty());
}

TEST(Model, IncorrectFile) {
  Model *model;
  model = &Model::GetInstance();

  model->SetFileName("tests/models/incorrect.obj");
  model->Parser();

  EXPECT_EQ(model->GetError(), INCORRECT_ENTRY_OF_THE_VERTEX_COORDINATE);
}

TEST(Model, Move) {
  Model *model;
  model = &Model::GetInstance();

  model->SetFileName("tests/models/cub.obj");
  model->Parser();

  std::vector<double> vertex_copy(model->GetVertexCoord());
  auto axis_x = X, axis_y = Y, axis_z = Z;
  int strategy = MOVE;
  double value = 1;
  model->Transform(strategy, value, axis_x);
  model->Transform(strategy, value, axis_y);
  model->Transform(strategy, value, axis_z);

  for (int i = 0; i < vertex_copy.size(); i++) {
    EXPECT_DOUBLE_EQ(model->GetVertexCoord()[i], vertex_copy[i] + 1);
  }
}

TEST(Model, Rotate) {
  Model *model;
  model = &Model::GetInstance();

  model->SetFileName("tests/models/cub.obj");
  model->Parser();

  std::vector<double> vertex_copy(model->GetVertexCoord());
  auto axis_x = X, axis_y = Y, axis_z = Z;
  int strategy = ROTATE;
  double value = 5;
  model->Transform(strategy, value, axis_x);
  model->Transform(strategy, value, axis_y);
  model->Transform(strategy, value, axis_z);

  for (int i = 0; i < vertex_copy.size(); i++) {
    if (vertex_copy[i] != 0) {
      EXPECT_FALSE(model->GetVertexCoord()[i] == vertex_copy[i]);
    }
  }
}

TEST(Model, Scale) {
  Model *model;
  model = &Model::GetInstance();

  model->SetFileName("tests/models/cub.obj");
  model->Parser();

  std::vector<double> vertex_copy(model->GetVertexCoord());
  auto axis_x = X;
  int strategy = SCALE;
  double value = 5;
  model->Transform(strategy, value, axis_x);

  for (int i = 0; i < vertex_copy.size(); i++) {
    EXPECT_DOUBLE_EQ(model->GetVertexCoord()[i], vertex_copy[i] * 5);
  }
}