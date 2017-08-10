import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

Item {
    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex
        Page {
            Label {
                text: qsTr("Second page")
                anchors.centerIn: parent
            }
        }

        Page1 {
        }
    }

    TabBar {
        id: tabBar
        contentWidth: parent.width
        anchors.bottom: parent.bottom
        currentIndex: swipeView.currentIndex
        TabButton {
            text: qsTr("First")
        }
        TabButton {
            text: qsTr("Second")
        }
    }
}
