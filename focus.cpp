#include "focus.h"

Focus::Focus()
{
    this->infocus = NULL;
}

bool Focus::isEmpty()
{
    if (this->infocus == NULL)
        return true;
    else
        return false;
}

void Focus::clear()
{
    this->infocus = NULL;
}

void Focus::setInfocus(Unit *f)
{
    this->infocus = f;
}
