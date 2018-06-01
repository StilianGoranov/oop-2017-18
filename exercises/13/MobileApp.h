#ifndef MOBILEAPP_H
#define MOBILEAPP_H

#include "LauncherItem.h"

class MobileApp : public LauncherItem
{
public:
    MobileApp(std::string const& _name = "DefaultName")
        : LauncherItem(_name)
    {}
    
    bool canMove() const override { return true; }
    LauncherItem* clone() const override { return new MobileApp(*this); }
};

#endif 
