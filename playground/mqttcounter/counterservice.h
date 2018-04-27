#ifndef COUNTERSERVICE_H
#define COUNTERSERVICE_H

#include <QtCore>

#include "counterservicebase.h"

class MqttClient;

class CounterService : public CounterServiceBase
{
    Q_OBJECT
public:
    explicit CounterService(QObject *parent = nullptr);
public:
    virtual void increment() override;
    virtual void decrement() override;
    virtual int count() const override;
    virtual void setCount(int count) override;
private:
    int m_count;
};

#endif // COUNTERSERVICE_H
