#include "view.h"

void View::initializeGL() {
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
  glClearColor(settings.backgroundColor.redF(),
               settings.backgroundColor.greenF(),
               settings.backgroundColor.blueF(), 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  updateValues();
  if (settings.projectionType) {
    glVertexPointer(3, GL_DOUBLE, 0, vertex_coord_);
    glEnableClientState(GL_VERTEX_ARRAY);
    setProjectionType();

    if (settings.projectionType == kParallel) {
      glRotated(15, 1, 0, 0);
      glRotated(15, 0, 1, 0);
      glRotated(1, 0, 0, 1);
    }

    setEdges();
    if (settings.pointVisibility == kAVertex) setVertices();
    glDisableClientState(GL_VERTEX_ARRAY);
  }
}

void View::updateValues() {
  settings.projectionType =
      ui->comboBox_disp_method_2->currentText() == "Parallel" ? kParallel
                                                              : kCentral;
  settings.edgeType = ui->comboBox->currentText() == "Solid" ? kSolid : kDashed;

  settings.edgeWidth = ui->horizontalSlider_edges_thick->value();
  settings.pointSize = ui->horizontalSlider_vert_size->value();

  if (ui->comboBox_disp_method->currentText() == "None") {
    settings.pointVisibility = kNoVertex;
  } else {
    settings.pointVisibility = kAVertex;

    settings.pointType =
        ui->comboBox_disp_method->currentText() == "Circle" ? kCircle : kSquare;
  }
}

void View::setEdges() {
  if (settings.edgeType == kDashed) {
    glLineStipple(1, 0x3333);
    glEnable(GL_LINE_STIPPLE);
  } else if (settings.edgeType == kSolid) {
    glDisable(GL_LINE_STIPPLE);
  }

  glLineWidth(settings.edgeWidth);
  glColor3f(settings.edgeColor.redF(), settings.edgeColor.greenF(),
            settings.edgeColor.blueF());  // setting the edge color
  glDrawElements(GL_LINES, count_vertex_index_, GL_UNSIGNED_INT, vertex_index_);
}

void View::setVertices() {
  glPointSize(settings.pointSize);
  glColor3f(settings.vertexColor.redF(), settings.vertexColor.greenF(),
            settings.vertexColor.blueF());

  if (settings.pointType == kCircle) {
    glEnable(GL_POINT_SMOOTH);
    glDrawArrays(GL_POINTS, 0, count_vertex_coord_ / 3);
    glDisable(GL_POINT_SMOOTH);
  } else {
    glDrawArrays(GL_POINTS, 0, count_vertex_coord_ / 3);
  }
}

void View::setProjectionType() {
  if (settings.projectionType == kParallel) {
    glOrtho(-5, 8.3, -5, 5, -100, 100);
    glTranslated(2, 0, -10);
  } else if (settings.projectionType == kCentral) {
    glFrustum(-1, 1.67, -1, 1, 1, 15);
    glTranslated(0, 0, -10);
  }
}
