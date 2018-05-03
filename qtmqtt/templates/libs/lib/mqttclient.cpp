#include "mqttclient.h"
#include "{{module.module_name|lower}}shared.h"

MqttClient::MqttClient(QObject *parent)
    : QObject(parent)
    , m_client(nullptr)
    , m_connected(false)
    , m_packageId(0)
{
    qCDebug(mqttClient) << __func__;

    QUrl url(qEnvironmentVariable("MQTT_URL", "tcp://127.0.0.1:1883"));
    m_client = new QMQTT::Client(QHostAddress(url.host()), url.port(), this);
    connect(m_client, &QMQTT::Client::connected, this, &MqttClient::onConnected);
    connect(m_client, &QMQTT::Client::disconnected, this, &MqttClient::onDisconnected);
    connect(m_client, &QMQTT::Client::subscribed, this, &MqttClient::onSubscribed);
    connect(m_client, &QMQTT::Client::received, this, &MqttClient::onReceived);
    connect(m_client, &QMQTT::Client::error, this, &MqttClient::onError);
    m_client->connectToHost();
}

void MqttClient::subscribe(const QString &topic)
{
    qCDebug(mqttClient) << __func__;
    m_subscriptions.enqueue(topic);
    process();
}

void MqttClient::unsubscribe(const QString &topic)
{
    qCDebug(mqttClient) << __func__;
    if(!m_client) {
        return;
    }
    m_client->unsubscribe(topic);
}

void MqttClient::publish(const QString &topic, const QVariantMap &data)
{
    qCDebug(mqttClient) << __func__ << "topic:" << topic << " data:" << data;
    QJsonDocument doc = QJsonDocument::fromVariant(data);
    QByteArray payload = doc.toJson();

    QMQTT::Message message(nextPackageId(), topic, payload);
    m_messages.enqueue(message);
    process();
}

bool MqttClient::connected() const
{
    return m_connected;
}

int MqttClient::nextPackageId()
{
    qCDebug(mqttClient) << __func__;
    m_packageId++;
    return m_packageId;
}

void MqttClient::setConnected(bool connected)
{
    qCDebug(mqttClient) << __func__ << connected;
    if (m_connected == connected)
        return;

    m_connected = connected;
    emit connectedChanged(m_connected);
    process();
}

void MqttClient::process()
{
    qCDebug(mqttClient) << __func__;

    if(!m_client || !connected()) {
        return;
    }
    while(!m_subscriptions.isEmpty()) {
        QString topic = m_subscriptions.dequeue();
        qDebug() << "subscribe to " << topic;
        m_client->subscribe(topic);
    }
    while(!m_messages.isEmpty()) {
        const QMQTT::Message& message = m_messages.dequeue();
        qDebug() << "publish message topic:" << message.topic();
        m_client->publish(message);
    }
}

void MqttClient::onConnected()
{
    setConnected(true);
}

void MqttClient::onDisconnected()
{
    setConnected(false);
}

void MqttClient::onSubscribed(const QString &topic)
{
    qCDebug(mqttClient) << __func__ <<  topic;
}

void MqttClient::onReceived(const QMQTT::Message &message)
{
    qCDebug(mqttClient) << __func__;
    QString topic = message.topic();
    QJsonDocument doc = QJsonDocument::fromJson(message.payload());
    QVariantMap data = doc.toVariant().toMap();
    emit received(topic, data);
}

void MqttClient::onError(const QMQTT::ClientError error)
{
    qCDebug(mqttClient) << __func__ << error;
}
