#include <QDebug>
#include <QDateTime>

#include "market.h"

Market::~Market()
{
    m_marketHistoryFile.close();
}

double Market::getBid() const
{
    return m_history[m_currentTick].m_bid;
}

double Market::getAsk() const
{
    return m_history[m_currentTick].m_ask;
}

qint64 Market::currentTime() const
{
    return m_history[m_currentTick].m_time;
}

void Market::loadHistory(const QString &historyFilePath)
{
    m_history.clear();
    m_history = {};

    if(m_marketHistoryFile.isOpen())
        m_marketHistoryFile.close();

    m_marketHistoryFile.setFileName(historyFilePath);
    if (!m_marketHistoryFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    while(!m_marketHistoryFile.atEnd())
    {
        //Row Fields:
        // DateTime Stamp;Bar OPEN Bid Quote;Bar HIGH Bid Quote;Bar LOW Bid Quote;Bar CLOSE Bid Quote;Volume

        QByteArray line = m_marketHistoryFile.readLine();
        QList<QByteArray> words = line.split(',');
        Q_ASSERT(words.size() == 7);

        QDate date = QDate::fromString(words[0]);
        QTime time = QTime::fromString(words[1], "hh:mm");
        QDateTime datetime(date, time);
        qint64 currentTime = datetime.toMSecsSinceEpoch();

        bool isOk;
        double ask = QString(words[2]).toDouble(&isOk);
        double bid = QString(words[3]).toDouble(&isOk);

        m_history.push_back(CurrentTickInfo(currentTime, ask, bid));

        static int count = 0;
        qDebug() << "bid = " << bid << " ask = " << ask << " iteration = " << count++;

    }
    printHistory();
    m_currentTick = 0;
}

void Market::reset()
{
//    loadHistory(m_marketHistory.fileName());
    m_currentTick = 0;
}

bool Market::nextTick()
{
    ++m_currentTick;
    if(m_currentTick >= m_history.size() - 1)
        return false;

    return  true;


}

void Market::printHistory() const
{
    qDebug() << "history size = " << m_history.size();
    for(int i = 0; i < m_history.size(); ++i)
    {
        const CurrentTickInfo& info = m_history[i];
        qDebug() << QString("iteration %1; %2")
                    .arg(i)
                    .arg(info.toString());
    }
}

Market::Market() :
    m_currentTick(0)

{

}

QString Market::CurrentTickInfo::toString() const
{
    return QString("Time = %1; Ask = %2; Bid = %3;")
            .arg(m_time)
            .arg(m_ask)
            .arg(m_bid);

}
