import QtQuick 2.12
import QtMultimedia 5.12
import QtQuick.Window 2.12

Window {
    id: root

    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    VideoOutput {
        anchors.fill: parent
        fillMode: VideoOutput.PreserveAspectFit
        source: cameraAccessManager.videoCapture
    }
}
