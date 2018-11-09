import QtQuick 2.0
import QtQuick.Templates 2.0 as QQT2
import QtGraphicalEffects 1.0
import "styles"

QQT2.Button {
 id: root

 property string buttonText: "Button Text"
 property color backColor: StyleLib.circleButtonBgColor
 property color foreColor: StyleLib.textActiveColor

 signal simClicked()

 function pulse()
 {
     pulseAnim.start()
 }

 Connections {
     target: root
     onClicked: pulseAnim.start()
 }

 indicator: Rectangle {
     id: rect
     implicitWidth: root.width
     implicitHeight: root.height
     radius: 5
     color:  root.checked || root.pressed ? StyleLib.lightMatDarkBackground : backColor
     border.width: 0

     SequentialAnimation {
         id: pulseAnim
         running: false
         loops: 1
         NumberAnimation { target: rect; property: "opacity"; from: 1.0; to: .7; duration: 100}
         NumberAnimation { target: rect; property: "opacity"; from: 0.7; to: 1.0; duration: 100}
         NumberAnimation { target: rect; property: "opacity"; from: 1.0; to: .7; duration: 100}
         NumberAnimation { target: rect; property: "opacity"; from: 0.7; to: 1.0; duration: 100}
     }

     Text {
         id: text
         anchors.horizontalCenter: parent.horizontalCenter
         anchors.verticalCenter: parent.verticalCenter
         text: buttonText
         font.family: StyleLib.defaultFont
         font.pixelSize: 35
         font.bold: true
         color: root.enabled ?
                    (root.checked || root.pressed ? foreColor : "white") : "gray"
     }
 }
}
