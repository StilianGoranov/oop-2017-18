#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <iostream>
#include "LauncherItem.h"
#include <vector>
#include <cassert>
#include "Printable.h"

using Position = std::pair<int, int>;

class Launcher : virtual public Printable
{
private:
    using LauncherItemRow = std::vector<LauncherItem*>;
    using LauncherItemMatrix = std::vector<LauncherItemRow>;

protected:
    LauncherItemMatrix lim;
    
    void initializeEmptyRolsAndCols(int rows, int cols)
    {
        assert(rows > 0 && cols > 0);
        lim = LauncherItemMatrix(rows, LauncherItemRow(cols, nullptr));
    }
    
    bool isValidPosition(Position p) const
    {
        return p.first >= 0 && p.first < lim.size() && 
                p.second >= 0 && p.second < lim[0].size();
    }
    
    bool hasElement(Position p) const
    {
        return lim[p.first][p.second] != nullptr;
    }
    
    bool findFirstEmptyPosition(Position& p) const 
    {
        for(int i = 0; i < getRows(); i++)
            for(int j = 0; j < getCols(); ++j)
                if(lim[i][j] == nullptr)
                {
                    p.first = i;
                    p.second = j;
                    return true;
                }
                
        return false;
    }
    
    bool elementCanMove(Position p) const 
    {
        return lim[p.first][p.second]->canMove();
    }
    
    void copy(Launcher const& other)
    {
        auto otherRows = other.getRows(), otherCols = other.getCols();
        initializeEmptyRolsAndCols(otherRows, otherCols);
        for(int i = 0; i < otherRows; i++)
            for(int j = 0; j < otherCols; j++)
                lim[i][j] = (other.lim[i][j] != nullptr) ? other.lim[i][j]->clone() : nullptr;
    }
    
    void erase()
    {
        for(auto& row : lim)
            for(auto& elemPtr : row)
                delete elemPtr;
    }
    
public:
    Launcher(int rows, int cols)
    {
        initializeEmptyRolsAndCols(rows, cols);
    }
    
    Launcher(Launcher const& other)
    {
        copy(other);
    }
    
    Launcher& operator=(Launcher const& other)
    {
        if(this != &other)
        {
            erase();
            copy(other);
        }
        
        return *this;
    }
    
    int getRows() const { return lim.size(); }
    int getCols() const { return lim[0].size(); }
    
    void clear()
    {
        for(auto& row : lim)
        {
            for(auto& elem : row)
            {
                delete elem;
                elem = nullptr;
            }
        }
    }
    
    bool addElement(LauncherItem const& newElem, int i, int j)
    {
        return addElement(newElem, {i, j});
    }
    
    bool addElement(LauncherItem const& newElem, Position p)
    {
        if(!isValidPosition(p))
        {
            std::cout << "Trying to add element add invalid position!\n";
            return false;
        }
        
        if(!hasElement(p))
        {
            lim[p.first][p.second] = newElem.clone();
            return true;
        }
        else 
        {
            Position p;
            if(findFirstEmptyPosition(p))
            {
                lim[p.first][p.second] = newElem.clone();
                return true;
            }
            
            return false;
        }
    }
    
    // add element to the first free position
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
        
        delete lim[p.first][p.second];
        lim[p.first][p.second] = nullptr;
    }
    
    bool moveElement(Position from, Position to)
    {
        if(!isValidPosition(from) || !isValidPosition(to))
        {
            std::cout << "Invalid position!\n";
            return false;
        }
        
        if(!elementCanMove(from))
            return false;
        
        if(!hasElement(to))
        {
            lim[to.first][to.second] = lim[from.first][from.second];
            lim[from.first][from.second] = nullptr;
            return true;
        }
        else
        {
            if(!elementCanMove(to))
                return false;
            
            // element at position "to" exists and can move
            std::swap(lim[from.first][from.second], lim[to.first][to.second]);
            return true;
        }
    }
    
    friend std::ostream& operator<<(std::ostream& os, Launcher const& l)
    {
        l.print(os);
        return os;
    }
    
protected:
    void printMatrix(std::ostream& os = std::cout) const 
    {
        for(int i = 0; i < getRows(); i++)
        {
            for(int j = 0; j < getCols(); ++j)
            {
                os << "Position (" << i << "," << j << ") : ";
                if(hasElement({i,j}))
                    os << *lim[i][j] << std::endl;
                else 
                    os << "empty" << std::endl;
            }
        }
    }
    
public:
    virtual void print(std::ostream& os = std::cout) const override
    {
        os << "Launcher with matrix " << getRows() << "x" << getCols() << std::endl;
        printMatrix();
    }
};

#endif
