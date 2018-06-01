#ifndef FOLDER_H
#define FOLDER_H

#include "Launcher.h"
#include "LauncherItem.h"

class Folder : public LauncherItem, public Launcher
{
private:
    void removeName(std::string const& nameToRemove)
    {
        auto pos = this->name.find(nameToRemove);
        if(pos != 0)
            pos -= 2; // if we want to remove "toRemove" from these names: "XXXX, toRemove, XXXX, XXXX" pos will be at 't', but we want pos 2 chars backwards
        auto len = nameToRemove.length() + 2; // we will erase ", toRemove"
        
        this->name.erase(pos, len);
    }
    
public:
    Folder(int rows, int cols)
        : LauncherItem(""), Launcher(rows, cols)
    {}
    
    LauncherItem* clone() const override { return new Folder(*this); }
    bool canMove() const override { return true; }
    
    bool addElement(LauncherItem const& newElem, Position p)
    {
        if(Launcher::addElement(newElem, p))
        {
            if(this->name.empty())
                this->name += newElem.getName();
            else 
                this->name += (", " + newElem.getName());
            return true;
        }
        
        return false;
    }
    
    bool addElement(LauncherItem const& newElem)
    {
        return addElement(newElem, {0,0});
    }
    
    bool removeElement(Position p)
    {
        if(!isValidPosition(p))
        {
            std::cout << "Trying to remove an element at invalid position!\n";
            return false;
        }
        
        if(!hasElement(p) || !elementCanMove(p))
            return false;
        
        removeName(lim[p.first][p.second]->getName());
        delete lim[p.first][p.second];
        lim[p.first][p.second] = nullptr;
    }
    
    virtual void print(std::ostream & os = std::cout) const override
    {
        os << "Folder with matrix " << getRows() << "x" << getCols() << std::endl;
        os << "The folder has the following elements: " << name << std::endl;
        os << "Positions of the elements in the matrix:\n";
        printMatrix();
        std::cout << "------- folder printing finished -------- \n";
    }
};

#endif
