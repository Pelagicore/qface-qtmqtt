#include "variantmodel.h"

namespace QFace { namespace MQTT {

VariantModel::VariantModel(QObject *parent)
    : QAbstractListModel(parent)
{
    m_roleNames.insert(VariantModel::Roles::ModelData, QByteArray("modelData"));
}

int VariantModel::count() const
{
    return m_data.count();
}

QVariant VariantModel::get(int index)
{
    return m_data.value(index);
}

int VariantModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_data.count();
}

QVariant VariantModel::data(const QModelIndex &index, int role) const
{
    if(index.row() < 0 || index.row() >= count()) {
        return QVariant();
    }
    const QVariant &entry = m_data.at(index.row());
    switch(role) {
    case Roles::ModelData:
        return entry;
    }
    return QVariant();
}

QHash<int, QByteArray> VariantModel::roleNames() const
{
    return m_roleNames;
}


void VariantModel::insert(int row, const QVariant &entry)
{
    if (row < 0) {
        row = 0;
    }
    if (row >= m_data.count()) {
        row = m_data.count();
    }

    beginInsertRows(QModelIndex(), row, row);
    m_data.insert(row, entry);
    endInsertRows();
    emit countChanged(count());
}

void VariantModel::reset(const QVariantList entries)
{
    beginResetModel();
    m_data = entries;
    endResetModel();
}

void VariantModel::append(const QVariant &entry)
{
    insert(m_data.count(), entry);
}

void VariantModel::update(int row, const QVariant &entry)
{
    if(row < 0 || row >= m_data.count()) {
        return;
    }
    m_data[row] = entry;
    const QModelIndex &index = createIndex(row, 0);
    emit dataChanged(index, index);
}

void VariantModel::remove(int row)
{
    if(row < 0 || row >= m_data.count()) {
        return;
    }
    beginRemoveRows(QModelIndex(), row, row);
    m_data.removeAt(row);
    endRemoveRows();
}

void VariantModel::clear()
{
    beginResetModel();
    m_data.clear();
    endResetModel();
}

}} // namespace QFace::MQTT

