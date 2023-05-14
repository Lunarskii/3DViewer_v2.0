#include "view/view.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Model model;
    Controller controller(&model);
    View view(&controller);
    view.show();
    return a.exec();
}
