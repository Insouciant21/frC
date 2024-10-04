#include "frC.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    frC w;
    w.show();
    w.setWindowIcon(QIcon(".\\favicon.ico"));
    return a.exec();
}
