#ifndef MARKET_H
#define MARKET_H

#include <QString>
#include <QFile>
#include <QDateTime>

static const double INVALID_DOUBLE = std::numeric_limits<double>::quiet_NaN();

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

    double getMaxBid() const;
    double getMinBid() const;

    double getMaxAsk() const;
    double getMinAsk() const;

    void loadHistory(const QString& historyFilePath);
    void reset();

    bool nextTick();

    void printHistory() const;

private:
    Market();
    void updateLimits();

    QFile m_marketHistoryFile;
    struct CurrentTickInfo
    {
        CurrentTickInfo(qint64 time, double ask, double bid) :
            m_time(time),
            m_ask(ask),
            m_bid(bid)
        {}

        QString toString() const;

        qint64 m_time;
        double m_ask;
        double m_bid;
    };

    QVector<CurrentTickInfo> m_history;
    int m_currentTick = 0;

    double m_cachedMaxBid = INVALID_DOUBLE;
    double m_cachedMinBid = INVALID_DOUBLE;

    double m_cachedMaxAsk = INVALID_DOUBLE;
    double m_cachedMinAsk = INVALID_DOUBLE;

};

#endif // MARKET_H
