import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtMultimedia 5.8
import myextension 1.0

Rectangle {
    id: main
    visible: true
    width: 1280
    height: 800

    OpenVidCap {
        id: vidCap
        width: 800
        height: 480
        anchors.top: parent.top
        anchors.left: parent.left
    }

    QtCvSlider {
        id: thresh
        anchors.bottom: maxthresh.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.margins: 20
        width: parent.width * .8
        height: 50
        showUpDownArrows: false
        propName: "Threshold: "
        floatingPointPrecision: false
        slideStep: 1
        minVal: 0
        maxVal: 255
        currentVal: vidCap.threshold
        onValChanged: vidCap.setThreshold(val)
    }


    QtCvSlider {
        id: maxthresh
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width * .8
        height: 50
        showUpDownArrows: false
        propName: "Max Threshold: "
        floatingPointPrecision: false
        slideStep: 1
        minVal: 0
        maxVal: 255
        currentVal: vidCap.maxThresh
        onValChanged: vidCap.setMaxThresh(val)
    }

    QtCvSlider {
        id: type
        anchors.bottom: thresh.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.margins: 20
        width: parent.width * .8
        height: 50
        showUpDownArrows: false
        propName: "Threshold Type: "
        floatingPointPrecision: false
        slideStep: 1
        minVal: 0
        maxVal: 4
        visible: !canny.checked
        currentVal: vidCap.thresholdType
        onValChanged: vidCap.setThresholdType(val)
    }


    QtCvSlider {
        id: blurSize
        anchors.bottom: type.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.margins: 20
        width: parent.width * .8
        height: 50
        showUpDownArrows: false
        propName: "Blur Size: "
        visible: blur.checked
        floatingPointPrecision: false
        slideStep: 1
        minVal: 0
        maxVal: 50
        currentVal: vidCap.blurSize
        onValChanged: {
            if(val % 2 == 1)
            {
                vidCap.setBlurSize(val)
            }
        }
    }


    Column {
        spacing: 10
        anchors.right: parent.right
        anchors.top: parent.top

        QtCvButton {
            id: canny
            width: 200
            height: 140
            backColor: "blue"
            buttonText: qsTr("Canny")
            foreColor: "green"
            checkable: true
            checked: vidCap.useCanny
            onClicked: {
                vidCap.setUseCanny(canny.checked)
            }
        }


        QtCvButton {
            id: blur
            width: 200
            height: 140
            backColor: "blue"
            buttonText: qsTr("Gau Blur")
            foreColor: "green"
            checkable: true
            checked: vidCap.useBlur
            onClicked: {
                vidCap.setUseBlur(blur.checked)
            }
        }

        QtCvButton {
            id: otsu
            width: 200
            height: 140
            backColor: "blue"
            buttonText: qsTr("Otsu")
            foreColor: "green"
            checkable: true
            checked: vidCap.useOtsu
            visible: !canny.checked
            onClicked: {
                tri.checked = false;
                vidCap.setUseTri(false)
                vidCap.setUseOtsu(otsu.checked)
            }
        }


        QtCvButton {
            id: tri
            width: 200
            height: 140
            backColor: "blue"
            buttonText: qsTr("Tri")
            foreColor: "green"
            checkable: true
            checked: vidCap.useTri
            visible: !canny.checked
            onClicked: {
                otsu.checked = false;
                vidCap.setUseOtsu(false)
                vidCap.setUseTri(tri.checked)
            }
        }
    }




}
