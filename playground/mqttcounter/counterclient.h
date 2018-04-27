#ifndef COUNTERCLIENT_H
#define COUNTERCLIENT_H

#include <QtCore>

class MqttClient;

class CounterClient : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int count READ count WRITE setCount NOTIFY countChanged)
public:
    explicit CounterClient(QObject *parent = nullptr);
    Q_INVOKABLE void increment();
    Q_INVOKABLE void decrement();
    int count() const;
signals:
    void countChanged(int count);
public slots:
    void setCount(int count);
    void onReceived(const QString& topic, const QVariantMap& data);
private:
    MqttClient *m_connection;
    int m_count;
};

#endif // COUNTERCLIENT_H
