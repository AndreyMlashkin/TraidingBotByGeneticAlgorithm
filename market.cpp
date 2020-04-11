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
    if(m_marketHistory.isOpen())
        m_marketHistory.close();

    m_marketHistory.setFileName(historyFilePath);
    if (!m_marketHistory.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
}

void Market::reset()
{
    loadHistory(m_marketHistory.fileName());
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

    QDate date = QDate::fromString(words[0]);
    QTime time = QTime::fromString(words[1], "hh:mm");
    QDateTime datetime(date, time);
    m_time = datetime.toMSecsSinceEpoch();

    bool isOk;
    double price = QString(words[2]).toDouble(&isOk);
    Q_ASSERT(isOk);
    m_bid = price * (1 + MARGIN);
    m_ask = price * (1 - MARGIN);
    //qDebug() << "bid = " << m_bid << " ask = " << m_ask;
    return true;
}

Market::Market()
{

}
