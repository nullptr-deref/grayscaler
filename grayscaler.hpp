#ifndef WIDGET_H
#define WIDGET_H

#include <sdbus-c++/sdbus-c++.h>

#include <QImage>
#include <QLabel>
#include <QStringList>
#include <QWidget>

#include <memory>

class Grayscaler : public QWidget {
    Q_OBJECT

public:
    Grayscaler(QWidget *parent = nullptr);
    ~Grayscaler() = default;

private:
    std::unique_ptr<QImage> m_image = nullptr;
    QLabel *m_imageLabel = nullptr;

    QStringList getCapableApps() const;
    void showAppsList();
    std::unique_ptr<sdbus::IProxy> m_sharingProxy;
signals:
    void imageLoaded() const;
};
#endif // WIDGET_H
