#include<iostream>
#include<stack>
#include<string>
#include<assert.h>

class Formula
{
public:
    virtual double value() const = 0;
    virtual ~Formula() {};
    virtual std::ostream& print(std::ostream& out) const = 0;
    virtual Formula* clone() const = 0;

    friend std::ostream& operator<<(std::ostream& out, const Formula& f)
    {
        return f.print(out);
    }
};

class Number : public Formula
{
public:
    Number(double _arg = 0): arg(_arg) {}
    virtual std::ostream& print(std::ostream& out) const override
    {
        return out << arg;
    }
    virtual double value() const override
    {
        return arg;
    }
    virtual Formula* clone() const override
    {
        return new Number(*this);
    }
private:
    double arg;
};

class Sum : public Formula
{
public:
    Sum(const Formula& _arg1, const Formula& _arg2): arg1(_arg1.clone()), arg2(_arg2.clone()) {}
    Sum(const Sum& other)
    {
        copy(other);
    }
    virtual ~Sum() override
    {
        del();
    }
    Sum& operator=(const Sum& other)
    {
        if (this != &other)
        {
            del();
            copy(other);
        }

        return *this;
    }

    virtual std::ostream& print(std::ostream& out) const override
    {
        return out << '(' << *arg1 << '+' << *arg2 << ')';
    }
    virtual double value()const override
    {
        return arg1->value() + arg2->value();
    }
    virtual Formula* clone() const override
    {
        return new Sum(*this);
    }
private:
    Formula *arg1, *arg2;
    void copy(const Sum& other)
    {
        arg1 = other.arg1->clone();
        arg2 = other.arg2->clone();
    }
    void del()
    {
        delete arg1;
        delete arg2;
    }
};

Sum operator+(const Formula& lhs, const Formula& rhs)
{
    return Sum(lhs, rhs);
}

class Difference : public Formula
{
public:
    Difference(const Formula& _arg1, const Formula& _arg2): arg1(_arg1.clone()), arg2(_arg2.clone()) {}
    Difference(const Difference& other)
    {
        copy(other);
    }
    virtual ~Difference() override
    {
        del();
    }
    Difference& operator=(const Difference& other)
    {
        if (this != &other)
        {
            del();
            copy(other);
        }

        return *this;
    }

    virtual std::ostream& print(std::ostream& out) const override
    {
        return out << '(' << *arg1 << '-' << *arg2 << ')';
    }
    virtual double value()const override
    {
        return arg1->value() - arg2->value();
    }
    virtual Formula* clone() const override
    {
        return new Difference(*this);
    }
private:
    Formula *arg1, *arg2;
    void copy(const Difference& other)
    {
        arg1 = other.arg1->clone();
        arg2 = other.arg2->clone();
    }
    void del()
    {
        delete arg1;
        delete arg2;
    }
};

Difference operator-(const Formula& lhs, const Formula& rhs)
{
    return Difference(lhs, rhs);
}

class Multiplication : public Formula
{
public:
    Multiplication(const Formula& _arg1, const Formula& _arg2): arg1(_arg1.clone()), arg2(_arg2.clone()) {}
    Multiplication(const Multiplication& other)
    {
        copy(other);
    }
    virtual ~Multiplication() override
    {
        del();
    }
    Multiplication& operator=(const Multiplication& other)
    {
        if (this != &other)
        {
            del();
            copy(other);
        }

        return *this;
    }

    virtual std::ostream& print(std::ostream& out) const override
    {
        return out << '(' << *arg1 << '*' << *arg2 << ')';
    }
    virtual double value()const override
    {
        return arg1->value() * arg2->value();
    }
    virtual Formula* clone() const override
    {
        return new Multiplication(*this);
    }
private:
    Formula *arg1, *arg2;
    void copy(const Multiplication& other)
    {
        arg1 = other.arg1->clone();
        arg2 = other.arg2->clone();
    }
    void del()
    {
        delete arg1;
        delete arg2;
    }
};

Multiplication operator*(const Formula& lhs, const Formula& rhs)
{
    return Multiplication(lhs, rhs);
}

class Division : public Formula
{
public:
    Division(const Formula& _arg1, const Formula& _arg2)
    {
        assert(_arg2.value() != 0 && "Division by Zero");
        arg1 = _arg1.clone();
        arg2 = _arg2.clone();
    }
    Division(const Division& other)
    {
        copy(other);
    }
    virtual ~Division() override
    {
        del();
    }
    Division& operator=(const Division& other)
    {
        if (this != &other)
        {
            del();
            copy(other);
        }

        return *this;
    }

    virtual std::ostream& print(std::ostream& out) const override
    {
        return out << '(' << *arg1 << '/' << *arg2 << ')';
    }
    virtual double value()const override
    {
        return arg1->value() / arg2->value();
    }
    virtual Formula* clone() const override
    {
        return new Division(*this);
    }
private:
    Formula *arg1, *arg2;
    void copy(const Division& other)
    {
        arg1 = other.arg1->clone();
        arg2 = other.arg2->clone();
    }
    void del()
    {
        delete arg1;
        delete arg2;
    }
};

Division operator/(const Formula& lhs, const Formula& rhs)
{
    assert(rhs.value() != 0 && "Division by Zero");
    return Division(lhs, rhs);
}
class FormulaParser
{
private:
    Formula* formula;
    void del()
    {
        delete formula;
    }
    void copy(const FormulaParser& other)
    {
        formula = other.formula->clone();
    }
    Formula* parsePostfix(const std::string& expression)
    {
        std::stack<Formula*> st;
        unsigned i = 0;
        unsigned len = expression.size();
        double number = 0.0;
        bool period = false;
        int divisor = 1;
        for (i; i <= len ; i++)
        {
            if (expression[i] >= '0' && expression[i] <= '9')
            {
                number = number * 10 + (expression[i] - '0');
                if (period) divisor*=10;
            }
            else if (expression[i] == '.')
            {
                period = true;
            }
            else if (expression[i] == ' ')
            {
                st.push(new Number(number/divisor));
                period = false;
                number = 0;
                divisor = 1;
            }
            else if (expression[i] == '\0' && expression[i-1] >= '0' && expression[i-1] <= '9')
            {
                st.push(new Number(number/divisor));
            }
            else // operator
            {
                Formula* rhs = st.top();
                Formula* lhs = (st.pop(), st.top());
                st.pop();
                switch(expression[i])
                {
                    case '+': st.push(new Sum(*lhs + *rhs)); break;
                    case '-': st.push(new Difference(*lhs - *rhs)); break;
                    case '*': st.push(new Multiplication(*lhs * *rhs)); break;
                    case '/': st.push(new Division(*lhs / *rhs)); break;
                }
                delete lhs;
                delete rhs;
                i++;
            }
            // ...
        }

        return st.top();
    }
public:
    FormulaParser(const std::string& expression)
    {
        formula = parsePostfix(expression);
    }
    ~FormulaParser()
    {
        del();
    }
    FormulaParser(const FormulaParser& other)
    {
        copy(other);
    }
    FormulaParser& operator=(const FormulaParser& other)
    {
        if (this != &other)
        {
            del();
            copy(other);
        }

        return *this;
    }

    void print() const
    {
        formula->print(std::cout);
    }

    double calculate() const
    {
        return formula->value();
    }
};

int main()
{
    std::string expression;
    std::getline(std::cin, expression);
    FormulaParser test(expression);
    test.print();
    std::cout<<'=';
    std::cout<<test.calculate()<<std::endl;

    return 0;
}

