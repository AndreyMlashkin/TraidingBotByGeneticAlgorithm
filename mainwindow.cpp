#include <QJsonDocument>
#include <QJsonArray>
#include <QSaveFile>

#include <QRandomGenerator>
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
const int GENERATIONS_COUNT = 100;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->m_loadHistory,         &QPushButton::clicked, this, &MainWindow::loadHistory);
    connect(ui->m_loadSpecificHistory, &QPushButton::clicked, this, &MainWindow::loadSpecificHistory);
    connect(ui->m_loadAgents,          &QPushButton::clicked, this, &MainWindow::loadAgents);


    initialGenerateAgents();
}

MainWindow::~MainWindow()
{
    delete ui;
    qDeleteAll(m_agents);
}

void MainWindow::loadHistory()
{
    QString filename = "C:/Users/malas/Documents/build-GenBots-Desktop_Qt_5_13_1_MinGW_64_bit-Debug/DAT_MT_EURUSD_M1_202004.csv";
    Market::getMarketInstance().loadHistory(filename);
    historyLoaded();
}

void MainWindow::loadSpecificHistory()
{
    QString filename = QFileDialog::getOpenFileName(nullptr, "Market History Data");
    Market::getMarketInstance().loadHistory(filename);
    historyLoaded();
}

void MainWindow::loadAgents()
{
    QFile file("generation.json");
    Q_ASSERT(file.exists());
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
           return;

    qDeleteAll(m_agents);
    m_agents = stringToGeneration(file.readAll());
    //Q_ASSERT(m_agents.size() <= POPULATION_SIZE);
    Q_ASSERT(m_agents.size() > 0);

    printBotsStatistic();
    qDebug() << "generation loaded";
}

void MainWindow::historyLoaded()
{
    QElapsedTimer timer;
    timer.start();

    bool strikeOnce = true;
    int incomeGeneration = 0;
    for(int i = 0; i < GENERATIONS_COUNT; ++i)
    {
        Market::getMarketInstance().reset();
        qDebug() << QString(" ======= GENERATION #%1 =======").arg(i);
        trainGenerationOnLoadedHistory();

        std::sort(m_agents.begin(), m_agents.end(), [](const AgentBot* one, const AgentBot* another)
        {
            if(one->getEurosEstimation() > another->getEurosEstimation())
                return true;
            if(one->getEurosEstimation() < another->getEurosEstimation())
                return false;

            return one->gensCount() < another->gensCount();
        });

        if(strikeOnce && m_agents.first()->getEurosEstimation() > 2000)
        {
            strikeOnce = false;
            incomeGeneration = i;
        }

        if(i % 10 == 0)
        {
            printBotsStatistic();
            saveGeneration(m_agents);
        }
        QList<AgentBot *> newGeneration = produceNewGeneration();
        qDeleteAll(m_agents);
        m_agents = newGeneration;
    }
    //printBotsStatistic();
    qDebug() << "processing of " << GENERATIONS_COUNT << " generations took " << timer.elapsed() / 1000 << "seconds";
    qDebug() << "one generation takes " << timer.elapsed() / GENERATIONS_COUNT  << " miliseconds";
    qDebug() << "income from generation " << incomeGeneration;

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
    QList<AgentBot*> selectedOldGeneration = m_agents;

    // Elliminate NOOP agents and agents with too low performance
    for(int i = 0; i < selectedOldGeneration.size(); ++i)
    {
        double euroEstimation = selectedOldGeneration[i]->getEurosEstimation();

        if(euroEstimation == 2000 ||
           euroEstimation < 1)
        {
            selectedOldGeneration.removeAt(i);
            --i;
            continue;
        }

        if(i != 0 && euroEstimation == selectedOldGeneration[i - 1]->getEurosEstimation())
        {
            selectedOldGeneration.removeAt(i);
            --i;
            continue;
        }
    }
    Q_ASSERT(selectedOldGeneration.size() > 0);

    // Clone 10% best
    for(int i = 0; i < selectedOldGeneration.size() * 0.1; ++i)
    {
        newGeneration << dynamic_cast<AgentBot*>(selectedOldGeneration[i]->copy());
    }

    // mutate 90% of rest
    for(int i = 0; i < selectedOldGeneration.size() * 0.9; ++i)
    {
        AgentBot* newAgent = dynamic_cast<AgentBot*>(selectedOldGeneration[i]->copy());
        newAgent->mutate();
        newGeneration << newAgent;
    }

    // Crossover till 100 is reached
    int i = 0;
    while(newGeneration.size() < POPULATION_SIZE)
    {
        AgentBot* topAgent = dynamic_cast<AgentBot*>(selectedOldGeneration[i]->copy());

        quint32 randomPartnerSelector = QRandomGenerator::global()->generate();
        const quint32 variants = selectedOldGeneration.size();
        randomPartnerSelector %= variants;
        AgentBot* partner = selectedOldGeneration[randomPartnerSelector];
        AgentBot* newAgent = topAgent->crossover(partner);
        newGeneration << newAgent;

        ++i;
        i %= selectedOldGeneration.size();
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

void MainWindow::printBotsStatistic() const
{
    for(AgentBot* bot : m_agents)
    {
        qDebug() << "bot's money: " << bot->getEurosEstimation() << bot->toString();
    }
}

QList<AgentBot *> MainWindow::stringToGeneration(const QByteArray &jsonString)
{
    QJsonParseError error;
    QJsonDocument jsonDocument = jsonDocument.fromJson(jsonString, &error);
    qDebug() << "following errors occured during loading: " << error.errorString();

    QJsonArray array = jsonDocument.array();
    Q_ASSERT(array.size() > 0);

    QList<AgentBot *> result;
    for(const QJsonValue& value : array)
    {
        AgentBot* newBot = new AgentBot();
        newBot->deserialize(value.toObject());
        result << newBot;
    }
    return result;
}

QString MainWindow::generationToString(QList<AgentBot *> &bots)
{
    QJsonArray array;
    for(AgentBot* bot : bots)
    {
        QJsonObject serializedBot = bot->serialize();
        array.push_back(serializedBot);
    }

    QJsonDocument document(array);
    return document.toJson();
}

void MainWindow::saveGeneration(QList<AgentBot *> &bots)
{
    QSaveFile file("generation.json");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
           return;

    QTextStream out(&file);
    out << generationToString(bots);
    file.commit();
}

