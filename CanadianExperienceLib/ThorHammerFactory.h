/**
 * @file ThorHammerFactory.h
 * @author Josh Thomas
 *
 *
 */
 
#ifndef FLAGFACTORY_H
#define FLAGFACTORY_H

#include <memory>
#include <string>
class Actor;

/**
 * Factory class that builds the Flag actor.
 */
class ThorHammerFactory
{
public:
 std::shared_ptr<Actor> Create();
};




#endif //FLAGFACTORY_H
