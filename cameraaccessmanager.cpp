#include "cameraaccessmanager.h"
#include "camerahandler.h"
#include "videocapture.h"

#include <QCameraInfo>

CameraAccessManager::CameraAccessManager(QObject* parent) : QObject{parent}
{
	qRegisterMetaType<VideoCapture*>("VideoCapture*");

	const auto cameras = QCameraInfo::availableCameras();

	if (!cameras.isEmpty())
	{
		const auto cameraInfo    = cameras.at(0);
		const auto cameraHandler = new CameraHandler{cameraInfo, this};

		_videoCapture = new VideoCapture{this};

		connect(cameraHandler, &CameraHandler::frameReceived, _videoCapture, &VideoCapture::onFrameReceived);
		connect(cameraHandler, &CameraHandler::frameReceived, this, &CameraAccessManager::onNewFrame);
		connect(cameraHandler, &CameraHandler::surfaceFormatChanged, _videoCapture, &VideoCapture::setSurfaceFormat);
	}
}
