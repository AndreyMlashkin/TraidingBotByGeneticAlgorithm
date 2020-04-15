#include <QtTest>
#include "../../gens/genconditionsfactory.h"
#include "../../gens/gencondition.h"
#include "gen.h"
#include "genconditionbid.h"

// add necessary includes here

class AgentBotTest : public QObject
{
    Q_OBJECT

public:
    AgentBotTest();
    ~AgentBotTest();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_mutations();
    void test_gens();
    void testBidCondition();

};

AgentBotTest::AgentBotTest()
{

}

AgentBotTest::~AgentBotTest()
{

}

void AgentBotTest::initTestCase()
{

}

void AgentBotTest::cleanupTestCase()
{

}

void AgentBotTest::test_mutations()
{
    QStringList mutatableClasses = {"GenConditionNoop",
                                   "GenConditionAsk",
                                   "GenConditionBid",
                                   "GenActionBuy",
                                   "GenActionSell"
                                   };

    for(const QString& className : mutatableClasses)
    {
        Mutatable* mutatable = GenFactory::getMutatableByClassName(className);
        for(int i = 0; i < 100; ++i)
            mutatable->mutate();
        qDebug() << "aftern 100 mutations: " << mutatable->toString();
        delete mutatable;
    }
}

void AgentBotTest::test_gens()
{
    Gen* gen = GenFactory::getRandomGen();
    for(int i = 0; i < 10; ++i)
    {
        gen->mutate();
        qDebug() << QString("mutation %1: %2")
                    .arg(i)
                    .arg(gen->toString());
    }
    qDebug() << "aftern 10 mutations: " << gen->toString();
    delete gen;
}

void AgentBotTest::testBidCondition()
{
    GenCondition* condition = GenFactory::getRandomGenCondition();
    while(!dynamic_cast<GenConditionBid*>(condition))
    {
        delete condition;
        condition = GenFactory::getRandomGenCondition();
    }
    GenConditionBid* bidCondition = dynamic_cast<GenConditionBid*>(condition);
    qDebug() << "random bid condition: " << bidCondition->toString();
    QVERIFY(std::isnan(bidCondition->m_strikeBid) == false);
}

QTEST_APPLESS_MAIN(AgentBotTest)

#include "tst_agentbottest.moc"
