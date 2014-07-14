#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQmlContext>
#include <QPixmap>

#include "svimage.h"
#include "svprocessor.h"
#include "svimageprovider.h"

int main(int argc, char *argv[])
{
    QGuiApplication a(argc, argv);

    QQmlApplicationEngine engine;
    SvImageProvider imageProvider;

    QImage imgLeft("../ComputerVision/img/left4_.png");
    QImage imgRight("../ComputerVision/img/right4_.png");
    QImage imgStereo(imgLeft.width(), imgRight.height(), QImage::Format_RGB32);

    SvImage left(imgLeft);
    SvImage right(imgRight);
    SvImage stereo(imgStereo);
    SvProcessor proc(&left, &right, &stereo, 4);

    imageProvider.addImage("left", &left);
    imageProvider.addImage("right", &right);
    imageProvider.addImage("result", &stereo);

    engine.addImageProvider("images", &imageProvider);
    engine.load(QUrl(QStringLiteral("qrc:///Main.qml")));
    engine.rootContext()->setContextProperty("processor", &proc);

    proc.start();

    return a.exec();
}
