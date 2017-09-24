import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import qmllive.logger 1.0 as MyLog

ApplicationWindow {
    visible: true
    width: 600
    height: 400
    title: qsTr("Game Center Dev")

    property alias headerItemAlias: header.item
    property alias contentItemAlias: content.item

    header: Loader {
        id: header
        source: "HeaderComponent.qml"
        objectName: "header"
        active: true
        Binding {
            target: contentItemAlias
            property: 'currentIndex'
            // ensure the current status is not null
            value: if (header.status == Loader.Ready) header.item.currentIndex
            // the content is ready
            when: content.status === Loader.Ready
        }
    }

    Loader {
        id: content
        anchors.fill: parent
        source: "ContentComponent.qml"
        objectName: "content"
        active: true
        Binding {
            target: headerItemAlias
            property: 'currentIndex'
            value: if (content.status == Loader.Ready) content.item.currentIndex
            when: header.status === Loader.Ready
        }
    }

    FocusScope{
        focus: false
        enabled: false
        width: parent.width
        height: parent.height
        // http://doc.qt.io/qt-5/qml-qtquick-textedit.html
        // For example, to add flickable scrolling that follows the cursor:
        Flickable {
            id: flickable
            width: parent.width
            height: parent.height
            contentWidth: logcurtain.paintedWidth
            contentHeight: logcurtain.paintedHeight
            function ensureVisible(r)
            {
                if (contentX >= r.x)
                    contentX = r.x;
                else if (contentX + width <= r.x + r.width)
                    contentX = r.x + r.width - width;
                if (contentY >= r.y)
                    contentY = r.y;
                else if (contentY + height <= r.y + r.height)
                    contentY = r.y + r.height - height;
            }
            TextEdit {
                id:logcurtain
                width: flickable.width
                height: flickable.height
                opacity: 0.4
                focus: false
                activeFocusOnPress: false
                cursorVisible: false
                readOnly: true
                wrapMode: TextEdit.WordWrap
                visible: false // default is invisible
                Connections {
                    target: MyLog.Logger
                    onMessage: logcurtain.append(msg)
                }
                onCursorRectangleChanged: flickable.ensureVisible(cursorRectangle)
            }
        }
    }

    Shortcut {
        sequence: "Ctrl+L"
        onActivated: logcurtain.clear()
    }

    Shortcut {
        sequence: "Ctrl+M"
        onActivated: {
            logcurtain.visible = !logcurtain.visible
        }
    }
}
