#include "barmodel.h"
#include "baritem.h"
#include "beatmodel.h"
#include "beatitem.h"
#include "currentbeat.h"
#include <QDebug>

namespace models {

BarModel::BarModel(QObject *parent)
    : QAbstractListModel (parent)
    , m_isWorking(false)
{
//    this->addBar();
//    this->addBar();
//    this->addBar();
//    this->addBar();
//    this->addBar();
    for (int i = 0; i < 200; ++i) {
        this->addBar();
    }
}

QVariant BarModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    switch (role) {
    case BarDimensionRole:
        return QVariant(m_track.at(index.row())->getDimension());
    case BarSizeRole:
        return QVariant(m_track.at(index.row())->getBarSize());
    case BarSelectedRole:
        return QVariant(m_track.at(index.row())->isSelected());
    case BarMarkedRole:
        return QVariant(m_track.at(index.row())->isMarked());
    case BarMarkerTextRole:
        return QVariant(m_track.at(index.row())->getMarkerText());
    case BarHeldRole:
        return QVariant(m_track.at(index.row())->isHeld());
    case BarLockedRole:
        return QVariant(m_track.at(index.row())->isLocked());
    case TrackLockedRole:
        return QVariant(m_track.isTrackLocked());
    case TrackHeldRole:
        return QVariant(m_track.isHeld());
    case TrackPreCountRole:
        return QVariant(m_track.getPreCount());
    default:
        return {};
    }
}

QHash<int, QByteArray> BarModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles[BarDimensionRole] = "dimension";
    roles[BarSizeRole] = "size";
    roles[BarSelectedRole] = "selected";
    roles[BarMarkedRole] = "marked";
    roles[BarMarkerTextRole] = "markerText";
    roles[BarLockedRole] = "locked";
    roles[BarHeldRole] = "held";
    roles[TrackLockedRole] = "trackLocked";
    roles[TrackHeldRole] = "trackHeld";
    roles[TrackPreCountRole] = "preCountNum";
    return roles;
}

void BarModel::addBar()
{
    //if(m_track.isLocked())
    //    return;

    auto count = m_track.size();
    beginInsertRows(QModelIndex(), count, count);

    items::BarItem* elemPtr = new items::BarItem(m_track.getBeatsNumber(), m_track.getDimension(), count);
    if(count == 0)
        elemPtr->mark(true, "Precount");
    if(count == m_track.getPreCount())
        elemPtr->mark(true, "Intro");
    const BeatModel* beatModel = elemPtr->getBeatModel();
    connect(beatModel, &BeatModel::tempoOrCoordinateYChanged, this, &BarModel::onTempoOrCoordinateYChanged);
    connect(beatModel, &BeatModel::currentBeatSet, this, &BarModel::onCurrentBeatSet);
    m_track.append(QSharedPointer<items::BarItem>(elemPtr));
    //m_track.insert(m_track.getPreCount(), std::move(QSharedPointer<items::BarItem>(elemPtr)));
    endInsertRows();
    emit countChanged();    
}

void BarModel::removeBar(const int id)
{
    auto count = m_track.size();
    if(id < 0) {
        beginRemoveRows(QModelIndex(), count-1, count-1);
        m_track.removeLast();
        endRemoveRows();
    }
    else if(id < rowCount() - 1) {
        m_track.removeAt(id);
    }
    emit countChanged();
}

void BarModel::onTempoOrCoordinateYChanged(const uint32_t barId, const uint16_t val, const int role)
{
    int nextBarIndex = static_cast<int>(barId+1);

    if(!this->hasIndex(nextBarIndex, 0))
        return;

    QModelIndex idx = createIndex(0, 0);
    m_track.at(nextBarIndex)->getBeatModel()->setData(idx, QVariant(val), role);
}

void BarModel::actionForeach(const BarModel::Roles role, QVariant val)
{
    for(int i = 0, size = rowCount(); i < size; ++i) {
        setData(createIndex(i, 0), QVariant(val), role);
    }
}

