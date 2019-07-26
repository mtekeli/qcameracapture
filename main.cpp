#include <QDateTime>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <QImage>

#include "cameraaccessmanager.h"

void myMessageOutput(QtMsgType type, const QMessageLogContext &context,
                     const QString &msg) {
  QByteArray localMsg = msg.toLocal8Bit();
  const char *time =
      QDateTime::currentDateTime().toString().toLocal8Bit().constData();
  const char *file = context.file ? context.file : "";
  const char *function = context.function ? context.function : "";
  switch (type) {
  case QtDebugMsg:
    fprintf(stderr, "%s Debug: %s (%s:%u, %s)\n", time, localMsg.constData(),
            file, context.line, function);
    break;
  case QtInfoMsg:
    fprintf(stderr, "%s Info: %s (%s:%u, %s)\n", time, localMsg.constData(),
            file, context.line, function);
    break;
  case QtWarningMsg:
    fprintf(stderr, "%s Warning: %s (%s:%u, %s)\n", time, localMsg.constData(),
            file, context.line, function);
    break;
  case QtCriticalMsg:
    fprintf(stderr, "%s Critical: %s (%s:%u, %s)\n", time, localMsg.constData(),
            file, context.line, function);
    break;
  case QtFatalMsg:
    fprintf(stderr, "%s Fatal: %s (%s:%u, %s)\n", time, localMsg.constData(),
            file, context.line, function);
    break;
  }
}

int main(int argc, char *argv[]) {
  qInstallMessageHandler(myMessageOutput);

  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QGuiApplication app(argc, argv);

  CameraAccessManager camManager;

  QQmlApplicationEngine engine;
  engine.rootContext()->setContextProperty(
      QStringLiteral("cameraAccessManager"), &camManager);

  const QUrl url(QStringLiteral("qrc:/main.qml"));
  QObject::connect(&engine, &QQmlApplicationEngine::objectCreated, &app,
                   [url](QObject *obj, const QUrl &objUrl) {
                     if (!obj && url == objUrl)
                       QCoreApplication::exit(-1);
                   },
                   Qt::QueuedConnection);

  engine.load(url);

  return app.exec();
}
