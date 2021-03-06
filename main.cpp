#include "backend.h"
#include "map.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "recruitment.h"
#include "toppanel.h"
#include "rightpanel.h"
#include "game.h"
#include "attackpanel.h"
#include "menu.h"
#include "passiveabilitiespanel.h"

int main(int argc, char *argv[])
{


    QGuiApplication app(argc, argv);
    qmlRegisterType<Game>("game", 1, 0, "Game");
    qmlRegisterType<Recruitment>("recruitment", 1, 0, "Recruitment");
    qmlRegisterType<BackEnd>("backend", 1, 0, "BackEnd");
    qmlRegisterType<Map>("map", 1, 0, "Map");
    qmlRegisterType<TopPanel>("toppanel", 1, 0, "TopPanel");
    qmlRegisterType<RightPanel>("rightpanel", 1, 0, "RightPanel");
    qmlRegisterType<AttackPanel>("attackpanel", 1, 0, "AttackPanel");
    qmlRegisterType<Menu>("menu", 1, 0, "Menu");
    qmlRegisterType<PassiveAbilitiesPanel>("passiveabilitiespanel", 1, 0, "PassiveAbilitiesPanel");
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
