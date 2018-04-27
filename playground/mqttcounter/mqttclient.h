#ifndef MQTTCLIENT_H
#define MQTTCLIENT_H

#include <QtCore>
#include <qmqtt.h>

struct Message {
    QString topic;
    QVariant data;
};


class MqttClient : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool connected READ connected WRITE setConnected NOTIFY connectedChanged)
public:
    explicit MqttClient(QObject *parent = nullptr);
    Q_INVOKABLE void subscribe(const QString& topic);
    Q_INVOKABLE void unsubscribe(const QString& topic);
    Q_INVOKABLE void publish(const QString& topic, const QVariantMap& data=QVariantMap());
    bool connected() const;
    int nextPackageId();
private:
    void setConnected(bool connected);
    void process();
public slots:
    void onConnected();
    void onDisconnected();
    void onSubscribed(const QString& topic);
    void onReceived(const QMQTT::Message& message);
    void onError(const QMQTT::ClientError error);
signals:
    void received(const QString& topic, const QVariantMap& data);
    void connectedChanged(bool connected);

private:
    QMQTT::Client* m_client;
    QQueue<QMQTT::Message> m_messages;
    QQueue<QString> m_subscriptions;
    bool m_connected;
    int m_packageId;
};



#endif // MQTTPEER_H
