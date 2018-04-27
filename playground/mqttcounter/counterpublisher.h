#ifndef COUNTERCLIENT_H
#define COUNTERCLIENT_H

#include <QtCore>

class MqttClient;

class CounterPublisher : public QObject
{
    Q_OBJECT    
    Q_PROPERTY(int count READ count WRITE setCount NOTIFY countChanged)
public:
    explicit CounterPublisher(QObject *parent = nullptr);
    Q_INVOKABLE void increment();
    Q_INVOKABLE void decrement();
    int count() const;
public slots:
    void setCount(int count);
    void onReceived(const QString& topic, const QVariantMap& data);
signals:
    void countChanged(int count);

private:
    MqttClient* m_client;
    int m_count;
};

#endif // COUNTERCLIENT_H
