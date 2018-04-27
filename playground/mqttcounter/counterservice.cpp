#include "counterservice.h"

#include "countershared.h"

CounterService::CounterService(QObject *parent)
    : CounterServiceBase(parent)
    , m_count(0)
{
    qCDebug(counterService) << __func__;
}

void CounterService::increment()
{
    qCDebug(counterService) << __func__;
    setCount(count() + 1);
}

void CounterService::decrement()
{
    qCDebug(counterService) << __func__;
    setCount(count() - 1);
}

int CounterService::count() const
{
    qCDebug(counterService) << __func__;
    return m_count;
}

void CounterService::setCount(int count)
{
    qCDebug(counterService) << __func__;
    if(m_count == count) {
        return;
    }
    m_count = count;
    publish("count/Counter/count", QVariantMap{{"count", count}});
}
