import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Shapes
import QuickRays3
import QtActionStore

Window {
    width: 1000
    height: 600
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
                renderTimeLabel.text = "Render time " + renderer.renderTime + "ms (" + Math.floor(
                            10000 / renderer.renderTime) / 10 + "fps)"
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
                checked: true
                onCheckedChanged: {
                    renderer.autoRender = checked
                    if (checked) {
                        renderer.render()
                    }
                }
            }

            CheckBox {
                text: "Accumulate"
                checked: true
                onCheckedChanged: {
                    renderer.accumulate = checked
                }
            }


            CheckBox {
                text: "Multi-threaded"
                checked: false
                onCheckedChanged: {
                    renderer.multiThreaded = checked
                }
            }

            Label {
                id: bounceLabel
                text: "Bounces: " + bouncesSlider.value
            }
            Slider {
                id: bouncesSlider
                from: 0
                to: 10
                stepSize: 1
                value: renderer.bounces
                onValueChanged: {
                    renderer.bounces = value
                    bounceLabel.text = "Bounces: " + value
                }
            }


            Label {
                text: "Spheres"
                font.pixelSize: 16
            }
        }
    }

    /* Actions */

    ActionMap {
        id: actionStore
    }

    ActionHandlers {
        actionStore: actionStore
        camera: renderer.camera
    }

    ActionStoreEventListener {
        actionStores: [actionStore]
        focus: true
    }
}
