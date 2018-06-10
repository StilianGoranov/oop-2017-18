#include "Laboratory.h"


void laboratoryDemo()
{
    Laboratory lab;
    
    PackageStudy packageStudy("packagestudy1");
    packageStudy.addStudy(SingleStudy("pstudy1", 500, 18, -300, 1000));
    packageStudy.addStudy(SingleStudy("pstudy2", 300, 1, -400, 700));

    lab.addStudy(SingleStudy("study1", 50, 20, -30, 100));
    lab.addStudy(SingleStudy("study2", 1000, 100, -500, 2000));
    lab.addStudy(packageStudy);
    
    std::cout << lab.getFastestExecutableStudy()->getName() << std::endl;
    std::cout << lab.getStudiesPrice() << std::endl;
}


int main()
{
    laboratoryDemo();
    
    return 0;
}
