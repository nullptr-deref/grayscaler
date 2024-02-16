#include "greyscaler.h"

#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Greyscaler g;
    g.show();

    return a.exec();
}
