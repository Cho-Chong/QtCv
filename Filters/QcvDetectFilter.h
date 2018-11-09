//#ifndef QCVDETECTFILTER_H
//#define QCVDETECTFILTER_H

//#include <QAbstractVideoFilter>
//#include <QDebug>
//#include <QTemporaryFile>
//#include <QMutex>
//#include "opencv2/opencv.hpp"

//class QCvDetectFilter : public QAbstractVideoFilter
//{
//    Q_OBJECT
//public:
//    QVideoFilterRunnable *createFilterRunnable();

//signals:
//    void objectDetected(float x, float y, float w, float h);

//public slots:

//};

//class QCvDetectFilterRunnable : public QVideoFilterRunnable
//{
//public:
//    QCvDetectFilterRunnable(QCvDetectFilter *creator) {filter = creator;}
//    QVideoFrame run(QVideoFrame *input, const QVideoSurfaceFormat &surfaceFormat, RunFlags flags);
//    QImage mat8ToImage(const cv::Mat &mat);
//    cv::Mat imageToMat8(const QImage &image);
//    cv::Mat yuvFrameToMat8(const QVideoFrame &frame);
//private:
//    void dft(cv::InputArray input, cv::OutputArray output);
//    QCvDetectFilter *filter;
//};

//#endif // QCVDETECTFILTER_H
