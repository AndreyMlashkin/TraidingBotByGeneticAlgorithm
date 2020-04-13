#include <QDebug>
#include <QPushButton>
#include <QFileDialog>
#include <QtAlgorithms>
#include <QElapsedTimer>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "market.h"
#include "agentbot.h"
#include "gens/genconditionsfactory.h"

const int POPULATION_SIZE = 100;
const int GENERATIONS_COUNT = 1000;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->m_loadHistory, &QPushButton::clicked, this, &MainWindow::loadHistory);
}

MainWindow::~MainWindow()
{
    delete ui;
    qDeleteAll(m_agents);
}

void MainWindow::loadHistory()
{
    QString filename = "C:/Users/malas/Documents/build-GenBots-Desktop_Qt_5_13_1_MinGW_64_bit-Debug/DAT_MT_EURUSD_M1_202004.csv";
            //QFileDialog::getOpenFileName(nullptr, "Market History Data");
    Market::getMarketInstance().loadHistory(filename);

    historyLoaded();
}

void MainWindow::historyLoaded()
{
    initialGenerateAgents();

    QElapsedTimer timer;
    timer.start();

    for(int i = 0; i < GENERATIONS_COUNT; ++i)
    {
        Market::getMarketInstance().reset();
        qDebug() << QString(" ======= GENERATION #%1 =======").arg(i);
        trainGenerationOnLoadedHistory();

        std::sort(m_agents.begin(), m_agents.end(), [](const AgentBot* one, const AgentBot* another)
        {
            return one->getEurosEstimation() > another->getEurosEstimation();
        });
        for(AgentBot* bot : m_agents)
        {
            qDebug() << "bot's money: " << bot->getEurosEstimation() << bot->toString();
        }

        QList<AgentBot *> newGeneration = produceNewGeneration();
        qDeleteAll(m_agents);
        m_agents = newGeneration;
    }
    qDebug() << "processing of " << GENERATIONS_COUNT << " generations took " << timer.elapsed() << "milliseconds";
}

void MainWindow::initialGenerateAgents()
{
    qDeleteAll(m_agents);
    GenFactory factory;
    for(int i = 0; i < POPULATION_SIZE; ++i)
    {
        AgentBot* bot = new AgentBot({factory.getRandomGen(), factory.getRandomGen()});
        m_agents << bot;
    }
}

void MainWindow::trainGenerationOnLoadedHistory()
{
    while(Market::getMarketInstance().nextTick())
    {
        for(AgentBot* bot : m_agents)
        {
            bot->nextTick();
        }
    }
}

QList<AgentBot *> MainWindow::produceNewGeneration() const
{
    QList<AgentBot*> newGeneration;    

    // Take 10% best
    for(int i = 0; i < POPULATION_SIZE * 0.1; ++i)
    {
        if(m_agents[i]->getEurosEstimation() == 2000)
            m_agents[i]->mutate();
        newGeneration << dynamic_cast<AgentBot*>(m_agents[i]->copy());
    }

    // mutate 90% of rest
    for(int i = 0; i < POPULATION_SIZE * 0.9; ++i)
    {
        AgentBot* newAgent = dynamic_cast<AgentBot*>(m_agents[i]->copy());
        newAgent->mutate();
        newGeneration << newAgent;
    }
    Q_ASSERT(newGeneration.size() == POPULATION_SIZE);
    resetMoney(newGeneration);
    return newGeneration;
}

void MainWindow::resetMoney(QList<AgentBot *> &bots)
{
    for(AgentBot* bot : bots)
    {
        bot->setEuros(2000);
        bot->setCurrency(0);
    }
}

