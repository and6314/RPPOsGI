#ifndef FOCUS_H
#define FOCUS_H
#include <unit.h>

class Focus
{
public:
    Focus();
    Unit *infocus;
    bool isEmpty();
    void clear();
    void setInfocus(Unit *f);
};

#endif // FOCUS_H
