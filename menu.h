#ifndef MENU_H
#define MENU_H

#include <QObject>


class Menu: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString s_map READ map WRITE setMap NOTIFY mapChanged)
    Q_PROPERTY(QString bi1 READ baseIncome1 WRITE setBI1)
    Q_PROPERTY(QString bi2 READ baseIncome2 WRITE setBI2)
    Q_PROPERTY(QString bi3 READ baseIncome3 WRITE setBI3)
    Q_PROPERTY(QString bi4 READ baseIncome4 WRITE setBI4)
    Q_PROPERTY(QString pf1 READ playerfr1 WRITE setPf1)
    Q_PROPERTY(QString pf2 READ playerfr2 WRITE setPf2)
    Q_PROPERTY(QString pf3 READ playerfr3 WRITE setPf3)
    Q_PROPERTY(QString pf4 READ playerfr4 WRITE setPf4)

public:
    Menu(QObject *parent = nullptr);
    QString s_map;
    QString bi1;
    QString bi2;
    QString bi3;
    QString bi4;
    QString pf1;
    QString pf2;
    QString pf3;
    QString pf4;
    QString baseIncome1();
    QString baseIncome2();
    QString baseIncome3();
    QString baseIncome4();
    void setBI1(QString bi);
    void setBI2(QString bi);
    void setBI3(QString bi);
    void setBI4(QString bi);
    QString playerfr1();
    QString playerfr2();
    QString playerfr3();
    QString playerfr4();
    void setPf1(QString pf);
    void setPf2(QString pf);
    void setPf3(QString pf);
    void setPf4(QString pf);
    QString map();
    void setMap(QString map);

signals:
    void accept();
    void mapChanged(QString map);
};

#endif // MENU_H
