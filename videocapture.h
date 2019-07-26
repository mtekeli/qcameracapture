#ifndef VIDEOCAPTURE_H
#define VIDEOCAPTURE_H

#include <QObject>

class QVideoFrame;
class QAbstractVideoSurface;

class VideoCapture : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QAbstractVideoSurface* videoSurface READ videoSurface WRITE setVideoSurface)
public:
    VideoCapture(QObject* parent = nullptr);

    QAbstractVideoSurface* videoSurface() const { return nullptr; }
    void setVideoSurface(QAbstractVideoSurface* surface);

public slots:
    void onFrameReceived(const QVideoFrame& frame);

private slots:
    void surfaceDestroyed();

private:
    QAbstractVideoSurface* _surface = nullptr;
};

#endif // VIDEOCAPTURE_H
