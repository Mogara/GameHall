import QtQuick 2.7
import qmllive.logger 1.0 as Logger


// http://doc.qt.io/qt-5/qml-qtquick-textedit.html
// For example, to add flickable scrolling that follows the cursor:
Flickable { // This is used to let the textedit be scrollable
    id: flickable

    property alias show: consoleText.visible
    property var clearlog: consoleText.clear

    enabled: false
    width: parent.width
    height: parent.height
    contentWidth: consoleText.paintedWidth
    contentHeight: consoleText.paintedHeight
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
    TextEdit { // By making use of this component's append method, we can easily record log
        id: consoleText
        width: flickable.width
        height: flickable.height
        opacity: 0.4
        focus: false
        enabled: false
        activeFocusOnPress: false
        cursorVisible: false
        readOnly: true
        wrapMode: TextEdit.Wrap
        textFormat: TextEdit.AutoText // enable richtext if possible
        visible: false // default is invisible
        Connections {
            target: Logger.Logger
            onMessage: consoleText.append("<b>" + msg + "</b>")
        }
        onCursorRectangleChanged: flickable.ensureVisible(cursorRectangle)
    }
}
