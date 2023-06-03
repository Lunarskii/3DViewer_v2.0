#include <QApplication>

#include "controller/controller.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  View view;
  view.setWindowTitle("3D Viewer");
  Controller controller(&view);

  QObject::connect(
      &controller,
      SIGNAL(solutionReady(std::vector<int> *, std::vector<double> *)), &view,
      SLOT(handleSolution(std::vector<int> *, std::vector<double> *)));

  view.show();
  return a.exec();
}
