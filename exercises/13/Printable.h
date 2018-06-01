#ifndef PRINTABLE_H
#define PRINTABLE_H

#include <iostream>

class Printable
{
public:
    virtual void print(std::ostream& os = std::cout) const = 0;
    virtual ~Printable() {}
};

#endif 
