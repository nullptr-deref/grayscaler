#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDir>

class DirView : public QWidget {
    Q_OBJECT

public:
    DirView(const QDir &dir, QWidget *parent = nullptr);
    ~DirView();

private:
    QDir m_dir;
};
#endif // WIDGET_H
