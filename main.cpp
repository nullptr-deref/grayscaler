#include "grayscaler.hpp"

#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Grayscaler g;
    g.show();

    return a.exec();
}
