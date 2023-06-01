#include "test_core.h"

using namespace std;

TEST(Model, CorrectFile) {
  Model *model;
  model = &Model::getInstance();

  model->setFileName("tests/models/cube.obj");
  model->parser();

  EXPECT_EQ(model->getError(), 0);
  EXPECT_EQ(model->getVertexCoord().size(), 24);
  EXPECT_EQ(model->getVertexIndex().size(), 72);
}

TEST(Model, WrongExtension) {
  Model *model;
  model = &Model::getInstance();

  model->setFileName("Makefile");
  model->parser();

  EXPECT_EQ(model->getError(), FILE_HAS_WRONG_EXTENSION);
  EXPECT_TRUE(model->getVertexCoord().empty());
  EXPECT_TRUE(model->getVertexIndex().empty());
}

TEST(Model, FailedToOpen) {
  Model *model;
  model = &Model::getInstance();

  model->setFileName("qwerty.obj");
  model->parser();

  EXPECT_EQ(model->getError(), FAILED_TO_OPEN_FILE);
  EXPECT_TRUE(model->getVertexCoord().empty());
  EXPECT_TRUE(model->getVertexIndex().empty());
}

TEST(Model, IncorrectFile) {
  Model *model;
  model = &Model::getInstance();

  model->setFileName("tests/models/incorrect.obj");
  model->parser();

  EXPECT_EQ(model->getError(), INCORRECT_ENTRY_OF_THE_VERTEX_COORDINATE);
}

// Возможно стоит еще тестить transform