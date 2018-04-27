#include "counterpublisher.h"
#include "mqttclient.h"

CounterPublisher::CounterPublisher(QObject *parent)
    : QObject(parent)
    , m_client(new MqttClient(this))
    , m_count(0)
{
    qDebug() << __func__;
    connect(m_client, &MqttClient::received, this, &CounterPublisher::onReceived);
    m_client->subscribe("count/Counter/#");

}
void CounterPublisher::increment()
{
    qDebug() << __func__;
    m_client->publish("count/Counter/increment");
}

void CounterPublisher::decrement()
{
    qDebug() << __func__;
    m_client->publish("count/Counter/decrement");
}

int CounterPublisher::count() const
{
    qDebug() << __func__;
    return m_count;
}

void CounterPublisher::setCount(int count)
{
    qDebug() << __func__;
    m_client->publish("count/Counter/count", {{"count", count}});
}

void CounterPublisher::onReceived(const QString &topic, const QVariantMap &data)
{
    qDebug() << __func__ << topic << " data:" << data;
    if(topic == "count/Counter/increment") {
        setCount(m_count+1);
    } else if(topic == "count/Counter/decrement") {
        setCount(m_count-1);
    } else if(topic == "count/Counter/count") {
        int count = data.value("count", m_count).toInt();
        m_count = count;
        emit countChanged(m_count);
    }
}
