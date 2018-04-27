#include "counterclient.h"
#include "mqttclient.h"
#include "countershared.h"

CounterClient::CounterClient(QObject *parent)
    : QObject(parent)
    , m_connection(new MqttClient(this))
    , m_count(0)
{
    qCDebug(counterClient) << __func__;
    connect(m_connection, &MqttClient::received, this, &CounterClient::onReceived);
    m_connection->subscribe("count/Counter/#");
}

void CounterClient::increment()
{
    qCDebug(counterClient) << __func__;
    m_connection->publish("count/Counter/increment");
}

void CounterClient::decrement()
{
    qCDebug(counterClient) << __func__;
    m_connection->publish("count/Counter/decrement");
}

int CounterClient::count() const
{
    qCDebug(counterClient) << __func__;
    return m_count;
}

void CounterClient::setCount(int count)
{
    qCDebug(counterClient) << __func__;
    if (m_count == count)
        return;

    m_count = count;
    emit countChanged(m_count);
}

void CounterClient::onReceived(const QString &topic, const QVariantMap &data)
{
    qCDebug(counterClient) << __func__ << topic << data;
    if(topic == "count/Counter/count") {
        setCount(data.value("count").toInt());
    }
}
