#include<iostream>
#include<stack>
#include<assert.h>

using namespace std;

template<typename T>
using pushingFunction = void(*)(stack<T>&, T);

template<typename T>
T maxElement(stack<T>& st)
{
    assert(!st.empty());
    if (st.size() == 1)
    {
        return st.top();
    }
    T temp = st.top();
    st.pop();
    T maxEl = max(temp, maxElement(st));
    st.push(temp);
    return maxEl;
}
template<typename T>
void pushBottom(stack<T>& st, T a)
{
    if(st.empty())
    {
        st.push(a);
        return;
    }
    T temp = st.top();
    st.pop();
    pushBottom(st, a);
    st.push(temp);
}

template<typename T>
void pushSorted(stack<T>& st, T a)
{
    if(st.empty() || st.top() < a)
    {
        st.push(a);
        return;
    }
    T temp = st.top();
    st.pop();
    pushSorted(st, a);
    st.push(temp);
}

template<typename T>
void doSomething(stack<T>& st, pushingFunction<T> specialPush)
{
    if (st.empty()) return;
    T temp = st.top();
    st.pop();
    doSomething(st, specialPush);
    specialPush(st, temp);
}
int main()
{
    stack<int> a;
    a.push(1);
    a.push(3);
    a.push(2);
    cout<<maxElement(a)<<endl;;
    doSomething(a, pushSorted);
    doSomething(a, pushBottom);
    while(!a.empty())
    {
        cout<<a.top();
        a.pop();
    }
    return 0;
}
