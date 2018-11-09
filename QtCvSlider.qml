import QtQuick 2.9
import QtQuick.Controls 2.2
import "styles"

Item {
    id: intDelegate

    property string propName : "SLIDER NAME"
    property double minVal: 0
    property double maxVal: 100
    property double currentVal: 50
    property int vertOffset: 5
    property int sliderMargins: 40
    property int textMargin: 5
    property bool floatingPointPrecision: true
    property double slideStep: .1
    property bool isTempDisplay: false
    property bool showUpDownArrows: true
    signal valChanged(double val)

    function updateVal(val)
    {
        currentVal = val;
    }

    function getVal()
    {
        return intSlider.value;
    }

    Slider {
        id: intSlider
        from: minVal
        to: maxVal
        value: currentVal
        stepSize: floatingPointPrecision ? slideStep : Math.round(slideStep)
        snapMode: Slider.SnapAlways
        height: intDelegate.height * 1.5
        width: intDelegate.width * .8
        anchors {
            left: parent.left
            leftMargin: sliderMargins
            rightMargin: sliderMargins
        }

        handle: Rectangle {
            x: intSlider.leftPadding + intSlider.visualPosition * (intSlider.availableWidth - width)
            y: intSlider.topPadding + intSlider.availableHeight / 2 - height / 2
            implicitWidth: 40
            implicitHeight: 20
            radius: 5
            color: StyleLib.materialDarkBackground
        }

        //  background is actually the line the handle slides along.
        background: Rectangle {
            x: intSlider.leftPadding
            y: intSlider.topPadding + intSlider.availableHeight / 2 - height / 2
            implicitWidth: 200
            implicitHeight: StyleLib.borderWidth
            width: intSlider.availableWidth
            height: implicitHeight
            color: StyleLib.buttonBorderColor
        }

        onPressedChanged: {
            if (!pressed) {
                intDelegate.valChanged(value);
            }
        }

        //  Called for each incremental move of the handle
        onVisualPositionChanged: {
            //  Display fixed point divided by 10 with one decimal, integers as is
            if(floatingPointPrecision)
            {
                var val = Math.round(value * 10)
                val = val / 10;
                if(!isTempDisplay)
                {
                    sliderValue.text = val;
                } else {
                    var farenheit = Math.round((val * 1.8 + 32) * 10)
                    farenheit = farenheit / 10;

                    sliderValue.text = val + " °C | " + farenheit + " °F";
                }
            }
            else
            {
                sliderValue.text = Math.round(value);
            }


        }

        onToChanged: {
            if(value > to)
            {
                value = to;
                intDelegate.valChanged(value);

                if(floatingPointPrecision)
                {
                    var val = Math.round(value * 10)
                    val = val / 10;
                    if(!isTempDisplay)
                    {
                        sliderValue.text = val;
                    } else {
                        var farenheit = Math.round((val * 1.8 + 32) * 10)
                        farenheit = farenheit / 10;

                        sliderValue.text = val + " °C | " + farenheit + " °F";
                    }
                }
                else
                {
                    sliderValue.text = Math.round(value);
                }
            }
        }
    }

    Text {
        id: sliderLabel
        text: propName
        anchors.left: decButton.right
        y: vertOffset

        color: StyleLib.textColor
        font.pixelSize: 18
        font.family: StyleLib.defaultFont
    }

    Text {
        id: sliderValue
        //  text: is set by slider onVisualPositionChanged
        color: StyleLib.statusTextColor
        font.pixelSize: 20
        font.bold: true
        font.family: StyleLib.defaultFont
        anchors {
            horizontalCenter: parent.horizontalCenter
            left: sliderLabel.right
            leftMargin: textMargin
            baseline: sliderLabel.baseline
        }
    }


}

