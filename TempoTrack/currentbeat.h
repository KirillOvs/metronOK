#ifndef CURRENTBEAT_H
#define CURRENTBEAT_H

#include <stdint.h>
//#include <QModelIndex>

namespace items {

class TempoTrack;

class CurrentBeat //: public QModelIndex
{
public:
    explicit CurrentBeat(const TempoTrack* const track);
    bool operator ++();
    void set(const int32_t barIdx, const int16_t beatIdx);
    void reset();
private:
    bool isReseted();

    const TempoTrack* const m_track;
    int32_t m_barIdx;
    int16_t m_beatIdx;
};

} // namespace models

#endif // CURRENTBEAT_H
