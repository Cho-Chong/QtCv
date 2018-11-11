QT +=  quick svg gui core qml network charts
CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
    Filters/QcvDetectFilter.cpp \
    cvmatandqimage.cpp

RESOURCES += qml.qrc

INCLUDEPATH += D:\opencv\opencv-3.4.3\opencv-3.4.3\build\install\include \
               .\Filters

HEADERS += D:\opencv\opencv-3.4.3\opencv-3.4.3\build\install\include\opencv2\*.hpp \
           .\Filters/QcvDetectFilter.h \
    openvidcap.h \
    cvmatandqimage.h


# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

LIBS += -LD:/opencv/opencv-3.4.3/opencv-3.4.3/build/install/x64/vc15/lib -lopencv_aruco343d \
-LD:/opencv/opencv-3.4.3/opencv-3.4.3/build/install/x64/vc15/lib -lopencv_aruco343d \
-LD:/opencv/opencv-3.4.3/opencv-3.4.3/build/install/x64/vc15/lib -lopencv_bgsegm343d \
-LD:/opencv/opencv-3.4.3/opencv-3.4.3/build/install/x64/vc15/lib -lopencv_bioinspired343d \
-LD:/opencv/opencv-3.4.3/opencv-3.4.3/build/install/x64/vc15/lib -lopencv_calib3d343d \
-LD:/opencv/opencv-3.4.3/opencv-3.4.3/build/install/x64/vc15/lib -lopencv_ccalib343d \
-LD:/opencv/opencv-3.4.3/opencv-3.4.3/build/install/x64/vc15/lib -lopencv_core343d \
-LD:/opencv/opencv-3.4.3/opencv-3.4.3/build/install/x64/vc15/lib -lopencv_datasets343d \
-LD:/opencv/opencv-3.4.3/opencv-3.4.3/build/install/x64/vc15/lib -lopencv_dnn_objdetect343d \
-LD:/opencv/opencv-3.4.3/opencv-3.4.3/build/install/x64/vc15/lib -lopencv_dnn343d \
-LD:/opencv/opencv-3.4.3/opencv-3.4.3/build/install/x64/vc15/lib -lopencv_dpm343 \
-LD:/opencv/opencv-3.4.3/opencv-3.4.3/build/install/x64/vc15/lib -lopencv_face343d \
-LD:/opencv/opencv-3.4.3/opencv-3.4.3/build/install/x64/vc15/lib -lopencv_features2d343d \
-LD:/opencv/opencv-3.4.3/opencv-3.4.3/build/install/x64/vc15/lib -lopencv_flann343d \
-LD:/opencv/opencv-3.4.3/opencv-3.4.3/build/install/x64/vc15/lib -lopencv_fuzzy343d \
-LD:/opencv/opencv-3.4.3/opencv-3.4.3/build/install/x64/vc15/lib -lopencv_hfs343d \
-LD:/opencv/opencv-3.4.3/opencv-3.4.3/build/install/x64/vc15/lib -lopencv_highgui343d \
-LD:/opencv/opencv-3.4.3/opencv-3.4.3/build/install/x64/vc15/lib -lopencv_img_hash343d \
-LD:/opencv/opencv-3.4.3/opencv-3.4.3/build/install/x64/vc15/lib -lopencv_imgcodecs343d \
-LD:/opencv/opencv-3.4.3/opencv-3.4.3/build/install/x64/vc15/lib -lopencv_imgproc343d \
-LD:/opencv/opencv-3.4.3/opencv-3.4.3/build/install/x64/vc15/lib -lopencv_line_descriptor343d \
-LD:/opencv/opencv-3.4.3/opencv-3.4.3/build/install/x64/vc15/lib -lopencv_ml343d \
-LD:/opencv/opencv-3.4.3/opencv-3.4.3/build/install/x64/vc15/lib -lopencv_objdetect343d \
-LD:/opencv/opencv-3.4.3/opencv-3.4.3/build/install/x64/vc15/lib -lopencv_optflow343d \
-LD:/opencv/opencv-3.4.3/opencv-3.4.3/build/install/x64/vc15/lib -lopencv_phase_unwrapping343d \
-LD:/opencv/opencv-3.4.3/opencv-3.4.3/build/install/x64/vc15/lib -lopencv_photo343d \
-LD:/opencv/opencv-3.4.3/opencv-3.4.3/build/install/x64/vc15/lib -lopencv_plot343d \
-LD:/opencv/opencv-3.4.3/opencv-3.4.3/build/install/x64/vc15/lib -lopencv_reg343d \
-LD:/opencv/opencv-3.4.3/opencv-3.4.3/build/install/x64/vc15/lib -lopencv_rgbd343d \
-LD:/opencv/opencv-3.4.3/opencv-3.4.3/build/install/x64/vc15/lib -lopencv_shape343d \
-LD:/opencv/opencv-3.4.3/opencv-3.4.3/build/install/x64/vc15/lib -lopencv_stereo343d \
-LD:/opencv/opencv-3.4.3/opencv-3.4.3/build/install/x64/vc15/lib -lopencv_stitching343d \
-LD:/opencv/opencv-3.4.3/opencv-3.4.3/build/install/x64/vc15/lib -lopencv_structured_light343d \
-LD:/opencv/opencv-3.4.3/opencv-3.4.3/build/install/x64/vc15/lib -lopencv_superres343d \
-LD:/opencv/opencv-3.4.3/opencv-3.4.3/build/install/x64/vc15/lib -lopencv_surface_matching343d \
-LD:/opencv/opencv-3.4.3/opencv-3.4.3/build/install/x64/vc15/lib -lopencv_text343d \
-LD:/opencv/opencv-3.4.3/opencv-3.4.3/build/install/x64/vc15/lib -lopencv_tracking343d \
-LD:/opencv/opencv-3.4.3/opencv-3.4.3/build/install/x64/vc15/lib -lopencv_video343d \
-LD:/opencv/opencv-3.4.3/opencv-3.4.3/build/install/x64/vc15/lib -lopencv_videoio343d \
-LD:/opencv/opencv-3.4.3/opencv-3.4.3/build/install/x64/vc15/lib -lopencv_videostab343d \
-LD:/opencv/opencv-3.4.3/opencv-3.4.3/build/install/x64/vc15/lib -lopencv_xfeatures2d343d \
-LD:/opencv/opencv-3.4.3/opencv-3.4.3/build/install/x64/vc15/lib -lopencv_ximgproc343d \
-LD:/opencv/opencv-3.4.3/opencv-3.4.3/build/install/x64/vc15/lib -lopencv_xobjdetect343d \
-LD:/opencv/opencv-3.4.3/opencv-3.4.3/build/install/x64/vc15/lib -lopencv_xphoto343d \





# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=
