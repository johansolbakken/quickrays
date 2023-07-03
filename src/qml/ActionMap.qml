import QtQuick
import QtActionStore

/* Defines all actions */

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
}