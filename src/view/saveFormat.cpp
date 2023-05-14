#include "view.h"

void View::on_actionSave_as_GIF_triggered() {
  frames = 0;
  gif = new QGifImage;
  timer = new QTimer(this);
  gif->setDefaultDelay(100);
  connect(timer, SIGNAL(timeout()), this, SLOT(saveImage()));
  timer->start(100);
}

void View::saveImage() {
  QPixmap pix = QPixmap::fromImage(grabFramebuffer());
  QPixmap scaledPix = pix.scaled(QSize(640, 480), Qt::IgnoreAspectRatio,
                                 Qt::SmoothTransformation);
  gif->addFrame(scaledPix.toImage());

  if (frames == 50) {
    timer->stop();
    QString pathGIF = QFileDialog::getSaveFileName(
        this, ("Save as GIF"), "image.gif", "GIF Image Files (*.gif)");
    gif->save(pathGIF);
    delete timer;
    delete gif;
  }
  frames++;
}

void View::on_actionSave_as_bmp_triggered() {
  QString pathScreenshot = QFileDialog::getSaveFileName(
      this, ("Save as BMP"), "image.bmp", "BMP Image Files (*.bmp)");

  grabFramebuffer().save(pathScreenshot, "bmp");
}

void View::on_actionSave_as_jpeg_triggered() {
  QString pathScreenshot = QFileDialog::getSaveFileName(
      this, ("Save as JPEG"), "image.jpeg", "JPEG Image Files (*.jpeg)");

  grabFramebuffer().save(pathScreenshot, "jpeg");
}
