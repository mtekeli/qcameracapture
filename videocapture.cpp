#include "videocapture.h"
#include <QAbstractVideoSurface>
#include <QDebug>
#include <QVideoSurfaceFormat>

VideoCapture::VideoCapture(QObject *parent) : QObject{parent} {}

void VideoCapture::setVideoSurface(QAbstractVideoSurface *surface) {
  if (!surface)
    return;

  _surface = surface;
  connect(_surface, &QObject::destroyed, this, &VideoCapture::surfaceDestroyed);

  //    qDebug() << "video surface set"
  //             << "format=" << _surface->surfaceFormat() << ",active=" <<
  //             (_surface->isActive() ? "true" : "false");
}

void VideoCapture::surfaceDestroyed() { qDebug() << "surface destroyed"; }

void VideoCapture::onFrameReceived(const QVideoFrame &frame) {
  if (!_surface)
    return;

  const auto surfaceFormat =
      QVideoSurfaceFormat{frame.size(), frame.pixelFormat()};

  if (!_surface->isActive() && !_surface->start(surfaceFormat)) {
    qWarning() << "surface start failed format:" << surfaceFormat;
  }

  _surface->present(frame);
}
