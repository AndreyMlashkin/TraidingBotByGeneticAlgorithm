#ifndef MARKET_H
#define MARKET_H

#include <QString>
#include <QFile>

class Market
{
public:
    ~Market();
    static Market& getMarketInstance()
    {
        static Market instance;
        return instance;
    }
    double getBid() const;
    double getAsk() const;
    qint64 currentTime() const;

    void loadHistory(const QString& historyFilePath);

    bool nextTick();

private:
    Market();

    QFile m_marketHistory;
    double m_bid;
    double m_ask;
    qint64 m_time;

};

#endif // MARKET_H
