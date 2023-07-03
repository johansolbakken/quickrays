import QtQuick
import QtActionStore
import QuickRays3

/* Handles actions */

ActionDispatch {
    property Camera camera

    ActionHandler {
        actionTitle: "MoveForward"
        onHandle: {
            camera.setWalkYDirection(Camera.Forward)
        }
    }

    ActionHandler {
        actionTitle: "MoveBackward"
        onHandle: {
            camera.setWalkYDirection(Camera.Backward)
        }
    }

    ActionHandler {
        actionTitle: "MoveLeft"
        onHandle: {
            camera.setWalkXDirection(Camera.Left)
        }
    }

    ActionHandler {
        actionTitle: "MoveRight"
        onHandle: {
            camera.setWalkXDirection(Camera.Right)
        }
    }

    ActionHandler {
        actionTitle: "MoveStopX"
        onHandle: {
            camera.setWalkXDirection(Camera.None)
        }
    }

    ActionHandler {
        actionTitle: "MoveStopY"
        onHandle: {
            camera.setWalkYDirection(Camera.None)
        }
    }

    ActionHandler {
        actionTitle: "LookUp"
        onHandle: {
            camera.setLookYDirection(Camera.Forward)
        }
    }

    ActionHandler {
        actionTitle: "LookDown"
        onHandle: {
            camera.setLookYDirection(Camera.Backward)
        }
    }

    ActionHandler {
        actionTitle: "LookLeft"
        onHandle: {
            camera.setLookXDirection(Camera.Left)
        }
    }

    ActionHandler {
        actionTitle: "LookRight"
        onHandle: {
            camera.setLookXDirection(Camera.Right)
        }
    }

    ActionHandler {
        actionTitle: "LookStopX"
        onHandle: {
            camera.setLookXDirection(Camera.None)
        }
    }

    ActionHandler {
        actionTitle: "LookStopY"
        onHandle: {
            camera.setLookYDirection(Camera.None)
        }
    }
}