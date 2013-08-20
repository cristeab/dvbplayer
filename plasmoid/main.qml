import QtQuick 1.1
Item {
  id: rootItem
  width: 640
  height: 480
  // create a model item instance
  ListModel {
    id: listModel
    ListElement { channelName: "France 2"}
    ListElement { channelName: "France 3"}
    ListElement { channelName: "France 4"}
    ListElement { channelName: "France 5"}
    ListElement { channelName: "France "}
    ListElement { channelName: "Gulli"}
    ListElement { channelName: "HD1"}
    ListElement { channelName: "IDF1"}
    ListElement { channelName: "L'Equipe 21"}
    ListElement { channelName: "LCP"}
    ListElement { channelName: "M6"}
    ListElement { channelName: "M6HD"}
    ListElement { channelName: "MCS"}
  }
  ListView {
    id: sampleListView
    anchors.fill: parent
    highlight: Rectangle {
                color: "lightgray"
                radius: 5
                width: sampleListView.currentItem.width
               }
    focus: true
    // concreate model
    model: listModel
    // provide delegate component.
    delegate: Text {
                id: itexItem
                font.pixelSize: 40
                // delegate can direclty use ListElement role name
                text: channelName
              }
    spacing: 4
  }
}
