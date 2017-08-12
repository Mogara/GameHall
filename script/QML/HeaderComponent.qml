import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

TabBar {
    id: tabBar
    //on the top level of the component code, there shouldn't be anything related to parent. Use QtQuick.Layout to avoid it.
//    contentWidth: parent.width
//    anchors.bottom: parent.bottom
    // we will bind this property in the Loader
//    currentIndex: swipeView.currentIndex
    TabButton {
        text: qsTr("First333")
    }
    TabButton {
        text: qsTr("Second222")
    }
}
