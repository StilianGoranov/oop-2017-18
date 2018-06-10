#ifndef CLONEABLE_H
#define CLONEABLE_H

class Cloneable 
{
public:
    virtual Cloneable* clone() const = 0;
    virtual ~Cloneable() {}
};

#endif 
