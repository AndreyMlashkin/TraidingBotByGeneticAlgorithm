#ifndef GENCONDITIONSFACTORY_H
#define GENCONDITIONSFACTORY_H

#include <QtGlobal>
class Market;

class GenCondition
{
public:
    virtual ~GenCondition() {}
    virtual bool operator() () = 0;
};

class AgentBot;
class GenAction
{
public:
    virtual ~GenAction() {}
    virtual void operator() (AgentBot&) = 0;
};

class Gen;
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
class Market;

class GenConditionNoop : public GenCondition
{
public:
    GenConditionNoop() {}
    virtual bool operator() () override { return true; }
};

class GenConditionBid : public GenCondition
{
public:
    GenConditionBid(double initialStrikeBid = 0);
    virtual bool operator() () override;

private:
    double m_strikeBid;
};

class GenConditionAsk : public GenCondition
{
public:
    GenConditionAsk(double initialStrikeAsk = 0);
    virtual bool operator() () override;

private:
    double m_strikeAsk;
};
//---------------------

class AgentBot;
class GenActionBuy : public GenAction
{
public:
    GenActionBuy(double ammount = 1);
    void operator() (AgentBot& parent) override;

private:
    double m_ammount;
};

class GenActionSell : public GenAction
{
public:
    GenActionSell(double ammount = 1);
    void operator() (AgentBot& parent) override;

private:
    double m_ammount;
};


#endif // GENCONDITIONSFACTORY_H
