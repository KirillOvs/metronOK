#ifndef BARMODEL_H
#define BARMODEL_H

#include <QAbstractListModel>
#include <QList>
#include <QSharedPointer>
#include "tempotrack.h"

class Serializable // TODO:
{

};

namespace models {

class BeatModel;
class BarModel : public QAbstractListModel, public Serializable
{
    Q_OBJECT
    Q_PROPERTY(int count READ rowCount NOTIFY countChanged)
public:
    enum Roles {
        BarDimensionRole = Qt::UserRole,
        BarSizeRole,
        BarSelectedRole,
        BarMarkedRole,
        BarMarkerTextRole,
        BarHeldRole,
        BarLockedRole,
        TrackLockedRole,
        TrackHeldRole,
        TrackPreCountRole,
    };

    explicit BarModel(QObject *parent = nullptr);

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QHash<int, QByteArray> roleNames() const override;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    virtual Qt::ItemFlags flags(const QModelIndex &index = QModelIndex()) const override;

    Q_INVOKABLE void addItem();
    Q_INVOKABLE void removeItem();
    Q_INVOKABLE models::BeatModel* getBeatModel(const int id);
    Q_INVOKABLE void actionClick();
    Q_INVOKABLE void select(const bool val);
    Q_INVOKABLE void lock(const bool val);
    Q_INVOKABLE void hold(const bool val);
    Q_INVOKABLE void resetCurrentBeat();
    Q_INVOKABLE bool hasSelectedBar() const;
    Q_INVOKABLE bool hasLockedBar() const;
    Q_INVOKABLE bool isTrackLocked() const;
    Q_INVOKABLE bool isHeld() const;
    Q_INVOKABLE int preCount(const int = -1);
    Q_INVOKABLE void update();
    Q_INVOKABLE bool isWorking() { return m_isWorking; }
signals:
    void countChanged();
    void finished();
public slots:
    void onTempoOrCoordinateYChanged(const uint32_t barId, const uint16_t tempoVal, const int role);
    void onCurrentBeatSet(const int32_t barIdx, const int16_t beatIdx);
private:
    void addBar();
    void removeBar(const int id = -1);
    void addBeat(const int id);
    void removeBeat(const int id);
    void actionForeach(const Roles role, QVariant val);

    bool m_isWorking;
    items::TempoTrack m_track;
};

} // namespase models

#endif // BARMODEL_H
