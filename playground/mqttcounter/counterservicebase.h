#ifndef COUNTERSERVICEBASE_H
#define COUNTERSERVICEBASE_H

#include <QtCore>

class MqttClient;

class CounterServiceBase : public QObject
{
    Q_OBJECT
public:
    explicit CounterServiceBase(QObject *parent = nullptr);
    virtual void increment() = 0;
    virtual void decrement() = 0;
    virtual int count() const = 0;
    virtual void setCount(int count) = 0;
protected:
    void publish(const QString& topic, const QVariantMap& data);
public slots:
    void onReceived(const QString& topic, const QVariantMap& data);
private:
    MqttClient *m_peer;
};

#endif // COUNTERSERVICEBASE_H
