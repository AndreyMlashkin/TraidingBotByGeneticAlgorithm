#include <QDebug>
#include <QPushButton>
#include <QFileDialog>
#include <QtAlgorithms>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "market.h"
#include "agentbot.h"
#include "gens/genconditionsfactory.h"

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

    while(Market::getMarketInstance().nextTick())
    {
        for(AgentBot* bot : m_agents)
        {
            bot->nextTick();
        }
    }

    std::sort(m_agents.begin(), m_agents.end(), [](const AgentBot* one, const AgentBot* another)
    {
        return one->getEurosEstimation() < another->getEurosEstimation();
    });

    for(AgentBot* bot : m_agents)
    {
        qDebug() << "bot's money: " << bot->getEurosEstimation();
    }
}

void MainWindow::initialGenerateAgents()
{
    qDeleteAll(m_agents);
    GenFactory factory;
    for(int i = 0; i < 100; ++i)
    {
        AgentBot* bot = new AgentBot({factory.getRandomGen(), factory.getRandomGen()});
        m_agents << bot;
    }
}

