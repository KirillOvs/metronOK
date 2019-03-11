#include "tempotrack.h"
#include "currentbeat.h"
#include "baritem.h"
#include "beatmodel.h"
#include "barmodel.h"
#include <QObject>

namespace  items {

class CurrentBeat;
TempoTrack::TempoTrack()
    : m_hold(false)
    , m_curBeat(this)
    , m_dimension(4)      // TODO: read it from defaults.ini file
    , m_beatsNumber(4)    //
    , m_tempo(120)        //
    , m_preCountNumber(4) //
{
}

void TempoTrack::removeFromSelected(const int id)
{
    m_selectedBarsIds.removeOne(id);
}

void TempoTrack::addToLocked(const int id)
{
    m_lockedBarsIds << id;
}

void TempoTrack::removeFromLocked(const int id)
{
    m_lockedBarsIds.removeOne(id);
}

void TempoTrack::clearSelected()
{
    m_selectedBarsIds.clear();
}

void TempoTrack::clearLocked()
{
    m_lockedBarsIds.clear();
}

void TempoTrack::addToSelected(const int id)
{
    m_selectedBarsIds << id;
}

QList<int>& TempoTrack::getSelectedBarsIds()
{
    return m_selectedBarsIds;
}

CurrentBeat& TempoTrack::currentBeat()
{
    return m_curBeat;
}

void TempoTrack::resetCurrentBeat()
{
    m_curBeat.reset();
}

void TempoTrack::select(const bool val)
{
    for(auto& it : *this) {
        it->select(val);
        if(val)
            addToSelected(it->getId());
        else
            removeFromSelected(it->getId());
    }
}

void TempoTrack::setCurrentBeat(const int32_t barIdx, const int16_t beatIdx)
{
    m_curBeat.set(barIdx,beatIdx);
}

bool TempoTrack::hasSelectedBar() const
{
    return !m_selectedBarsIds.empty();
}

bool TempoTrack::isHeld() const
{
    return m_hold;
}

void TempoTrack::hold(bool val)
{
    for(auto& it : *this)
        it->hold(val);
    m_hold = val;
}

bool TempoTrack::hasLockedBar() const
{
    return !m_lockedBarsIds.empty();
}

bool TempoTrack::isTrackLocked() const
{
    return m_lockedBarsIds.size() == this->size();
}

void TempoTrack::lock(bool val)
{
    for(auto& it : *this) {
        it->lock(val);
        if(val)
            addToLocked(it->getId());
        else
            removeFromLocked(it->getId());
    }
}

void TempoTrack::setDimension(const uint8_t val)
{
    m_dimension = val;
}

uint8_t TempoTrack::getDimension()
{
    return m_dimension;
}

void TempoTrack::setBeatsNumber(const uint8_t val)
{
    m_beatsNumber = val;
}

uint8_t TempoTrack::getBeatsNumber()
{
    return m_beatsNumber;
}

void TempoTrack::setTempo(const uint8_t val)
{
    m_tempo = val;
}

uint8_t TempoTrack::getTempo()
{
    return m_tempo;
}

void TempoTrack::setPreCount(const uint8_t val)
{
    m_preCountNumber = val;
}

uint8_t TempoTrack::getPreCount() const
{
    return m_preCountNumber;
}

} // namespace  items
