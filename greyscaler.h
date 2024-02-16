#ifndef WIDGET_H
#define WIDGET_H

#include <QImage>
#include <QLabel>
#include <QStringList>
#include <QWidget>

#include <memory>

class Greyscaler : public QWidget {
    Q_OBJECT

public:
    Greyscaler(QWidget *parent = nullptr);
    ~Greyscaler() = default;

private:
    std::unique_ptr<QImage> m_image = nullptr;
    QLabel *m_imageLabel = nullptr;

    QStringList getCapableApps() const;
signals:
    void imageLoaded() const;
};
#endif // WIDGET_H
