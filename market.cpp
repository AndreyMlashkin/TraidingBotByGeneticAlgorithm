#include <QDebug>
#include <QDateTime>

#include "market.h"

const double MARGIN = 0.05;

Market::~Market()
{
    m_marketHistory.close();
}

double Market::getBid() const
{
    return m_bid;
}

double Market::getAsk() const
{
    return m_ask;
}

qint64 Market::currentTime() const
{
    return m_time;
}

void Market::loadHistory(const QString &historyFilePath)
{
    m_marketHistory.setFileName(historyFilePath);
    if (!m_marketHistory.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
}

bool Market::nextTick()
{
    if(m_marketHistory.atEnd())
    {
        qDebug() << Q_FUNC_INFO << " file is at the end";
        return false;
    }

    //Row Fields:
    // DateTime Stamp;Bar OPEN Bid Quote;Bar HIGH Bid Quote;Bar LOW Bid Quote;Bar CLOSE Bid Quote;Volume

    QByteArray line = m_marketHistory.readLine();
    QList<QByteArray> words = line.split(',');
    Q_ASSERT(words.size() == 7);
    QDateTime time = QDateTime::fromString(words[0]);
    m_time = time.toMSecsSinceEpoch();

    bool isOk;
    double price = QString(words[1]).toDouble(&isOk);
    Q_ASSERT(isOk);
    m_bid = price * (1 + MARGIN);
    m_ask = price * (1 - MARGIN);
    return true;
}

Market::Market()
{

}
