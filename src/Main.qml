import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Shapes
import QuickRays3
import QtActionStore

Window {
    width: 1600
    height: 900
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

    ActionStore {
        id: actionStore
        
        InputAction {
            title: "MoveForward"
            JoyAxisEvent {
                axis: JoyAxisEvent.LeftY
                direction: JoyAxisEvent.Up
                minVal: 0.5
            }
        }

        InputAction {
            title: "MoveBackward"
            JoyAxisEvent {
                axis: JoyAxisEvent.LeftY
                direction: JoyAxisEvent.Down
                minVal: 0.5
            }
        }

        InputAction {
            title: "MoveLeft"
            JoyAxisEvent {
                axis: JoyAxisEvent.LeftX
                direction: JoyAxisEvent.Left
                minVal: 0.5
            }
        }

        InputAction {
            title: "MoveRight"
            JoyAxisEvent {
                axis: JoyAxisEvent.LeftX
                direction: JoyAxisEvent.Right
                minVal: 0.5
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
        }

        InputAction {
            title: "LookUp"
            JoyAxisEvent {
                axis: JoyAxisEvent.RightY
                direction: JoyAxisEvent.Up
                minVal: 0.5
            }
        }

        InputAction {
            title: "LookDown"
            JoyAxisEvent {
                axis: JoyAxisEvent.RightY
                direction: JoyAxisEvent.Down
                minVal: 0.5
            }
        }

        InputAction {
            title: "LookLeft"
            JoyAxisEvent {
                axis: JoyAxisEvent.RightX
                direction: JoyAxisEvent.Left
                minVal: 0.5
            }
        }

        InputAction {
            title: "LookRight"
            JoyAxisEvent {
                axis: JoyAxisEvent.RightX
                direction: JoyAxisEvent.Right
                minVal: 0.5
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
        }

        onActionEvent: action => {
            renderer.camera.handleActionTriggered(action)
        }
    }
}
