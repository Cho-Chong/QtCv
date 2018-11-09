#ifndef OPENVIDCAP_H
#define OPENVIDCAP_H

#include <QQuickPaintedItem>
#include <QQuickItem>
#include <QPainter>
#include <QTimer>
#include <QImage>
#include "opencv2/opencv.hpp"
#include "cvmatandqimage.h"

class OpenVidCap : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QImage image READ image WRITE setImage NOTIFY imageChanged)
    Q_PROPERTY(bool useTri READ useTri NOTIFY threshChanged)
    Q_PROPERTY(bool useOtsu READ useOtsu NOTIFY threshChanged)
    Q_PROPERTY(bool useBlur READ useBlur NOTIFY threshChanged)
    Q_PROPERTY(bool useCanny READ useCanny NOTIFY threshChanged)
    Q_PROPERTY(double threshold READ threshold NOTIFY threshChanged)
    Q_PROPERTY(double maxThresh READ maxThresh NOTIFY threshChanged)
    Q_PROPERTY(quint32 thresholdType READ thresholdType NOTIFY threshChanged)
    Q_PROPERTY(quint32 blurSize READ blurSize NOTIFY threshChanged)


public:
    OpenVidCap(QQuickItem *parent = nullptr) : QQuickPaintedItem(parent),
        VidCap(0)
    {
        connect(&VidUpdateTimer, &QTimer::timeout, this, &OpenVidCap::UpdateVid);
        VidUpdateTimer.setSingleShot(false);
        VidUpdateTimer.setInterval(VID_UPDATE_RATE_MS);
        VidUpdateTimer.start(VID_UPDATE_RATE_MS);
    }

    Q_INVOKABLE void setImage(const QImage &image) {
        this->current_image = image;
        update();
    }
    void paint(QPainter *painter) {
        QRectF bounding_rect = boundingRect();
//        QImage scaled = this->current_image.scaledToHeight(bounding_rect.height());
        QPointF center = bounding_rect.center() - this->current_image.rect().center();

        if(center.x() < 0)
            center.setX(0);
        if(center.y() < 0)
            center.setY(0);
       painter->drawImage(center, this->current_image);
    }

    QImage image() const { return current_image; }


    quint32 thresholdType() const { return ThresholdType; }
    double threshold() const { return Thresh; }
    double maxThresh() const { return MaxThresh; }
    qint32 blurSize() const { return BlurSize; }

    bool useOtsu() const { return use_otsu; }
    bool useTri() const { return use_tri; }
    bool useBlur() const { return use_blur; }
    bool useCanny() const { return use_canny; }

    Q_INVOKABLE void setUseOtsu(bool val) { use_otsu = val; }
    Q_INVOKABLE void setUseTri(bool val) { use_tri = val; }
    Q_INVOKABLE void setUseBlur(bool val) { use_blur = val; }
    Q_INVOKABLE void setUseCanny(bool val) { use_canny = val; }
    Q_INVOKABLE void setThreshold(double val) { Thresh = val; }
    Q_INVOKABLE void setMaxThresh(double val) { MaxThresh = val; }
    Q_INVOKABLE void setBlurSize(qint32 val) { BlurSize = val; }
    Q_INVOKABLE void setThresholdType(quint32 thresh_type)
    {
        if((thresh_type >= CV_THRESH_BINARY && thresh_type <= CV_THRESH_TOZERO_INV))
        {
            ThresholdType = thresh_type;
        }
    }


signals:
    void imageChanged();
    void threshChanged();


private:

    void UpdateVid()
    {
        if(VidCap.isOpened())
        {
            VidCap >> mat;
            auto type = ThresholdType;

            if(use_blur)
            {
                cv::GaussianBlur(mat, mat, cv::Size(BlurSize, BlurSize), 0);
            }

            if(use_canny || use_otsu || use_tri)
            {
                cv::cvtColor(mat, mat, CV_BGR2GRAY);
            }

            if(use_canny)
            {
                cv::Canny(mat, mat, Thresh, MaxThresh, 3, true);
            }
            else
            {
                if(use_otsu)
                {
                    type |= CV_THRESH_OTSU;
                }
                else if (use_tri)
                {
                    type |= CV_THRESH_TRIANGLE;
                }

                cv::threshold(mat, mat, Thresh, MaxThresh, type);
            }

            current_image = QtOcv::mat2Image(mat, QtOcv::MCO_BGR, QImage::Format_RGB888);
            update();
        }
    }


    constexpr static qint32 VID_UPDATE_RATE_MS = 50;

    QTimer VidUpdateTimer;
    cv::VideoCapture VidCap;
    cv::Mat mat;
    QImage current_image;
    quint32 ThresholdType = CV_THRESH_BINARY;
    double Thresh = 100;
    double MaxThresh = 255;
    qint32 BlurSize = 5;
    bool use_otsu = false;
    bool use_tri = false;
    bool use_blur = false;
    bool use_canny = false;
};

#endif // OPENVIDCAP_H
