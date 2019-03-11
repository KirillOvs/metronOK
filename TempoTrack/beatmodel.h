#ifndef BEATMODEL_H
#define BEATMODEL_H

#include <QAbstractListModel>
#include <QSharedPointer>

namespace items { class BarItem; class BeatItem; class CurrentBeat; }

namespace models {

class BeatModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles {
        TempoRole = Qt::UserRole,
        IsActiveRole,
        CoordinateY_Role,
        IsOwnerBarLockedRole,
        CurrentBeatRole,
    };

    explicit BeatModel(QObject *parent = nullptr);

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QHash<int, QByteArray> roleNames() const override;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    virtual Qt::ItemFlags flags(const QModelIndex &index = QModelIndex()) const override;
    void add(const uint8_t tempo, const items::BarItem* const barOwner);
    void removeLast();
signals:
    void tempoOrCoordinateYChanged(const int barId, const uint16_t tempoVal, const int role);
    void currentBeatSet(const int barId, const uint16_t beatId);
private:
    QList<QSharedPointer<items::BeatItem>> m_data;

    friend class items::CurrentBeat;
};

} // namespace models

#endif // BEATMODEL_H
