import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

ApplicationWindow {
    visible: true
    width: 600
    height: 400
    title: qsTr("Game Center Dev")

    // this way window will not vanish and re-appear
    // cannot use ApplicaitonWindow in MainWindow.qml
    Loader {
        anchors.fill: parent
        source: "qrc:/MainWindow.qml"
        objectName: "loader"
        active: true
    }
}
