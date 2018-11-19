#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QStandardItemModel>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    QStandardItemModel weekModel;
    weekModel.appendRow(new QStandardItem("Sunday"));
    weekModel.appendRow(new QStandardItem("Monday"));
    weekModel.appendRow(new QStandardItem("Tuesday"));
    weekModel.appendRow(new QStandardItem("Wednesday"));
    weekModel.appendRow(new QStandardItem("Thursday"));
    weekModel.appendRow(new QStandardItem("Friday"));
    weekModel.appendRow(new QStandardItem("Saturday"));

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
