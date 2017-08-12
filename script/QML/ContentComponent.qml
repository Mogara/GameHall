import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

Item {
    // don't forget to expose the internal property using alias if you want you use it as a component
    property alias currentIndex: swipeView.currentIndex
    SwipeView {
        id: swipeView
        anchors.fill: parent
        Page {
            Label {
                text: qsTr("Second page")
                anchors.centerIn: parent
            }
            Test {

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
