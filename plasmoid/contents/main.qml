import QtQuick 1.1
import QtProcess 0.1

Item {
  id: rootItem
  width: 320
  height: 5*(listView.currentItem.height+listView.spacing)-listView.spacing

  property int oldIndex: -1

  //create process element
  Process {
    id: mplayer
    program: "mplayer"
    onReadyReadStandardError: {
      console.log(readAllStandardError())
    }
    onReadyReadStandardOutput: {
      //console.log(readAllStandardOutput())
    }
  }
  ListView {
    id: listView
    anchors.fill: parent
    highlight: Rectangle {
                color: "lightgray"
                radius: 5
                width: listView.currentItem.width
              }
    highlightFollowsCurrentItem: true
    highlightMoveSpeed: 2000
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
                    mplayer.kill()
                    if (oldIndex != index) {
                      listView.currentIndex = index
                      mplayer.arguments = ["-ao", "sdl", "dvb://"+channelItem.text]
                      mplayer.start()
                      oldIndex = index
                    }
                  }
                }
              }
    spacing: 4
    snapMode: ListView.SnapToItem
    focus: true
    keyNavigationWraps: true
  }
}