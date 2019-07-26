#ifndef CAMERAACCESSMANAGER_H
#define CAMERAACCESSMANAGER_H

#include <QObject>

class VideoCapture;

class CameraAccessManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(VideoCapture* videoCapture READ videoCapture CONSTANT)
public:
    explicit CameraAccessManager(QObject* parent = nullptr);

    VideoCapture* videoCapture() const { return _videoCapture; }

private:
    VideoCapture* _videoCapture;
};

#endif // CAMERAACCESSMANAGER_H
