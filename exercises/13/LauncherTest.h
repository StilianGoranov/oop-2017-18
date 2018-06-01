#ifndef LAUNCHERTEST_H
#define LAUNCHERTEST_H

#include <iostream>
#include "Launcher.h"
#include "SystemWidget.h"
#include "MobileApp.h"
#include "Folder.h"

Launcher createTestLauncher()
{
    // launcher 
    Launcher l(3,3);
    
    // elements for launcher
    Folder f1(2,2);
    f1.addElement(MobileApp("FolderMobileApp1"));
    f1.addElement(MobileApp("FolderMobileApp2"));
    f1.addElement(SystemWidget());
    f1.addElement(SystemWidget());
    
    Folder f2(2,2);
    f2.addElement(SystemWidget());
    f2.addElement(SystemWidget());
    
    l.addElement(MobileApp("MobileApp1"));
    l.addElement(f1);
    l.addElement(SystemWidget());
    l.addElement(f2);
    l.addElement(SystemWidget());
    l.addElement(MobileApp("MobileApp2"));
    
    return l;
}

void testLauncher()
{
    auto launcher = createTestLauncher();
    std::cout << launcher << std::endl;
    
}

#endif 
