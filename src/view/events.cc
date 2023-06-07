#include "view.h"

void View::mouseMoveEvent(QMouseEvent *cursorPosition) {
  if (leftButton) {
    int rotate_x = (cursorPosition->pos().y() - clickPosition.y()) / 3;
    int rotate_y = (cursorPosition->pos().x() - clickPosition.x()) / 3;
    ui->horizontalSlider_rotate_x->setValue(
        ui->horizontalSlider_rotate_x->value() + rotate_x);
    ui->horizontalSlider_rotate_y->setValue(
        ui->horizontalSlider_rotate_y->value() + rotate_y);

  } else if (rightButton) {
    int move_x = (cursorPosition->pos().x() - clickPosition.x()) / 2;
    int move_y = (clickPosition.y() - cursorPosition->pos().y()) / 2;
    ui->horizontalSlider_move_x->setValue(ui->horizontalSlider_move_x->value() +
                                          move_x);
    ui->horizontalSlider_move_y->setValue(ui->horizontalSlider_move_y->value() +
                                          move_y);
  }

  clickPosition.setX(cursorPosition->pos().x());
  clickPosition.setY(cursorPosition->pos().y());
  update();
}

void View::mousePressEvent(QMouseEvent *event) {
  clickPosition = event->pos();
  if (event->button() == Qt::LeftButton) {
    leftButton = true;
  } else if (event->button() == Qt::RightButton) {
    rightButton = true;
  }
}

void View::mouseReleaseEvent(QMouseEvent *cursorPosition) {
  leftButton = false;
  rightButton = false;
  clickPosition = cursorPosition->pos();
}

void View::wheelEvent(QWheelEvent *event) {
  int offset = 0;
  if (event->angleDelta().y() > 0) {
    offset = 6;
  } else if (event->angleDelta().y() < 0) {
    offset = -6;
  }
  ui->horizontalSlider_scale->setValue(ui->horizontalSlider_scale->value() +
                                       offset);
}