#include "view/view.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Controller controller;
    View view(&controller);
    view.show();
    return a.exec();
}
