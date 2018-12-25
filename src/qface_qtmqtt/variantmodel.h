#pragma once

#include <QtCore>

namespace QFace { namespace MQTT {

class VariantModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ count NOTIFY countChanged)
public:
    enum Roles { ModelData = Qt::UserRole };
    VariantModel(QObject *parent = nullptr);
    Q_INVOKABLE QVariant get(int index);
    int count() const;
    void insert(int row, const QVariant &entry);
    void append(const QVariant &entry);
    void update(int row, const QVariant &entry);
    void remove(int row);
    void reset(const QVariantList entries);
    void clear();
public: // from QAbstractListModel
    virtual int rowCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual QHash<int, QByteArray> roleNames() const;
Q_SIGNALS:
   void countChanged(int count);
private:
    QVariantList m_data;
    QHash<int, QByteArray> m_roleNames;
};

}} // namespace QFace::MQTT



