 #include "view.h"

 void View::mouseMoveEvent(QMouseEvent *cursorPosition) {
   if (leftButton) {
      int rotateX = (cursorPosition->pos().x() - clickPosition.x()) / 15;
      int rotateY = (cursorPosition->pos().y() - clickPosition.y()) / 15;
      ui->horizontalSlider_rotate_y->setValue(rotateY);
      ui->horizontalSlider_rotate_x->setValue(rotateX);



   } else if (rightButton) {
      int moveX = (cursorPosition->pos().x() - clickPosition.x()) / 100;
      int moveY = (clickPosition.y() - cursorPosition->pos().y()) / 100;
      ui->horizontalSlider_move_x->setValue(moveX);
      ui->horizontalSlider_move_y->setValue(moveY);
   }

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
   cursorPosition->pos() = clickPosition;
 }

  void View::wheelEvent(QWheelEvent *event) {
    int offset = 0;
    if (event->angleDelta().y() > 0) {
      offset = 8;
    } else if (event->angleDelta().y() < 0) {
      offset = -8;
    }
    ui->horizontalSlider_scale->setValue(ui->horizontalSlider_scale->value() + offset);
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
