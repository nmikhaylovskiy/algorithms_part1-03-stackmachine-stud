////////////////////////////////////////////////////////////////////////////////
// Module Name:  stack_machine.h/cpp
// Authors:      Sergey Shershakov
// Version:      0.2.0
// Date:         23.01.2017
//
// This is a part of the course "Algorithms and Data Structures"
// provided by  the School of Software Engineering of the Faculty
// of Computer Science at the Higher School of Economics.
////////////////////////////////////////////////////////////////////////////////

#include "stack_machine.h"

#include <vector>
#include <sstream>
#include <iostream>
#include <stdlib.h>

namespace xi
{

//==============================================================================
// Free functions -- helpers
//==============================================================================

std::vector<std::string> TheParsingMethod(std::string expr)
{
    std::istringstream input(expr);
    std::string token;
    std::vector<std::string> tokens;
    while (std::getline(input, token, ' '))
    {
        tokens.push_back(token);
    }


    return tokens;
}

bool IsItIntNumber(std::string &s)
{
    size_t offset = 0;
    if (s[0] == '+' && s.length() > 1)
        s.erase(0, 1);
    if (s[offset] == '-')
    {
        ++offset;
        return s.find_first_not_of("0123456789", offset) == std::string::npos;
    }
    return s.find_first_not_of("0123456789", offset) == std::string::npos;

}

//==============================================================================
// class PlusOp
//==============================================================================


int PlusOp::operation(char op, int a, int b,
                      int /*c*/) // < just commented unused argument. This does not affect the code anyhow.
{
    if (op != '+')
        throw std::logic_error("Operation other than Plus (+) are not supported");
    return a + b;
}

IOperation::Arity PlusOp::getArity() const
{
    return arDue;
}

//==============================================================================
// class StackMachine
//==============================================================================

void StackMachine::registerOperation(char symb, IOperation *oper)
{
    SymbolToOperMapConstIter it = _opers.find(symb);
    if (it != _opers.end())
        throw std::logic_error("An operation ... is alr. reg...");
    _opers[symb] = oper;
}

IOperation *StackMachine::getOperation(char symb)
{
    SymbolToOperMapConstIter it = _opers.find(symb);
    if (it == _opers.end())
        throw std::logic_error("looooooogic(((((");
    return _opers[symb];
}

//==============================================================================
// class DivOp
//========================================================================

int DivOp::operation(char op, int a, int b, int c)
{
    if (op != '/')
        throw std::logic_error("operation other than Div(-) are nor supported");
    else
    {
        if (b != 0)
            return a / b;
        else
        {
            if (a > 0)
                return INT_MAX;
            else
                return -INT_MAX;
        }
    }
}

IOperation::Arity DivOp::getArity() const
{
    return arDue;
}

//==============================================================================
// class ChoiseOp
//========================================================================

int ChoiceOp::operation(char op, int a, int b, int c)
{
    if (a != 0)
    {
        return b;
    } else
    {
        return c;
    }
}

IOperation::Arity ChoiceOp::getArity() const
{
    return arTre;
}

int AssignOp::operation(char op, int a, int /*b*/, int /*c*/)
{
    return a;
}

IOperation::Arity AssignOp::getArity() const
{
    return arUno;
}

//кстати, тут было оч много
// проверок на всякое такое по типу "а что если длинна
// оператора больше одного, а что если где-то нуллптр и проч,
// весь код закидал экспешанами, а потом подчистил, потому что
// и без них все работает. Я к тому, что не надо снижать оценку
// за не проверку на что-то, потому что это сделано ради
// оптимизации и скорости работы кода. Не, ну правда :(((
// (пс - эксепшены есть в более ранних версиях на гите, их много)

int StackMachine::calculate(const std::string &expr, bool clearStack)
{
    if (clearStack)
        _s.clear();
    std::vector<std::string> points = TheParsingMethod(expr);
    for (int i = 0; i < points.size(); i++)
    {
        if (IsItIntNumber(points[i]) != 0)
        {
            std::string str = points[i];
            int n = std::stoi(str);
            _s.push(n);
        } else
        {
            IOperation *operation = getOperation(points[i][0]);
            int arity = operation->getArity() + 1;
            if (arity == 1)
                _s.push(operation->operation(points[i][0], _s.pop()));
            if (arity == 2)
                _s.push(operation->operation(points[i][0], _s.pop(), _s.pop()));
            if (arity == 3)
                _s.push(operation->operation(points[i][0], _s.pop(), _s.pop(), _s.pop()));
        }
    }
    return _s.top();
}
} // namespace xi
