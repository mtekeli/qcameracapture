#include "camerahandler.h"

#include <QDebug>
#include <stdexcept>

CameraHandler::CameraHandler(const QCameraInfo& cameraInfo, QObject* parent)
    : QAbstractVideoSurface{parent}, _cameraInfo{cameraInfo}
{
	if (_cameraInfo.isNull())
		throw std::runtime_error("invalid cameraInfo given to CameraHandler");

	_camera = new QCamera{_cameraInfo, this};
	_camera->setViewfinder(this);
	connect(_camera, &QCamera::stateChanged, this, &CameraHandler::onCameraStateChanged);
	connect(_camera, &QCamera::statusChanged, this, &CameraHandler::onCameraStatusChanged);

	_camera->load();
	_camera->start();
}

CameraHandler::~CameraHandler() { qDebug() << "releasing camera handler"; }

bool CameraHandler::present(const QVideoFrame& frame)
{
	qDebug() << "frame received size:" << frame.size() << " format:" << frame.pixelFormat();

	emit frameReceived(frame, {});

	return true;
}

QList<QVideoFrame::PixelFormat> CameraHandler::supportedPixelFormats(QAbstractVideoBuffer::HandleType) const
{
	return {QVideoFrame::Format_YUV420P, QVideoFrame::Format_NV12, QVideoFrame::Format_YUYV, QVideoFrame::Format_RGB32,
	        QVideoFrame::Format_ARGB32};
}

void CameraHandler::onCameraStateChanged(const QCamera::State state)
{
	qDebug() << "camera state changed to " << state;
}

void CameraHandler::onCameraStatusChanged(const QCamera::Status status)
{
	qDebug() << "camera status changed to " << status;

	Q_ASSERT(_camera);

	if (status != QCamera::LoadedStatus)
		return;

	auto isSettingSet = false;

	for (const auto& setting : _camera->supportedViewfinderSettings())
	{
		qDebug() << "camera discovered setting"
		         << "maxFPS=" << setting.maximumFrameRate() << "minFPS=" << setting.minimumFrameRate()
		         << "aspect=" << setting.pixelAspectRatio() << "pf=" << setting.pixelFormat()
		         << "resolution=" << setting.resolution() << "state:" << _camera->state()
		         << "deviceName=" << _cameraInfo.description();

		if (!isSettingSet && _camera->viewfinderSettings() != setting && setting.resolution().width() == 640 &&
		    static_cast<int>(setting.maximumFrameRate()) == 30)
		{
			_camera->setViewfinderSettings(setting);
			isSettingSet = true;
			qDebug() << "camera setting was set";
		}
	}

	if (!isSettingSet)
		qWarning() << "unable to set the camera setting, will be using default";
}
