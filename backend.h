#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QString>
#include <QFile>
#include <QString>
class BackEnd : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString userName READ userName WRITE setUserName NOTIFY userNameChanged)
    Q_PROPERTY(QStringList map READ getMap() WRITE setMap NOTIFY mapChanged)
    Q_PROPERTY(int sizeX READ getSizeX() WRITE setSizeX NOTIFY sizeXChanged)
    Q_PROPERTY(int sizeY READ getSizeY() WRITE setSizeY NOTIFY sizeYChanged)
    public:
        explicit BackEnd(QObject *parent = nullptr);
        Q_INVOKABLE void start();
        QString userName();
        void setUserName(const QString &userName);
        QStringList getMap();
        void setMap(const QStringList &m);
        int getSizeX();
        void setSizeX(const int &sx);
        int getSizeY();
        void setSizeY(const int &sy);

    signals:
        void userNameChanged();
        void mapChanged();
        void sizeXChanged();
        void sizeYChanged();

    private:
        QString m_userName;
        QStringList map;
        int sizeX;
        int sizeY;

};

#endif // BACKEND_H
