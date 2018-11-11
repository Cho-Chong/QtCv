#ifndef OPENVIDCAP_H
#define OPENVIDCAP_H

#include <QQuickPaintedItem>
#include <QQuickItem>
#include <QPainter>
#include <QTimer>
#include <QImage>
#include "opencv2/opencv.hpp"
#include "opencv2/xfeatures2d/nonfree.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/xfeatures2d.hpp"
#include "cvmatandqimage.h"

using namespace cv;
using namespace cv::xfeatures2d;

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

        if(!face_cascade.load("face_class.xml"))
        {
            qWarning() << "Failed to load classifier";
        }
        if(!eyes_cascade.load("eye_class.xml"))
        {
            qWarning() << "Failed to load classifier";
        }
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

//            int minHessian = 400;



//            if(use_canny || use_otsu || use_tri)
//            {
//                cv::cvtColor(mat, mat, CV_BGR2GRAY);
//            }

//            if(use_canny)
//            {
//                cv::Canny(mat, mat, Thresh, MaxThresh, 3, true);
//            }
//            else
//            {
//                if(use_otsu)
//                {
//                    type |= CV_THRESH_OTSU;
//                }
//                else if (use_tri)
//                {
//                    type |= CV_THRESH_TRIANGLE;
//                }

//                cv::threshold(mat, mat, Thresh, MaxThresh, type);
//            }

////            Ptr<SURF> detector = SIFT::create(minHessian);
//            Ptr<SIFT> detector = SIFT::create();
////            SiftFeatureDetector sift_detector;

//            std::vector<KeyPoint> keypoints;
//            detector->detect(mat, keypoints);

//            Mat img_keypoints;
//            drawKeypoints( mat, keypoints, img_keypoints );

//            if(use_blur)
//            {
//                cv::GaussianBlur(mat, mat, cv::Size(BlurSize, BlurSize), 0);
//            }

            detectAndDisplay(mat);

            current_image = QtOcv::mat2Image(mat, QtOcv::MCO_BGR, QImage::Format_RGB888);
            update();
        }
    }

    /** @function detectAndDisplay */
    void detectAndDisplay( Mat& frame )
    {
      std::vector<Rect> faces;
      Mat frame_gray;

      cvtColor( frame, frame_gray, CV_BGR2GRAY );
      equalizeHist( frame_gray, frame_gray );

      //-- Detect faces
      face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );

      for( size_t i = 0; i < faces.size(); i++ )
      {
        Point center( faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5 );
        ellipse( frame, center, Size( faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );

        Mat faceROI = frame_gray( faces[i] );
        std::vector<Rect> eyes;

        //-- In each face, detect eyes
        eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 |CV_HAAR_SCALE_IMAGE, Size(30, 30) );

        for( size_t j = 0; j < eyes.size(); j++ )
         {
           Point center( faces[i].x + eyes[j].x + eyes[j].width*0.5, faces[i].y + eyes[j].y + eyes[j].height*0.5 );
           int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
           circle( frame, center, radius, Scalar( 255, 0, 0 ), 4, 8, 0 );
         }
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
    CascadeClassifier face_cascade;
    CascadeClassifier eyes_cascade;
};

#endif // OPENVIDCAP_H
