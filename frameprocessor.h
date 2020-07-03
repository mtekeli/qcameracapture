#ifndef FRAMEPROCESSOR_H
#define FRAMEPROCESSOR_H

#include <QObject>
#include <QTimer>
#include <QVideoFrame>

class FrameProcessor : public QObject
{
	Q_OBJECT
public:
	FrameProcessor(QObject* parent = nullptr);

public slots:
	void updateFrame(const QVideoFrame& newFrame);

private slots:
	void process();

private:
	QVideoFrame _lastFrame;
	QTimer _processTimer;
};

#endif // FRAMEPROCESSOR_H
