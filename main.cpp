#include "dirview.h"

#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    if (argc < 2) {
        QMessageBox mbox;
        mbox.setWindowTitle("Fatal error");
        mbox.setText("No directory to observe.");
        mbox.addButton(QMessageBox::Ok);
        return mbox.exec();
    }
    const QString strPath(argv[1]);
    DirView v{QDir(strPath)};
    v.show();

    return a.exec();
}
