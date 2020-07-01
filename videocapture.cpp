#include "videocapture.h"
#include <QAbstractVideoSurface>
#include <QDebug>

VideoCapture::VideoCapture(QObject* parent) : QObject{parent} {}

void VideoCapture::setVideoSurface(QAbstractVideoSurface* surface)
{
	if (_surface == surface)
		return;

	if (_surface && _surface->isActive())
		_surface->stop();

	_surface = surface;

	if (_surface && !_surface->isActive())
		_surface->start(_surfaceFormat);

	connect(_surface, &QObject::destroyed, this, &VideoCapture::surfaceDestroyed);

	qDebug() << "video surface set"
	         << "format=" << _surface->surfaceFormat() << ",active=" << (_surface->isActive() ? "true" : "false");
}

void VideoCapture::surfaceDestroyed() { qDebug() << "surface destroyed"; }

void VideoCapture::onFrameReceived(const QVideoFrame& frame)
{
	if (!_surface)
		return;

	if (!_surfaceFormat.isValid())
		return;

	//const auto surfaceFormat = QVideoSurfaceFormat{frame.size(), frame.pixelFormat()};

	if (!_surface->isActive() && !_surface->start(_surfaceFormat))
	{
		qWarning() << "surface start failed format:" << _surfaceFormat;
	}

	_surface->present(frame);
}

void VideoCapture::setSurfaceFormat(const QVideoSurfaceFormat& surfaceFormat)
{
	if (_surfaceFormat == surfaceFormat)
		return;

	_surfaceFormat = surfaceFormat;
	qDebug() << "surface format set " << surfaceFormat;
}
