#ifndef SORTEDLISTTESTS_H
#define SORTEDLISTTESTS_H

#include "SortedList.h"
#include <cassert>

class SortedListTests
{
private:
    using TestList = SortedList<int>;
    using I = SortedListIterator<int>;

    static bool isSorted(TestList const& l)
    {
        if (l.empty())
            return true;
        I it = l.begin();
        while (it != l.end())
            if (!((*it) <= *(++it)))
                return false;
        return true;
    }

    static void insertOnce()
    {
        TestList l;
        l.insert(5);
        assert(isSorted(l));
        assert(!l.empty());
    }

    static void insertFiveElementsSorted()
    {
        TestList l;
        l.insert(1);
        l.insert(3);
        l.insert(2);
        l.insert(5);
        l.insert(4);

        assert(isSorted(l));
    }

    static void insertEraseValidIterator()
    {
        TestList l;
        l.insert(5);
        l.insert(6);

        I it = l.begin();
        l.eraseAt(it);

        assert(it);
        l.eraseAt(it);
        assert(!it);
    }

    static void eraseAtBeginnig()
    {
        TestList l;
        l.insert(1);
        l.insert(3);
        l.insert(2);
        l.insert(5);
        l.insert(4);

        // l.print();

        I it = l.begin();
        l.eraseAt(it);
        assert(it);
        // l.print();
        assert(isSorted(l));
    }

    static void eraseAtEnd()
    {
        TestList l;
        l.insert(1);
        l.insert(3);
        l.insert(2);
        l.insert(5);
        l.insert(4);

        I it = l.end();
        l.eraseAt(it);
        // l.print();
        assert(!it);
        assert(isSorted(l));
    }

    static void eraseAtMiddle()
    {
        TestList l;
        l.insert(1);
        l.insert(3);
        l.insert(2);
        l.insert(5);
        l.insert(4);

         // l.print();

        I it = l.begin();
        ++it;
        ++it;
        l.eraseAt(it);
        l.eraseAt(it);
        // l.print();
        assert(it);
        assert(isSorted(l));
    }
    
    static void copyAvoidsSharing()
    {
        TestList* l1 = new TestList;
        for(int i = 0; i < 10; ++i)
            l1->insert(i);
        
        TestList l2 = *l1;
        delete l1;
        l1 = nullptr;
        
        l2.insert(-1);
        l2.insert(10);
        
        int i = -1;
        for(auto it = l2.begin(); it; ++it, ++i)
            assert(i == *it);
    }
    
    static void assingAvoidsSharing()
    {
        TestList* l1 = new TestList;
        for(int i = 0; i < 10; ++i)
            l1->insert(i);
        
        TestList l2;
        l2.insert(100);
        l2.insert(200);
        
        l2 = *l1;
        
        delete l1;
        l1 = nullptr;
        
        l2.insert(-1);
        l2.insert(10);
        
        int i = -1;
        for(auto it = l2.begin(); it; ++it, ++i)
            assert(i == *it);
    }

public:

    static void runTests()
    {
        insertOnce();
        insertFiveElementsSorted();
        insertEraseValidIterator();
        eraseAtBeginnig();
        eraseAtEnd();
        eraseAtMiddle();
        copyAvoidsSharing();
        assingAvoidsSharing();
    }
};


#endif /* SORTEDLISTTESTS_H */

