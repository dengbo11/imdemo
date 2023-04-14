import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    flags: Qt.Tool | Qt.FramelessWindowHint | Qt.WindowStaysOnTopHint

    x: kimpanel.pos.x
    y: kimpanel.pos.y
    width: 640
    height: 40
    visible: true
    title: qsTr("Hello World")

    Flow {
        Repeater{
            model: kimpanel.lookupTable
            delegate: Row {
                Text {
                    id: label
                    text: modelData.label
                }
                Text {
                    id: text
                    text: modelData.text
                }
                Text {
                    id: attr
                    text: modelData.attr
                }
            }
        }
    }
}
