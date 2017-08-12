import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

Item {
    property alias currentIndex: swipeView.currentIndex
    SwipeView {
        id: swipeView
        anchors.fill: parent
        // we will bind this property in the Loader
//        currentIndex: tabBar.currentIndex
        Page {
            Label {
                text: qsTr("Secondpage")
                anchors.centerIn: parent
            }
        }

        Page {
            Button {
                onClicked: popup.open()
                Popup {
                    id: popup
                    parent: ApplicationWindow.overlay
                    x: (parent.width - width) / 2
                    y: (parent.height - height) / 2
                    width: 50
                    height: 50
                }
            }
        }
    }
}
