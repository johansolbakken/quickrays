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

    ActionStore {
        id: actionStore
        
        InputAction {
            title: "MoveForward"
            JoyAxisEvent {
                axis: JoyAxisEvent.LeftY
                direction: JoyAxisEvent.Up
                minVal: 0.5
            }
            KeyEvent {
                key: Qt.Key_W
                isPressed: true
            }
        }

        InputAction {
            title: "MoveBackward"
            JoyAxisEvent {
                axis: JoyAxisEvent.LeftY
                direction: JoyAxisEvent.Down
                minVal: 0.5
            }
            KeyEvent {
                key: Qt.Key_S
                isPressed: true
            }
        }

        InputAction {
            title: "MoveLeft"
            JoyAxisEvent {
                axis: JoyAxisEvent.LeftX
                direction: JoyAxisEvent.Left
                minVal: 0.5
            }
            KeyEvent {
                key: Qt.Key_A
                isPressed: true
            }
        }

        InputAction {
            title: "MoveRight"
            JoyAxisEvent {
                axis: JoyAxisEvent.LeftX
                direction: JoyAxisEvent.Right
                minVal: 0.5
            }
            KeyEvent {
                key: Qt.Key_D
                isPressed: true
            }
        }

        InputAction {
            title: "MoveStopX"
            JoyAxisEvent {
                axis: JoyAxisEvent.LeftX
                direction: JoyAxisEvent.Right
                maxVal: 0.5
            }
            JoyAxisEvent {
                axis: JoyAxisEvent.LeftX
                direction: JoyAxisEvent.Left
                maxVal: 0.5
            }
            KeyEvent {
                key: Qt.Key_A
                isPressed: false
            }
            KeyEvent {
                key: Qt.Key_D
                isPressed: false
            }
        }

        InputAction {
            title: "MoveStopY"
            JoyAxisEvent {
                axis: JoyAxisEvent.LeftY
                direction: JoyAxisEvent.Up
                maxVal: 0.5
            }
            JoyAxisEvent {
                axis: JoyAxisEvent.LeftY
                direction: JoyAxisEvent.Down
                maxVal: 0.5
            }
            KeyEvent {
                key: Qt.Key_W
                isPressed: false
            }
            KeyEvent {
                key: Qt.Key_S
                isPressed: false
            }
        }

        InputAction {
            title: "LookUp"
            JoyAxisEvent {
                axis: JoyAxisEvent.RightY
                direction: JoyAxisEvent.Up
                minVal: 0.5
            }
            KeyEvent {
                key: Qt.Key_Up
                isPressed: true
            }
        }

        InputAction {
            title: "LookDown"
            JoyAxisEvent {
                axis: JoyAxisEvent.RightY
                direction: JoyAxisEvent.Down
                minVal: 0.5
            }
            KeyEvent {
                key: Qt.Key_Down
                isPressed: true
            }
        }

        InputAction {
            title: "LookLeft"
            JoyAxisEvent {
                axis: JoyAxisEvent.RightX
                direction: JoyAxisEvent.Left
                minVal: 0.5
            }
            KeyEvent {
                key: Qt.Key_Left
                isPressed: true
            }
        }

        InputAction {
            title: "LookRight"
            JoyAxisEvent {
                axis: JoyAxisEvent.RightX
                direction: JoyAxisEvent.Right
                minVal: 0.5
            }
            KeyEvent {
                key: Qt.Key_Right
                isPressed: true
            }
        }

        InputAction {
            title: "LookStopX"
            JoyAxisEvent {
                axis: JoyAxisEvent.RightX
                direction: JoyAxisEvent.Right
                maxVal: 0.5
            }
            JoyAxisEvent {
                axis: JoyAxisEvent.RightX
                direction: JoyAxisEvent.Left
                maxVal: 0.5
            }
            KeyEvent {
                key: Qt.Key_Left
                isPressed: false
            }
            KeyEvent {
                key: Qt.Key_Right
                isPressed: false
            }
        }

        InputAction {
            title: "LookStopY"
            JoyAxisEvent {
                axis: JoyAxisEvent.RightY
                direction: JoyAxisEvent.Up
                maxVal: 0.5
            }
            JoyAxisEvent {
                axis: JoyAxisEvent.RightY
                direction: JoyAxisEvent.Down
                maxVal: 0.5
            }
            KeyEvent {
                key: Qt.Key_Up
                isPressed: false
            }
            KeyEvent {
                key: Qt.Key_Down
                isPressed: false
            }
        }

        onActionEvent: action => {
            renderer.camera.handleActionTriggered(action)
        }
    }

    ActionStoreEventListener {
        actionStore: actionStore
        focus: true
    }
}
