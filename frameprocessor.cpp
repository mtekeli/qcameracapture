#include "frameprocessor.h"
#include <QDebug>
#include <QThread>

struct FrameMapper
{
	QVideoFrame vf;

	FrameMapper(QVideoFrame& frame) : vf(frame)
	{
		if (!vf.map(QAbstractVideoBuffer::MapMode::ReadOnly))
			throw std::runtime_error("failed to map QVideoFrame");
		if (!vf.mappedBytes())
			throw std::runtime_error("received frame with no data");
	};
};

FrameProcessor::FrameProcessor(QObject* parent) : QObject{parent}
{
	_processTimer.setInterval(1000);
	connect(&_processTimer, &QTimer::timeout, this, &FrameProcessor::process);
	_processTimer.start();
}

void FrameProcessor::updateFrame(const QVideoFrame& newFrame) { _lastFrame = newFrame; }

void FrameProcessor::process()
{
	try
	{
		if (!_lastFrame.isValid())
			return;

		auto copy = _lastFrame;
		FrameMapper fp{copy};
		// process
	}
	catch (std::exception& e)
	{
		qDebug() << e.what();
	}
}
