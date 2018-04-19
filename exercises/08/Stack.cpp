#include<iostream>
#include<stack> // <-
#include<assert.h>
#include<string.h>
#include<algorithm>
template<typename T>
T sum(std::stack<T>& st)
{
    assert(!st.empty());
    T s = st.top(); st.pop(); // T s; st.pop(s);
    T temp;
    while(!st.empty())
    {
        temp = st.top(); st.pop(); // st.pop(temp);
        s+=temp;
    }

    return s;
}

template<class T>
T sumRec(std::stack<T>& st)
{
    assert(!st.empty());
    if (st.size() == 1)
    {
        return st.top();
    }
    T top;
    top = st.top(); st.pop(); // st.pop(top)
    T sum = top + sumRec(st);

    st.push(top);
    return sum;
}


template<typename T>
T min(std::stack<T>& st)
{
    assert(!st.empty());
    if (st.size() == 1)
    {
        return st.top();
    }
    T top;
    top = st.top(); st.pop(); // st.pop(top)
    T m = std::min(top, min(st));
    // T m = top > min(st) ? min(st) : top;

    st.push(top);
    return m;
}

int calculate(const char* expr)
{
    int len = strlen(expr);
    std::stack<int> st;
    for(int i = 0; i < len ; i++)
    {
        // ako e 4islo -> v stacka
        // ako e znak
        // vadim 2 ot stacka -> vkarvame znak(chislo, chislo)
        if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*')
        {
            int lhs, rhs;
            assert(st.size() >= 2);
            rhs = st.top(); st.pop(); // st.pop(rhs);
            lhs = st.top(); st.pop(); // st.pop(lhs);
            switch (expr[i])
            {
                case '+':
                    st.push(lhs + rhs);
                    break;
                case '-':
                    st.push(lhs - rhs);
                    break;
                case '*':
                    st.push(lhs * rhs);
                    break;
            }
        }
        else if (expr[i] >= '0' && expr[i] <= '9')
        {
            st.push(expr[i] - '0');
        }

    }
    return st.top();
}



template<typename T>
void reverse(std::stack<T>& st)
{
    std::stack<T> reversed;
    while(!st.empty())
    {
        reversed.push(st.top());
        st.pop();
        // T top;
        // st.pop(top);
        // reversed.push(top);
    }
    st = reversed;
}

// NO
template <typename T>
void sortStack(std::stack<T> st)
{
    std::vector<T> v;
    while(!st.empty())
    {
        v.push_back(st.top());
        st.pop();
    }
    std::sort(v.begin(), v.end());
    for (T el : v)
    {
        st.push(el);
    }
}


int main()
{
//    std::stack<int> st;
//    st.push(1);
//    st.push(3);
//    st.push(2);
//    //std::cout<<sum(st)<<std::endl;
//    std::cout<<sumRec(st)<<std::endl;
//    std::cout<<min(st)<<std::endl;
//    std::cout<<std::boolalpha<<st.empty();

    char expr[10000];
    std::cin>>expr;
    std::cout<<calculate(expr);
}

