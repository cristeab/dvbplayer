import QtQuick 1.1
import QtProcess 0.1
import org.kde.plasma.core 0.1 as PlasmaCore

Item {
  id: rootItem

  property int oldIndex: -1

  PlasmaCore.Theme {
    id: theme
  }

  //create process element
  Process {
    id: mplayer
    program: "mplayer"
    onReadyReadStandardError: {
      //console.log(readAllStandardError())
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
       height: listView.currentItem.height
       color: theme.highlightColor
       y: listView.currentItem.y;
       Behavior on y {
         SpringAnimation { spring: 2; damping: 0.1 }
       }
     }
   }
   Component {
    id: emptyHighlightBar
    Rectangle {
      width: listView.currentItem.width
      height: listView.currentItem.height
      color: theme.viewBackgroundColor
    }
   }

  //channel list
  ListView {
    id: listView
    anchors.fill: parent
    highlightFollowsCurrentItem: true
    highlightMoveSpeed: 2000
    // concreate model
    model: mplayer.channels
    // provide delegate component.
    delegate: Text {
                id: channelItem
                font.pixelSize: 24
                color: theme.textColor
                // delegate can direclty use ListElement role name
                text: modelData
                MouseArea {
                  anchors.fill: parent
                  onDoubleClicked: {
                    mplayer.kill()
                    if (oldIndex != index) {
                      listView.highlight = highlightBar
                      listView.currentIndex = index
                      mplayer.arguments = ["-ao", "sdl", "dvb://"+channelItem.text]
                      mplayer.start()
                      oldIndex = index
                    } else {
                      listView.highlight = emptyHighlightBar
                      oldIndex = -1
                    }
                  }
                }
              }
    spacing: 4
    snapMode: ListView.SnapToItem
    focus: true
    keyNavigationWraps: true
    clip: true
  }
}
