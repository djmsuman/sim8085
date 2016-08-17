#include "../libs/core.h"
#include <algorithm>

Ram::Ram(int SIZE)
    : memory(NULL), _refcount(0), _currentpos(0), _SIZE(SIZE)
{
    memory = new Byte[SIZE];
    std::fill(memory, memory + SIZE, 0);
}

Ram::Ram(Ram &r)
    : memory(r.memory), _currentpos(r._currentpos), usedAddress(r.usedAddress), loadedAddress(r.loadedAddress)
{
    _refcount = ++r._refcount;
}

Ram::~Ram()
{
    if (memory && _refcount <= 0)
        delete memory;
    else
        --_refcount;
}
void Ram::clear()
{
    std::fill(memory, memory + _SIZE, 0);
    usedAddress.clear();
    loadedAddress.clear();
}
Byte &Ram::operator[](const Byte2 addr)
{
    if (usedAddress.empty())
        usedAddress.push_back(addr);
    else // if addr is not in usedAddress then
        if (find(usedAddress.begin(), usedAddress.end(), addr) == usedAddress.end())
        usedAddress.push_back(addr);
    return memory[addr];
}

void Ram::append_inst(Byte val)
{
    memory[_currentpos] = val;
    if (!loadedAddress.empty())
        if (find(loadedAddress.begin(), loadedAddress.end(), _currentpos) != loadedAddress.end())
        {
            ++_currentpos;
            return; // _currentpos is already in loadedAddress vector
        }
    loadedAddress.push_back(_currentpos);
    ++_currentpos; // In both cases increment _currentpos after it is added to the list
}

Byte2 Ram::jump(Byte2 nextNibleoffset)
{
    _currentpos = nextNibleoffset;
    return _currentpos;
}

Ram::AddrIter Ram::uaBegin()
{
    return usedAddress.begin();
}

Ram::AddrIter Ram::uaEnd()
{
    return usedAddress.end();
}

Ram::AddrIter Ram::laBegin()
{
    return loadedAddress.begin();
}

Ram::AddrIter Ram::laEnd()
{
    return loadedAddress.end();
}
