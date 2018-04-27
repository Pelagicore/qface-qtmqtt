#include "counterservicebase.h"
#include "mqttclient.h"

#include "countershared.h"

CounterServiceBase::CounterServiceBase(QObject *parent)
    : QObject(parent)
    , m_peer(new MqttClient(this))
{
    qCDebug(counterService) << __func__;
    connect(m_peer, &MqttClient::received, this, &CounterServiceBase::onReceived);
    m_peer->subscribe("count/Counter/#");
}

void CounterServiceBase::publish(const QString &topic, const QVariantMap &data)
{
    qCDebug(counterService) << __func__ << topic << data;
    m_peer->publish(topic, data);
}


void CounterServiceBase::onReceived(const QString &topic, const QVariantMap &data)
{
    qCDebug(counterService) << __func__ << topic << data;
    if(topic == "count/Counter/increment") {
        increment();
    } else if(topic == "count/Counter/decrement") {
        decrement();
    } else if(topic == "count/Counter/count") {
        setCount(data.value("count").toInt());
    }
}
