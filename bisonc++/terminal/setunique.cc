#include "terminal.ih"

bool Terminal::setUnique(size_t/*unsigned*/ value) 
{
    if (s_valueSet.count(value))
        return false;               // value already used

    s_valueSet.insert(value);
    return true;
}
