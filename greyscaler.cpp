#include "greyscaler.h"

#include <QDir>
#include <QFileDialog>
#include <QImageReader>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QPushButton>
#include <QStringList>

Greyscaler::Greyscaler(QWidget *parent)
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
    connect(this, &Greyscaler::imageLoaded, convertButton, [convertButton]() {
        convertButton->setVisible(true);
    });
    connect(convertButton, &QPushButton::clicked, this, &Greyscaler::listApps);

    browseLayout->addWidget(selectLabel);
    browseLayout->addWidget(browseButton);
    topLayout->addLayout(browseLayout);
    topLayout->addWidget(m_imageLabel);
    topLayout->addWidget(convertButton);
    setLayout(topLayout);
}
