import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Shapes
import QuickRays3

Window {
    width: 1920
    height: 1080
    visible: true
    title: qsTr("Hello World")
    color: "black"

    RowLayout {
        anchors.fill: parent
        JohanRenderer {
            id: renderer
            Layout.fillHeight: true
            Layout.fillWidth: true

            onRenderTimeChanged: {
                renderTimeLabel.text = "Render time " + renderer.renderTime + "ms"
            }
        }

        ColumnLayout {
            Layout.preferredWidth: 300
            Layout.fillHeight: true

            Label {
                text: "Properties"
                font.pixelSize: 20
            }

            Label {
                id: renderTimeLabel
            }

            Button {
                text: "Render"
                onPressed: {
                    renderer.render()
                }
            }
        }
    }

}
