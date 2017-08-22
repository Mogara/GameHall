import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

TabBar {
    id: tabBar
    // if you want to bind the property to parent just use the Loader id instead of parent.XXX
    contentWidth: header.width
    anchors.bottom: header.bottom
    TabButton {
        text: qsTr("First")
    }
    TabButton {
        text: qsTr("Second")
    }
}
