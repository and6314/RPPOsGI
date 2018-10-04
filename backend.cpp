#include "backend.h"

BackEnd::BackEnd(QObject *parent) :
    QObject(parent)
{

}

QString BackEnd::userName()
{
    return m_userName;
}

void BackEnd::setUserName(const QString &userName)
{
    if (userName == m_userName)
        return;

    m_userName = userName;
    emit userNameChanged();
}

QStringList BackEnd::getMap()
{
    return map;
}

void BackEnd::setMap(const QStringList &m)
{
    map = m;
    emit mapChanged();
}

int BackEnd::getSizeX()
{
    return sizeX;
}

void BackEnd::setSizeX(const int &sx)
{
    sizeX = sx;
    emit sizeXChanged();
}

int BackEnd::getSizeY()
{
    return sizeY;
}

void BackEnd::setSizeY(const int &sy)
{
    sizeY = sy;
    emit sizeYChanged();
}

void BackEnd::start()
{
    QFile file1("E:/QtProjects/untitled13/map1.txt");
    file1.open(QIODevice::ReadOnly);

    QByteArray a = file1.readAll();
    QString s = a;
    map = s.split(',');
    m_userName = map.at(0);
    file1.close();
    bool ok;
    sizeX = map.at(0).toInt(&ok,10);
    sizeY = map.at(1).toInt(&ok,10);
}
