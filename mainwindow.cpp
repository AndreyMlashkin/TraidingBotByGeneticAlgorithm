#include <QDebug>
#include <QPushButton>
#include <QFileDialog>
#include <QtAlgorithms>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "market.h"
#include "agentbot.h"
#include "gens/genconditionsfactory.h"

const int POPULATION_SIZE = 100;
const int GENERATIONS_COUNT = 100;

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
    QString filename = QFileDialog::getOpenFileName(nullptr, "Market History Data");
    Market::getMarketInstance().loadHistory(filename);

    historyLoaded();
}

void MainWindow::historyLoaded()
{
    initialGenerateAgents();

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
    return newGeneration;
}

