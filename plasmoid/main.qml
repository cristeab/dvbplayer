import QtQuick 1.1
import QtProcess 0.1

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
  //create process element
  Process {
    id: mplayer
    program: "mplayer"
    onReadyReadStandardError: {
      console.log(readAllStandardError())
    }
  }
  ListView {
    id: sampleListView
    anchors.fill: parent
    highlight: Rectangle {
                color: "lightgray"
                radius: 5
                width: sampleListView.currentItem.width
               }
    focus: false
    // concreate model
    model: mplayer.channels
    // provide delegate component.
    delegate: Text {
                id: channelItem
                font.pixelSize: 40
                // delegate can direclty use ListElement role name
                text: modelData
                MouseArea {
                  anchors.fill: parent
                  onDoubleClicked: {
                    sampleListView.currentIndex = index
                    mplayer.arguments = ["-ao", "sdl", "dvb://"+channelItem.text]
                    mplayer.kill()
                    mplayer.start()
                  }
                }
              }
    spacing: 4
  }
}
