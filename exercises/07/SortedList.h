#ifndef SORTEDLIST_H
#define SORTEDLIST_H

#include <iostream>

template <typename T>
struct Node
{
    Node(T const& _data, Node* _prev = nullptr, Node* _next = nullptr)
    : data{_data}, next{_next}, prev{_prev}
    {
    }

    T data;
    Node *next, *prev;
};

template <typename T>
class SortedListIterator;

template <typename T>
class SortedList
{
private:
    Node<T> *first, *last;

    using I = SortedListIterator<T>;

    void copy(SortedList const& other)
    {
        for (auto it = other.begin(); it; ++it)
            insert(*it);
    }

    void clear()
    {
        auto it = begin();
        while (it)
            eraseAt(it);
    }

public:
    SortedList() : first{nullptr}, last{nullptr}
    {
    }

    SortedList(SortedList const& other)
    : first{nullptr}, last{nullptr}
    {
        copy(other);
    }

    SortedList& operator=(SortedList const& other)
    {
        if(this != &other)
        {
            clear();
            copy(other);
        }

        return *this;
    }

    ~SortedList()
    {
        clear();
    }

    bool insert(T const& newElem)
    {
        if (empty())
        {
            first = last = new Node<T>(newElem);
            return true;
        }

        I it = begin();

        while (it && *it <= newElem)
            ++it;

        // insert at beginning
        if (it == begin())
        {
            Node<T>* newNode = new Node<T>(newElem, nullptr, first);
            first->prev = newNode;
            first = first->prev;
            return true;
        }

        // insert at end
        if (!it)
        {
            Node<T>* newNode = new Node<T>(newElem, last);
            last->next = newNode;
            last = last->next;
            return true;
        }

        // insert in middle
        Node<T>* newNode = new Node<T>(newElem, it.ptr->prev, it.ptr);
        auto temp = it.ptr->prev;
        it.ptr->prev = newNode;
        temp->next = newNode;
        return true;
    }

    // makes the iterator point to the next element if there is one
    // otherwise invalidates it

    bool eraseAt(I& it)
    {
        if (!it)
            return false;

        // erase at beginning
        if (it == begin())
        {
            auto temp = first;
            first = first->next;
            ++it;
            delete temp;

            if (!first)
                // no elements left
            {
                last = nullptr;
                return true;
            }

            // at least 1 element left
            first->prev = nullptr;
            return true;

        } else if (it == end())
            // erase at end
        {
            // surely there are at least 2 elements in the list
            // (if only 1 elements -> that would've been the previous case)
            last = last->prev;
            ++it;
            delete last->next;
            last->next = nullptr;
            return true;
        } else
            // erase at middle
        {
            it.ptr->prev->next = it.ptr->next;
            it.ptr->next->prev = it.ptr->prev;
            ++it;
            delete it.ptr;
            return true;
        }
    }

    bool empty() const
    {
        return first == nullptr;
    }

    I begin() const
    {
        return I(first);
    }

    I end() const
    {
        return I(last);
    }

    void print(std::ostream& os = std::cout) const
    {
        for (auto it = begin(); it; ++it)
            os << *it << ' ';

        if (empty())
            os << "Empty list." << std::endl;
        else
            os << std::endl;
    }
};

template <typename T>
class SortedListIterator
{
    friend class SortedList<T>;

private:
    using I = SortedListIterator<T>;
    Node<T>* ptr;

public:
    SortedListIterator(Node<T>* _ptr = nullptr) : ptr{_ptr}
    {
    }

    bool valid() const
    {
        return ptr != nullptr;
    }

    T& get()
    {
        return ptr->data;
    }

    I next()
    {
        return I(ptr->next);
    }

    I prev()
    {
        return I(ptr->prev);
    }

    friend bool operator==(I const& it1, I const& it2)
    {
        return it1.ptr == it2.ptr;
    }

    friend bool operator!=(I const& it1, I const& it2)
    {
        return !(it1 == it2);
    }

    // syntactic sugar

    operator bool()
    {
        return valid();
    }

    I& operator++()
    {
        return *this = next();
    }

    I operator++(int)
    {
        I prev = *this;
        ++(*this);
        return prev;
    }

    I operator--()
    {
        return *this = prev();
    }

    I& operator--(int)
    {
        I prev = *this;
        --(*this);
        return prev;
    }

    T& operator*()
    {
        return get();
    }
};


#endif /* SORTEDLIST_H */

