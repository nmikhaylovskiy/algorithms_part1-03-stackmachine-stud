////////////////////////////////////////////////////////////////////////////////
// Module Name: int_stack.h/cpp
// Authors: Sergey Shershakov
// Version: 0.2.0
// Date: 23.01.2017
//
// This is a part of the course "Algorithms and Data Structures"
// provided by the School of Software Engineering of the Faculty
// of Computer Science at the Higher School of Economics.
////////////////////////////////////////////////////////////////////////////////

#include <stdexcept>
#include "int_stack.h"

// TODO: add necessary headers here
// #include <...

namespace xi
{

// TODO: add method definitions here

IntStack::IntStack(size_t sz)
{
    _ssize = sz;
    _stack = new int[sz];
    _head = 0;
}

IntStack::~IntStack()
{
    delete[] _stack;
}

void IntStack::push(int el)
{
    if (isFull())
        throw std::logic_error("logic_error is thrown NOW");
    else
    {
        _stack[_head] = el;
        _head++;
    }
}

int IntStack::pop()
{
    if (!isEmpty())
    {
        _head--;
        return _stack[_head];
    } else
        throw std::logic_error("logic_erroris thrown");
}

int IntStack::top()
{
    if (!isEmpty())
        return _stack[_head - 1];
    else
        throw std::logic_error("logic_error is thrown");
}

void IntStack::clear()
{
    _head = 0;
}

bool IntStack::isEmpty() const
{
    return _head == 0;
}

bool IntStack::isFull() const
{
    return _head == _ssize;
}
} // namespace xi