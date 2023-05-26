// #include "view.h"

// void View::mouseMoveEvent(QMouseEvent *cursorPosition) {
//   if (leftButton) {
//     double rotateX = (cursorPosition->pos().x() - clickPosition.x()) / 75.0;
//     double rotateY = (cursorPosition->pos().y() - clickPosition.y()) / 75.0;
//     rotateModel(&model, rotateY, X);
//     rotateModel(&model, rotateX, Y);
//   } else if (rightButton) {
//     double moveX = (cursorPosition->pos().x() - clickPosition.x()) / 10000.0;
//     double moveY = (cursorPosition->pos().y() - clickPosition.y()) / 10000.0;
//     moveModel(&model, moveY, moveX, 0);
//   }

//   update();
// }

// void View::mousePressEvent(QMouseEvent *event) {
//   clickPosition = event->pos();
//   if (event->button() == Qt::LeftButton) {
//     leftButton = true;
//   } else if (event->button() == Qt::RightButton) {
//     rightButton = true;
//   }
// }

// void View::mouseReleaseEvent(QMouseEvent *cursorPosition) {
//   leftButton = false;
//   rightButton = false;
//   cursorPosition->pos() = clickPosition;
// }

// void View::wheelEvent(QWheelEvent *event) {
//   scaleModel(&model, event->angleDelta().y() >= 0 ? 10 : -10);
//   update();
// }

// void View::keyPressEvent(QKeyEvent *event) {
//   if (event->key() == Qt::Key_G) {
//     on_actionSave_as_GIF_triggered();
//   } else if (event->key() == Qt::Key_J) {
//     on_actionSave_as_jpeg_triggered();
//   } else if (event->key() == Qt::Key_B) {
//     on_actionSave_as_bmp_triggered();
//   }
// }
