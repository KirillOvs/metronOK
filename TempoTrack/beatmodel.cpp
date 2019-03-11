#include "beatmodel.h"
#include "baritem.h"
#include "beatitem.h"
#include <QDebug>
#include <QThread>

namespace  models {

BeatModel::BeatModel(QObject *parent)
    : QAbstractListModel(parent)
{}

int BeatModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0;
    }

    return m_data.size();
}
QVariant BeatModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    switch (role) {
    case TempoRole:
        return QVariant(m_data.at(index.row())->getTempo());
    case IsActiveRole:
        return QVariant(m_data.at(index.row())->isActive());
    case CoordinateY_Role:
        return QVariant(m_data.at(index.row())->coordinateY());
    case IsOwnerBarLockedRole:
        return QVariant(m_data.at(index.row())->isOwnerBarLocked());
    default:
        return QVariant();
    }
}
QHash<int, QByteArray> BeatModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles[TempoRole] = "tempo";
    roles[IsActiveRole] = "isActive";
    roles[CoordinateY_Role] = "y";
    roles[IsOwnerBarLockedRole] = "isOwnerBarLocked";
    roles[CurrentBeatRole] = "currentBeat";
    return roles;
}
bool BeatModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid()) {
        return false;
    }

    switch (role) {
    case CurrentBeatRole:
        emit currentBeatSet(m_data[index.row()]->ownerBarId(), static_cast<uint16_t>(value.toInt()));
        break;
    case TempoRole:
    case CoordinateY_Role:
    {        
        int i = index.row();
        if(m_data[i]->isOwnerBarLocked())
            return false;
        uint16_t val = static_cast<uint16_t>(value.toInt());
        int barId = m_data[i]->ownerBarId();
        bool selected = m_data[i]->isOwnerBarSelected();
        // TODO: if isOwnerBarHeld i = 0
        while(i < m_data.count()) {
            if(role == TempoRole) m_data[i]->setTempo(val);
            if(role == CoordinateY_Role) m_data[i]->setCoordinateY(val);
            ++i;
            if(selected) break;
        }
        QModelIndex endIndex = createIndex(i - 1, 0);
        emit dataChanged(index, endIndex, QVector<int>() << role);
        if(!selected)
            emit tempoOrCoordinateYChanged(barId, val, role);
    }
        break;
    case IsActiveRole:
        m_data[index.row()]->setActive(value.toBool());
        emit dataChanged(index, index, QVector<int>() << role);
        break;
    default:
        return false;
    }


    return true;
}
Qt::ItemFlags BeatModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractListModel::flags(index) | Qt::ItemIsEditable;
}
void BeatModel::add(const uint8_t tempo, const items::BarItem* const barOwner)
{
    // i have no idea why sometimes i get invalid model when its members are "not accessible", i think this is qt bug
    auto size = m_data.size();
    beginInsertRows(QModelIndex(), size, size);
    int n = this->rowCount() + 1;
    m_data.append(QSharedPointer<items::BeatItem>(new items::BeatItem(tempo, n, barOwner)));
    //m_data.append(new items::BeatItem(tempo, n, barOwner));
    endInsertRows();
    //emit countChanged();
}
void BeatModel::removeLast()
{
    auto size = this->rowCount();
    if(size == 2) return;
    beginRemoveRows(QModelIndex(), size-1, size-1);
    m_data.removeLast();
    endRemoveRows();
    //emit countChanged();
}

} // namespace models
