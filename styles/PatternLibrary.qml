pragma Singleton
import QtQuick 2.0

Item {
    //  Imported as UIlib via the qmldir file
    //  Usage:   width: StyleLib.borderWidth

    //  Load the fonts globally
    FontLoader { id: openSansRegular; source: "qrc:/Fonts/OpenSans-Regular.ttf" }

    //  Fonts
    property string defaultFont: openSansRegular.name
    property int textFontSize: 35
    property int borderWidth: 3
    property color textColor: "#CF7F00"
    property color statusTextColor: "orange"

    property color materialDarkBackground : "#343b34"
    property color lightMatDarkBackground: "#795548"
    property color opaqueMaterialDarkBackground : "#30343b34"

    property color accessibleHighlightColor: "#0058e8"
    //property color accessibleHighlightColor: "forestgreen"
    property color accessibleLowlightColor: "#276cdb"
    //property color accessibleLowlightColor: "firebrick"
    property color buttonBorderColor: "#757575"   //25% opacity
    property color disabledButtonBorderColor: "#757575"   //10% opacity
    //property color buttonBgColor: "forestgreen"
    property color buttonBgColor: "#dddddd"
    property color buttonBgPressedColor: "#30ffffff"    //20% opacity
    property color buttonActiveBgColor: Qt.rgba(222/255, 105/255, 50/255, 1)
    property color buttonActiveBorderColor: "#773F2A"
    property color circleButtonBgColor: "#a3a3a3"

}
