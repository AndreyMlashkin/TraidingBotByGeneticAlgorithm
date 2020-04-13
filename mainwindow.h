#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class AgentBot;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void loadHistory();

private:
    void historyLoaded();
    void initialGenerateAgents();

    void trainGenerationOnLoadedHistory();
    QList<AgentBot*> produceNewGeneration() const;
    static void resetMoney(QList<AgentBot*>& bots);
    void printBotsStatistic() const;

private:
    Ui::MainWindow *ui;
    QList<AgentBot*> m_agents;
};
#endif // MAINWINDOW_H
