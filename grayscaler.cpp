#include "grayscaler.hpp"

#include <sdbus-c++/sdbus-c++.h>

#include <QDir>
#include <QFileDialog>
#include <QImageReader>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QPushButton>
#include <QStringList>

#include <iostream>

constexpr char const *interface = "org.rt.SharingService";
constexpr char const *dest = "org.rt.sharing";
constexpr char const *objPath = "/org/rt/router";

Grayscaler::Grayscaler(QWidget *parent)
: QWidget(parent), m_imageLabel(new QLabel) {
    auto topLayout = new QVBoxLayout();
    auto browseLayout = new QHBoxLayout();
    QLabel *selectLabel = new QLabel("Select image to convert");
    QPushButton *browseButton = new QPushButton("Browse...");
    browseButton->setDefault(true);
    connect(browseButton, &QPushButton::clicked, this,
            [this]() {
                const QString filename = QFileDialog::getOpenFileName(this, tr("Browse for file"),
                                                                      QDir::currentPath(),
                                                                      "Images (*.png *.jpg);;All files (*.*)");
                QImageReader rdr(filename);
                rdr.setAutoTransform(true);
                const QImage img = rdr.read();
                if (img.isNull()) {
                    QMessageBox::information(this, tr("Failure"), "Specified file is not an image.");
                } else {
                    if (m_image) {
                        m_image.release();
                    }
                    m_image = std::make_unique<QImage>(img.copy());
                    const QPixmap pixmap = QPixmap::fromImage(*m_image);
                    m_imageLabel->setPixmap(pixmap);
                    emit imageLoaded();
                }
            });
    QPushButton *convertButton = new QPushButton("Greyscale with...");
    convertButton->setVisible(false);
    connect(this, &Grayscaler::imageLoaded, convertButton, [convertButton]() {
        convertButton->setVisible(true);
    });
    connect(convertButton, &QPushButton::clicked, this, &Grayscaler::showAppsList);

    browseLayout->addWidget(selectLabel);
    browseLayout->addWidget(browseButton);
    topLayout->addLayout(browseLayout);
    topLayout->addWidget(m_imageLabel);
    topLayout->addWidget(convertButton);
    setLayout(topLayout);

    m_sharingProxy = sdbus::createProxy(dest, objPath);
    m_sharingProxy->finishRegistration();
}

void Grayscaler::showAppsList() {
    std::vector<std::string> endpointsList;
    m_sharingProxy->callMethod("getEndpoints").onInterface(interface).storeResultsTo(endpointsList);
    for (const auto &endpoint : endpointsList) {
        std::cout << endpoint << '\n';
    }
}
