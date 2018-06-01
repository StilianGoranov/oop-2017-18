#ifndef SYSTEMWIDGET_H
#define SYSTEMWIDGET_H

#include "LauncherItem.h"

class SystemWidget : public LauncherItem
{
public:
    SystemWidget()
        : LauncherItem("SystemWidget")
    {}
    
    LauncherItem * clone() const override { return new SystemWidget(*this); }
    bool canMove() const override { return false; }
};

#endif
