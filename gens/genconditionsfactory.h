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

    Gen* getRandomGen();

private:
    GenCondition* getRandomGenCondition();
    GenAction*    getRandomGenAction();
};

//---------------------




#endif // GENCONDITIONSFACTORY_H
