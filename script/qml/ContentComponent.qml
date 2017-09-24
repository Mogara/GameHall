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
            TextField {
                id: textField1
                anchors.left: parent.left
                placeholderText: qsTr("Game Hall Dev Text Field")
            }
            Button {
                id: button1
                anchors.right: parent.right
                text: qsTr("Press Me")
                onClicked: {
                    console.log("Button Pressed. Entered text: " + textField1.text);
                }
            }
            Label {
                text: qsTr("First page")
                anchors.centerIn: parent
            }
        }

        Page {
            Button {
                onClicked: {
                    popup.open()
                    console.log("Button clicked")
                }
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