bool BarModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid()) {
        return false;
    }

    QVector<int> vec { role };
    switch (role) {
    case BarDimensionRole:
        m_track[index.row()]->setDimension(static_cast<uint8_t>(value.toInt()));
        break;
    case BarSelectedRole:
        m_track[index.row()]->select(value.toBool());
        if(m_track[index.row()]->isSelected())
            m_track.addToSelected(index.row());
        else
            m_track.removeFromSelected(index.row());
        break;
    case BarMarkedRole:
        m_track[index.row()]->mark(value.toBool(), value.toBool() ? "marked" :  "unmarked");
        vec << BarMarkerTextRole;
        break;
    case BarMarkerTextRole:
        m_track[index.row()]->setMarkerText(value.toString());
        break;
    case BarHeldRole:
        m_track[index.row()]->hold(value.toBool());
        break;
    case BarLockedRole:
        m_track[index.row()]->lock(value.toBool());
        break;
    default:
        return false;
    }

    emit dataChanged(index, index, vec);
    return true;
}

BeatModel* BarModel::getBeatModel(const int id)
{
    if(!this->hasIndex(id, 0)) {
        return nullptr;
    }

    return m_track[id]->getBeatModel();
}

void BarModel::addBeat(const int id)
{
    qDebug() << id;
    auto beatModel = m_track[id]->getBeatModel(); //->add(items::BarItem::defaultTempo, m_track[id].get());
    beatModel->add(items::BarItem::defaultTempo, m_track[id].get());
    //auto idx = createIndex(id,0);
    //emit dataChanged(idx, idx, QVector<int>() << BarSizeRole);
}

void BarModel::removeBeat(const int id)
{
    m_track[id]->getBeatModel()->removeLast();
    //auto idx = createIndex(id,0);
    //emit dataChanged(idx, idx, QVector<int>() << BarSizeRole);
}

void BarModel::actionClick()
{
    auto res = ++m_track.currentBeat();
    if(!res)
        emit finished();
}

void BarModel::select(const bool val)
{
    m_track.select(val);
    dataChanged(createIndex(0,0), createIndex(rowCount(), 0), QVector<int>() << BarSelectedRole);
}

void BarModel::lock(const bool val)
{
    m_track.lock(val);
    dataChanged(createIndex(0,0), createIndex(rowCount(), 0), QVector<int>() << BarLockedRole);
}

void BarModel::hold(const bool val)
{
    m_track.hold(val);
    dataChanged(createIndex(0,0), createIndex(rowCount(), 0), QVector<int>() << BarLockedRole);
}

void BarModel::resetCurrentBeat()
{
    m_track.resetCurrentBeat();
}

void BarModel::onCurrentBeatSet(const int32_t barIdx, const int16_t beatIdx)
{
    if(barIdx < rowCount() && beatIdx < m_track[barIdx]->getBeatModel()->rowCount()) {
        m_track.setCurrentBeat(barIdx, beatIdx);
    }
    else {
        ; // TODO: error
    }
}

bool BarModel::hasSelectedBar() const
{
    return m_track.hasSelectedBar();
}

bool BarModel::hasLockedBar() const
{
    return m_track.hasLockedBar();
}

bool BarModel::isTrackLocked() const
{
    return m_track.isTrackLocked();
}

bool BarModel::isHeld() const
{
    return m_track.isHeld();
}

int BarModel::preCount(const int newVal)
{
    uint8_t oldPreCount = m_track.getPreCount();
    if(newVal > -1) {
        m_track.setPreCount(static_cast<uint8_t>(newVal));
        emit dataChanged(createIndex(0,0), createIndex(rowCount(),0), QVector<int>() << TrackPreCountRole);
    }

    return oldPreCount;
}

void BarModel::update()
{
    emit dataChanged(createIndex(0,0), createIndex(rowCount(),0), QVector<int>() << BarSizeRole);
}

int BarModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0;
    }

    return m_track.size();
}

Qt::ItemFlags BarModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractListModel::flags(index) | Qt::ItemIsEditable;
}

void BarModel::addItem()
{
    //m_isWorking = true;
    if(m_track.hasSelectedBar()) {
        auto idList = m_track.getSelectedBarsIds();
        for(auto& elemId : idList) {
            addBeat(elemId);
        }
        /*for(auto it : m_track)
            if(it->isSelected())
                it->getBeatModel()->add(120, &(*it));*/

        //emit dataChanged(createIndex(0,0), createIndex(rowCount(),0), QVector<int>() << BarSizeRole);
    }
    else {
        addBar();
    }
    //m_isWorking = false;
}

void BarModel::removeItem()
{
    if(m_track.hasSelectedBar()) {
        auto idList = m_track.getSelectedBarsIds();
        for(auto& elem : idList) {
            removeBeat(elem);            
        }
        //emit dataChanged(createIndex(0,0), createIndex(rowCount(),0), QVector<int>() << BarSizeRole);
    }
    else {
        removeBar();
    }
}

} // namespace models
