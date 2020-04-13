#ifndef GENCONDITIONSFACTORY_H
#define GENCONDITIONSFACTORY_H

#include <QtGlobal>
class Market;
class AgentBot;
class Gen;
class GenCondition;
class GenAction;

class GenFactory
{
public:
    GenFactory();

    static Gen* getRandomGen();
    static GenCondition* getRandomGenCondition();
    static GenAction*    getRandomGenAction();
};

//---------------------




#endif // GENCONDITIONSFACTORY_H
