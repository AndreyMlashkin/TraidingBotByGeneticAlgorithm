#ifndef GENCONDITIONSFACTORY_H
#define GENCONDITIONSFACTORY_H

#include <QtGlobal>
class Market;
class AgentBot;
class Gen;
class GenCondition;
class GenAction;
class Mutatable;

class GenFactory
{
public:
    GenFactory();

    static Gen* getRandomGen();
    static GenCondition* getRandomGenCondition();
    static GenAction*    getRandomGenAction();

    static GenCondition *getConditionByClassName(const QString& className);
    static GenAction    *getActionByClassName   (const QString& className);
    static Mutatable    *getMutatableByClassName(const QString& className);
};

//---------------------




#endif // GENCONDITIONSFACTORY_H
