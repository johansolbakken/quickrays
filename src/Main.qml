import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Shapes
import QuickRays3

Window {
    width: 800
    height: 400
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
                renderTimeLabel.text = "Render time " + renderer.renderTime + "ms (" + Math.floor(10000 / renderer.renderTime)/10 + "fps)"
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

            CheckBox {
                text: "Auto render"
                checked: false
                onCheckedChanged: {
                    renderer.autoRender = checked
                    if (checked) {
                        renderer.render()
                    }
                }
            }
        }
    }
}
