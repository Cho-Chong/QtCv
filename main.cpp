#include <QApplication>
#include <QQuickView>
#include <QQmlContext>
#include "openvidcap.h"


int main(int argc, char **argv)
{
  QApplication app(argc, argv);
  qmlRegisterType<OpenVidCap>("myextension", 1, 0, "OpenVidCap");

  QQuickView view;
  view.setSource(QUrl("qrc:/main.qml"));
  view.show();

    return app.exec();
}
