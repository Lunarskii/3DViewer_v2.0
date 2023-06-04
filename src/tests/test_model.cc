#include "test_core.h"

using namespace std;

TEST(Model, CorrectFile) {
  Model *model;
  model = &Model::GetInstance();

  model->SetFileName("tests/models/cube.obj");
  model->Parser();

  EXPECT_EQ(model->GetError(), 0);
  EXPECT_EQ(model->GetVertexCoord().size(), 24);
  EXPECT_EQ(model->GetVertexIndex().size(), 72);
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

// Возможно стоит еще тестить transform
