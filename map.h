#ifndef MAP_H
#define MAP_H

#include <QObject>
#include <QString>
#include <QFile>
#include <QString>
#include <QQuickItem>
#include <QQuickPaintedItem>
#include <QPainter>
#include <qmath.h>
#include <QDebug>
#include <unit.h>
#include <unittype.h>
#include <QMouseEvent>
#include <focus.h>
#include <village.h>

class Map : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(int **mapArr READ getMapArr WRITE setMapArr NOTIFY mapArrChanged)
    Q_PROPERTY(int sizeX READ getSizeX WRITE setSizeX NOTIFY sizeXChanged)
    Q_PROPERTY(int sizeY READ getSizeY WRITE setSizeY NOTIFY sizeYChanged)
    Q_PROPERTY(double cx READ cx WRITE setCx NOTIFY cxChanged)
    Q_PROPERTY(double cy READ cy WRITE setCy NOTIFY cyChanged)
    Q_PROPERTY(QList<Unit> units READ unitsList /*WRITE setUnitsList NOTIFY unitsChanged*/)
    Q_PROPERTY(QList<UnitType> unittypes READ unittypesList)
    Q_PROPERTY(bool rercActive READ isRercActive WRITE setRercActive)

public:
    Map(QQuickItem *parent  = nullptr);
    void paint(QPainter *painter);

    QList<Unit> units;
    QList<UnitType> unittypes;
    QList<Player> players;
    QList<Village> villages;
    Player *activePlayer;
    Focus focus;
    Q_INVOKABLE bool isRecrPoss(int x, int y);
    Q_INVOKABLE void start();
    Q_INVOKABLE void mouseClicked(int x, int y, Qt::MouseButtons);
    Q_INVOKABLE void newturn();
    Q_INVOKABLE bool isCellEmpty(int x, int y);
    QList<Unit> unitsList();
    QList<UnitType> unittypesList();
    int **getMapArr();
    void setMapArr(int **m);
    int getSizeX();
    void setSizeX(const int &sx);
    int getSizeY();
    void setSizeY(const int &sy);
    double cx() const;
    double cy() const;
    bool isRercActive();
    void setRercActive(bool r);
    Q_INVOKABLE bool isFocusEmpty();
    Q_INVOKABLE void setLastxy(double ls,double ly);
    Q_INVOKABLE QString getFocus();
    Unit *unitOnCell(int cellx, int celly);
    Village *villageUnCell(QPoint cell);
    void distributePlayers();
    void readMap(QString filename);
    double lastx;
    double lasty;
    bool gameInProgress;
    bool **occupancy;   //true if cell is occupied
    void clear();
    double distance(int cellx1, int celly1, int cellx2, int celly2);
    QList <QPoint> path(QPoint cell1,QPoint cell2);
    void aiVictory();

signals:
    void aiturn();
    void cxChanged(double cx);
    void cyChanged(double cy);
    void mapArrChanged();
    void sizeXChanged();
    void sizeYChanged();
    void activePlayerChanged();
    void victory();
    void defeat();


public slots:
    void setCx(double cx);
    void setCy(double cy);

private:
    QMap<QString, QPixmap> tileCache;
    int **mapArr;
    int sizeX;
    int sizeY;
    double m_cx;
    double m_cy;
    int turnNum;
    bool rercActive;


};

#endif // MAP_H
