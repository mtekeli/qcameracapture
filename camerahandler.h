#ifndef CAMERAHANDLER_H
#define CAMERAHANDLER_H

#include <QAbstractVideoSurface>
#include <QCameraInfo>

class CameraHandler : public QAbstractVideoSurface
{
	Q_OBJECT
public:
	CameraHandler(const QCameraInfo& cameraInfo, QObject* parent = nullptr);
	~CameraHandler();

	// QAbstractVideoSurface interface
	bool present(const QVideoFrame& frame) override;
	QList<QVideoFrame::PixelFormat> supportedPixelFormats(QAbstractVideoBuffer::HandleType) const override;

signals:
	void frameReceived(const QVideoFrame& frame, QPrivateSignal);

private slots:
	void onCameraStateChanged(const QCamera::State state);
	void onCameraStatusChanged(const QCamera::Status status);

private:
	QSize _preferredResolution;
	QCamera* _camera = nullptr;
	QCameraInfo _cameraInfo;
};

#endif // CAMERAHANDLER_H
