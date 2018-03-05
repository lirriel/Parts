#include <iostream>
#include "parts.h"


void Part::describe()
{
    std::cout << "Part " + name + " subparts are:" << std::endl;

    for (const auto& subpart: subparts)
        std::cout << subpart.second << " " << subpart.first->name << std::endl;

    if (subparts.size() == 0)
        std::cout << "It has no subparts" << std::endl;
}


int Part::countHowMany(const Part* p)
{
    if (p->parent == 0 || p == this)
        return 0;

    Part* parent = p->parent;
    int count = 0;
    for (NodeToCount::iterator it = parent->subparts.begin(); it != parent->subparts.end(); it++)
        if ((*it).first == p)
            count = (*it).second;

    while (parent->parent != 0 && parent != this)
    {
        Part* current = parent;
        parent = parent->parent;

        count *= parent->subparts[current];
    }

    if (parent != this)
        return 0;

    return count;
}


Part &Part::operator=(const Part &other) {
    if (this  != &other)
    {
        name = other.name;
        parent = other.parent;
        subparts = other.subparts;
    }
    return *this;
}


NameContainer::~NameContainer()
{
    for (NameToNode::iterator it = _nameMap.begin(); it != _nameMap.end(); it++)
    {
        Part* p = (*it).second;
        delete p;
        p = nullptr;
    }
}


NameContainer& NameContainer::operator=(const NameContainer &other)
{
    _nameMap = other._nameMap;
}


Part* NameContainer::lookup(const std::string &name)
{
    if (_nameMap[name] == 0)
        _nameMap[name] = new Part(name);

    return _nameMap[name];
}


void NameContainer::addPart(const std::string &part, int quantity, const std::string &subpart)
{
    Part* part1 = lookup(part);
    Part* part2 = lookup(subpart);

    part2->setParent(part1);

    if (part1->subparts[part2] == 0)
        part1->subparts[part2] = quantity;
}