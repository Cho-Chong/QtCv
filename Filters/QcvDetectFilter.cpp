//#include "Qcvdetectfilter.h"
//#include <QImage>
//#include <QAbstractVideoBuffer>
//#include <QOpenGLContext>
//#include <QOpenGLFunctions>
//#include <QOpenGLFramebufferObject>

///*
//  Returns a QImage that wraps the given video frame.
//  This is suitable only for QAbstractVideoBuffer::NoHandle frames with RGB (or BGR)
//  data. YUV is not supported here.
//  The QVideoFrame must be mapped and kept mapped as long as the wrapping QImage
//  exists.
//  As a convenience the function also supports frames with a handle type of
//  QAbstractVideoBuffer::GLTextureHandle. This allows creating a system memory backed
//  QVideoFrame containing the image data from an OpenGL texture. However, readback is a
//  slow operation and may stall the GPU pipeline and should be avoided in production code.
//*/
//static QImage imageWrapper(const QVideoFrame &frame)
//{
//#ifndef QT_NO_OPENGL
//    if (frame.handleType() == QAbstractVideoBuffer::GLTextureHandle) {
//        // Slow and inefficient path. Ideally what's on the GPU should remain on the GPU, instead of readbacks like this.
//        QImage img(frame.width(), frame.height(), QImage::Format_RGBA8888);
//        GLuint textureId = frame.handle().toUInt();
//        QOpenGLContext *ctx = QOpenGLContext::currentContext();
//        QOpenGLFunctions *f = ctx->functions();
//        GLuint fbo;
//        f->glGenFramebuffers(1, &fbo);
//        GLuint prevFbo;
//        f->glGetIntegerv(GL_FRAMEBUFFER_BINDING, (GLint *) &prevFbo);
//        f->glBindFramebuffer(GL_FRAMEBUFFER, fbo);
//        f->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureId, 0);
//        f->glReadPixels(0, 0, frame.width(), frame.height(), GL_RGBA, GL_UNSIGNED_BYTE, img.bits());
//        f->glBindFramebuffer(GL_FRAMEBUFFER, prevFbo);
//        return img;
//    } else
//#endif // QT_NO_OPENGL
//    {
//        if (!frame.isReadable()) {
//            qWarning("imageWrapper: No mapped image data available for read");
//            return QImage();
//        }

//        QImage::Format fmt = QVideoFrame::imageFormatFromPixelFormat(frame.pixelFormat());
//        if (fmt != QImage::Format_Invalid)
//            return QImage(frame.bits(), frame.width(), frame.height(), fmt);

//        qWarning("imageWrapper: No matching QImage format");
//    }

//    return QImage();
//}


//cv::CascadeClassifier classifier;

//QVideoFilterRunnable* QCvDetectFilter::createFilterRunnable()
//{
//    return new QCvDetectFilterRunnable(this);
//}

//QVideoFrame QCvDetectFilterRunnable::run(QVideoFrame *input, const QVideoSurfaceFormat &surfaceFormat, RunFlags flags)
//{
//    Q_UNUSED(flags);
//    input->map(QAbstractVideoBuffer::ReadOnly);

//    if(surfaceFormat.handleType() == QAbstractVideoBuffer::NoHandle)
//    {
//        cv::Mat mat;
//        if (input->pixelFormat() == QVideoFrame::Format_YUV420P || input->pixelFormat() == QVideoFrame::Format_NV12) {
//                mat = yuvFrameToMat8(*input);
//            }
//        else {
//                QImage wrapper = imageWrapper(*input);
//                if (wrapper.isNull()) {
//                    if (input->handleType() == QAbstractVideoBuffer::NoHandle)
//                        input->unmap();
//                    return *input;
//                }
//                mat = imageToMat8(wrapper);
//        }

////        cvtColor(mat, mat, CV_RGB2GRAY);

//        return QVideoFrame(mat8ToImage(mat));


////        if(classifier.empty())
////        {
////            QFile xml(":/faceclassifier.xml");
////            if(xml.open(QFile::ReadOnly | QFile::Text))
////            {
////                QTemporaryFile temp;
////                if(temp.open())
////                {
////                    temp.write(xml.readAll());
////                    temp.close();
////                    if(classifier.load(temp.fileName().toStdString()))
////                    {
////                        qDebug() << "Successfully loaded classifier!";
////                    }
////                    else
////                    {
////                        qDebug() << "Could not load classifier.";
////                    }
////                }
////                else
////                {
////                    qDebug() << "Can't open temp file.";
////                }
////            }
////            else
////            {
////                qDebug() << "Can't open XML.";
////            }
////        }
////        else
////        {
////            std::vector<cv::Rect> detected;

////            /*
////             * Resize in not mandatory but it can speed up things quite a lot!
////             */
////            QSize resized = image.size().scaled(320, 240, Qt::KeepAspectRatio);
////            cv::resize(mat, mat, cv::Size(resized.width(), resized.height()));

////            classifier.detectMultiScale(mat, detected, 1.1);

