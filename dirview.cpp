#include "dirview.h"

#include <QMessageBox>
#include <QStringList>

DirView::DirView(const QDir &dir, QWidget *parent)
: QWidget(parent), m_dir(dir) {
    // TODO: manage non-existing directory
    // TODO: manage showing QFileDialog
}

DirView::~DirView() {}
