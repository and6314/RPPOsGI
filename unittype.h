#ifndef UNITTYPE_H
#define UNITTYPE_H
#include <QString>
#include <QObject>
#include <attacktype.h>

enum Fraction {O_Hereticus, Tzinch_cult};

class UnitType
{
public:
    UnitType();
    UnitType(int type_id,Fraction f, QString name, QString descr, QString imS,
             double n_hp, int n_ap, double n_mp, double n_mor, double off,
             double def, int attackR,int cost);
    Fraction fraction;
    QList<QString> specialfeatures;
    int cost;
    void setName(QString n);
    QString getName();
    void setDescr(QString d);
    QString getDescription();
    void setImSource(QString s);
    QString getImSorce();
    int getid();
    void setNorm_hp(double n);
    double getNorm_hp();
    void setNorm_mp(double n);
    double getNorm_mp();
    void setNorm_ap(int n);
    int getNorm_ap();
    double getOff();
    void setOff(double o);
    double getDef();
    void setDef(int d);
    void setNorm_morale(double n);
    double getNorm_morale();
    int getAttackRadius();
    bool operator==(const UnitType& arg);
    QList <AttackType> attacks;
    int getDamage();

private:
    int id;
    QString name;
    QString description;
    QString imSource;
    double norm_hp;
    double norm_mp;
    int norm_ap;
    double off;
    double def;
    double norm_morale;
    int attackRadius; //in cells
};

#endif // UNITTYPE_H