////            // We'll use only the first detection to make sure things are not slow on the qml side
////            if(detected.size() > 0)
////            {
////                // Normalize x,y,w,h to values between 0..1 and send them to UI
////                emit filter->objectDetected(float(detected[0].x) / float(mat.cols),
////                        float(detected[0].y) / float(mat.rows),
////                        float(detected[0].width) / float(mat.cols),
////                        float(detected[0].height) / float(mat.rows));
////            }
////            else
////            {
////                emit filter->objectDetected(0.0,
////                                            0.0,
////                                            0.0,
////                                            0.0);
////            }
////        }
//    }
//    else
//    {
//        qDebug() << "Other surface formats are not supported yet!";
//    }


//    input->unmap();
//    return *input;
//}

//QImage QCvDetectFilterRunnable::mat8ToImage(const cv::Mat &mat)
//{
//    switch (mat.type()) {
//    case CV_8UC1:
//    {
//        QVector<QRgb> ct;
//        for (int i = 0; i < 256; ++i)
//            ct.append(qGray(i, i, i));
//        QImage result(mat.data, mat.cols, mat.rows, (int) mat.step, QImage::Format_Indexed8);
//        result.setColorTable(ct);
//        return result.copy();
//    }
//    case CV_8UC3:
//    {
//        cv::Mat tmp;
//        cvtColor(mat, tmp, CV_GRAY2BGRA);
//        return mat8ToImage(tmp);
//    }
//    case CV_8UC4:
//    {
//        QImage result(mat.data, mat.cols, mat.rows, (int) mat.step, QImage::Format_RGB32);
//        result.invertPixels();
//        return result.rgbSwapped();

//    }
//    default:
//        qWarning("Unhandled Mat format %d", mat.type());
//        return QImage();
//    }
//}

//cv::Mat QCvDetectFilterRunnable::yuvFrameToMat8(const QVideoFrame &frame)
//{
//    Q_ASSERT(frame.handleType() == QAbstractVideoBuffer::NoHandle && frame.isReadable());
//    Q_ASSERT(frame.pixelFormat() == QVideoFrame::Format_YUV420P || frame.pixelFormat() == QVideoFrame::Format_NV12);

//    cv::Mat tmp(frame.height() + frame.height() / 2, frame.width(), CV_8UC1, (uchar *) frame.bits());
//    cv::Mat result(frame.height(), frame.width(), CV_8UC3);
//    cvtColor(tmp, result, frame.pixelFormat() == QVideoFrame::Format_YUV420P ? CV_YUV2BGR_YV12 : CV_YUV2BGR_NV12);
//    return result;
//}



//cv::Mat QCvDetectFilterRunnable::imageToMat8(const QImage &image)
//{
//    QImage img = image.convertToFormat(QImage::Format_RGB32).rgbSwapped();
//    cv::Mat tmp(img.height(), img.width(), CV_8UC4, (void *) img.bits(), img.bytesPerLine());
//    return tmp.clone();
//}

//cv::Mat yuvFrameToMat8(const QVideoFrame &frame)
//{
//    Q_ASSERT(frame.handleType() == QAbstractVideoBuffer::NoHandle && frame.isReadable());
//    Q_ASSERT(frame.pixelFormat() == QVideoFrame::Format_YUV420P || frame.pixelFormat() == QVideoFrame::Format_NV12);

//    cv::Mat tmp(frame.height() + frame.height() / 2, frame.width(), CV_8UC1, (uchar *) frame.bits());
//    cv::Mat result(frame.height(), frame.width(), CV_8UC3);
//    cvtColor(tmp, result, frame.pixelFormat() == QVideoFrame::Format_YUV420P ? CV_YUV2BGR_YV12 : CV_YUV2BGR_NV12);
//    return result;
//}




//#ifndef QT_NO_OPENGL
//class TextureBuffer : public QAbstractVideoBuffer
//{
//public:
//    TextureBuffer(uint id) : QAbstractVideoBuffer(GLTextureHandle), m_id(id) { }
//    MapMode mapMode() const { return NotMapped; }
//    uchar *map(MapMode, int *, int *) { return 0; }
//    void unmap() { }
//    QVariant handle() const { return QVariant::fromValue<uint>(m_id); }

//private:
//    GLuint m_id;
//};
//#endif // QT_NO_OPENGL

///*
//  Creates and returns a new video frame wrapping the OpenGL texture textureId. The size
//  must be passed in size, together with the format of the underlying image data in
//  format. When the texture originates from a QImage, use
//  QVideoFrame::imageFormatFromPixelFormat() to get a suitable format. Ownership is not
//  altered, the new QVideoFrame will not destroy the texture.
//*/
//QVideoFrame frameFromTexture(uint textureId, const QSize &size, QVideoFrame::PixelFormat format)
//{
//#ifndef QT_NO_OPENGL
//    return QVideoFrame(new TextureBuffer(textureId), size, format);
//#else
//    return QVideoFrame();
//#endif // QT_NO_OPENGL
//}

