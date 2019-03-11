#ifndef TEMPOTRACK_H
#define TEMPOTRACK_H

#include <QSharedPointer>
#include "currentbeat.h"

namespace items {

class BarItem;

class TempoTrack : public QList<QSharedPointer<items::BarItem>>
{
public:
    explicit TempoTrack();

    void addToSelected(const int id);
    void removeFromSelected(const int id);
    void addToLocked(const int id);
    void removeFromLocked(const int id);
    void clearSelected();
    void clearLocked();
    QList<int>& getSelectedBarsIds();
    CurrentBeat& currentBeat();
    void setCurrentBeat(const int32_t barIdx, const int16_t beatIdx);
    void resetCurrentBeat();
    void select(const bool val);
    bool hasSelectedBar() const;
    bool isHeld() const;
    void hold(bool val);
    bool hasLockedBar() const;
    bool isTrackLocked() const;
    void lock(bool val);
    void setDimension(const uint8_t val);
    uint8_t getDimension();
    void setBeatsNumber(const uint8_t val);
    uint8_t getBeatsNumber();
    void setTempo(const uint8_t val);
    uint8_t getTempo();
    void setPreCount(const uint8_t val);
    uint8_t getPreCount() const;
private:
    bool m_hold;
    CurrentBeat m_curBeat;
    uint8_t m_dimension;
    uint8_t m_beatsNumber;
    uint8_t m_tempo;
    uint8_t m_preCountNumber;
    QList<int> m_selectedBarsIds;
    QList<int> m_lockedBarsIds;
};

} // namespace items

#endif // TEMPOTRACK_H
