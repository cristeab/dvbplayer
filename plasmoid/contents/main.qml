import QtQuick 1.1
import QtProcess 0.1
import org.kde.plasma.core 0.1 as PlasmaCore

Item {
  id: rootItem
  width: 320
  height: 5*(listView.currentItem.height+listView.spacing)-listView.spacing

  property int minimumWidth: width
  property int minimumHeight: height
  property int oldIndex: -1

  PlasmaCore.Theme {
    id: theme
  }

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

  //highligh component
   Component {
     id: highlightBar
     Rectangle {
       width: listView.currentItem.width
       color: theme.highlightColor
       y: listView.currentItem.y;
       Behavior on y {
         SpringAnimation { spring: 2; damping: 0.1 }
       }
     }
   }

  //channel list
  ListView {
    id: listView
    anchors.fill: parent
    highlight: highlightBar
    highlightFollowsCurrentItem: true
    highlightMoveSpeed: 2000
    // concreate model
    model: mplayer.channels
    // provide delegate component.
    delegate: Text {
                id: channelItem
                font.pixelSize: 30
                color: theme.textColor
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
                    } else {
                      oldIndex = -1
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
