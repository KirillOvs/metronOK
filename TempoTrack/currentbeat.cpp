#include "currentbeat.h"
#include "barmodel.h"
#include "baritem.h"
#include "beatmodel.h"
#include "beatitem.h"
#include "tempotrack.h"

namespace items {

CurrentBeat::CurrentBeat(const TempoTrack* const track)
    : m_track(track)
    , m_barIdx(-1)
    , m_beatIdx(-1)
{
    assert(m_track);
}

bool CurrentBeat::operator ++()
{
    if(isReseted()) {
        m_barIdx = 0;
        m_beatIdx = 0;
        auto beatModel = m_track->at(m_barIdx)->getBeatModel();
        beatModel->setData(beatModel->createIndex(m_beatIdx, 0), QVariant(true), models::BeatModel::Roles::IsActiveRole);
        return true;
    }

    auto beatModel = m_track->at(m_barIdx)->getBeatModel();
    beatModel->setData(beatModel->createIndex(m_beatIdx, 0), QVariant(false), models::BeatModel::Roles::IsActiveRole); // unset previos

    if(m_beatIdx + 1 == beatModel->rowCount()) {
        ++m_barIdx;
        m_beatIdx = 0;
        beatModel = m_track->at(m_barIdx)->getBeatModel(); // get next bar's beat model
    }
    else {
        ++m_beatIdx;
    }

    beatModel->setData(beatModel->createIndex(m_beatIdx, 0), QVariant(true), models::BeatModel::Roles::IsActiveRole); // set next

    return true;
}

void CurrentBeat::set(const int32_t barIdx, const int16_t beatIdx)
{
    if(m_barIdx < m_track->size()) {
        // unset old current beat
        if(!isReseted()) {
            auto beatModel = m_track->at(m_barIdx)->getBeatModel();
            beatModel->setData(beatModel->createIndex(m_beatIdx, 0), QVariant(false), models::BeatModel::Roles::IsActiveRole);
        }

        m_barIdx = barIdx;
        m_beatIdx = beatIdx;
        // set new
        auto beatModel = m_track->at(m_barIdx)->getBeatModel();
        beatModel = m_track->at(m_barIdx)->getBeatModel();
        beatModel->setData(beatModel->createIndex(m_beatIdx, 0), QVariant(true), models::BeatModel::Roles::IsActiveRole);
    }
}

void CurrentBeat::reset()
{
    set(-1, -1);
}

bool CurrentBeat::isReseted()
{
    return m_barIdx == -1 && m_beatIdx == -1;
}

} // namespace models
