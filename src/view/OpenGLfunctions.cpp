#include "view.h"

void View::initializeGL() {
  x_angle = 15;
  y_angle = 15;
  z_angle = 1;
  glEnable(GL_DEPTH_TEST);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // инициализирую начальный цвет viewport
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void View::resizeGL(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  resize(1440, 1080);
}

void View::paintGL() {
  resize(1440, 1080);
  glClearColor(backgroundColor.redF(), backgroundColor.greenF(), backgroundColor.blueF(), 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  updateValues();
  if (projectionType) {
    std::vector<double> vertexCoord = controller->getVertexCoord();
    glVertexPointer(3, GL_DOUBLE, 0, vertexCoord.data());
    glEnableClientState(GL_VERTEX_ARRAY);
    setProjectionType();

    if (projectionType == PARALLEL) {
      glRotated(x_angle, 1, 0, 0);
      glRotated(y_angle, 0, 1, 0);
      glRotated(z_angle, 0, 0, 1);
    }

    setEdges();
    if (pointVisibility == AVERTEX) setVertices();
    glDisableClientState(GL_VERTEX_ARRAY);
  }
}

void View::updateValues() {
    // projection type
    projectionType = ui->radioButton_parallel_type->isChecked() ? PARALLEL : CENTRAL;

    // edge type
    edgeType = ui->radioButton_edgeType_solid->isChecked() ? SOLID : DASHED;

    edgeWidth = (float)ui->edgeThickness->value();
    pointSize = (float)ui->vertexSize->value() * 2;

    if (ui->radioButton_vertexType_novertex->isChecked()) {
      pointVisibility = NOVERTEX;
    } else {
      pointVisibility = AVERTEX;

      pointType = ui->radioButton_vertexType_circle->isChecked() ? CIRCLE : SQUARE;
    }
}

void View::setEdges() {
  if (edgeType == DASHED) {
    glLineStipple(1, 0x3333);
    glEnable(GL_LINE_STIPPLE);
  } else if (edgeType == SOLID) {
    glDisable(GL_LINE_STIPPLE);
  }

  glLineWidth(edgeWidth);  // setting the edge thickness
  glColor3f(edgeColor.redF(), edgeColor.greenF(), edgeColor.blueF());  // setting the edge color
  std::vector<int> vertexIndex = controller->getVertexIndex();
  glDrawElements(GL_LINES, controller->getVertexIndex().size(), GL_UNSIGNED_INT, vertexIndex.data());
}

void View::setVertices() {
  glPointSize(pointSize);
  glColor3f(vertexColor.redF(), vertexColor.greenF(), vertexColor.blueF());

  if (pointType == CIRCLE) 
  {
    glEnable(GL_POINT_SMOOTH);
    glDrawArrays(GL_POINTS, 0, controller->getVertexCoord().size() / 3);
    glDisable(GL_POINT_SMOOTH);
  } 
  else 
  {
    glDrawArrays(GL_POINTS, 0, controller->getVertexCoord().size() / 3);
  }
}

void View::setProjectionType() {
  if (projectionType == PARALLEL) {
    glOrtho(-5, 8.3, -5, 5, -100, 100);
    glTranslated(2, 0, -10);
  } else if (projectionType == CENTRAL) {
    glFrustum(-1, 1.67, -1, 1, 1, 15);
    glTranslated(0, 0, -10);
  }
}
