#include "view.h"

void View::mouseMoveEvent(QMouseEvent *cursorPosition) {
  if (leftButton) {
    int rotateX = (cursorPosition->pos().y() - clickPosition.y()) / 3;
    int rotateY = (cursorPosition->pos().x() - clickPosition.x()) / 3;
    ui->horizontalSlider_rotate_x->setValue(
        ui->horizontalSlider_rotate_x->value() + rotateX);
    ui->horizontalSlider_rotate_y->setValue(
        ui->horizontalSlider_rotate_y->value() + rotateY);

  } else if (rightButton) {
    int moveX = (cursorPosition->pos().x() - clickPosition.x()) / 2;
    int moveY = (clickPosition.y() - cursorPosition->pos().y()) / 2;
    ui->horizontalSlider_move_x->setValue(ui->horizontalSlider_move_x->value() +
                                          moveX);
    ui->horizontalSlider_move_y->setValue(ui->horizontalSlider_move_y->value() +
                                          moveY);
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
    offset = 8;
  } else if (event->angleDelta().y() < 0) {
    offset = -8;
  }
  ui->horizontalSlider_scale->setValue(ui->horizontalSlider_scale->value() +
                                       offset);
}

// // void View::keyPressEvent(QKeyEvent *event) {
// //   if (event->key() == Qt::Key_G) {
// //     on_actionSave_as_GIF_triggered();
// //   } else if (event->key() == Qt::Key_J) {
// //     on_actionSave_as_jpeg_triggered();
// //   } else if (event->key() == Qt::Key_B) {
// //     on_actionSave_as_bmp_triggered();
// //   }
// // }
