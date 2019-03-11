#ifndef BEATITEM_H
#define BEATITEM_H
#include "stdint.h"

namespace items {

class BarItem;
class BeatItem
{
    //const uint16_t defaultY = 260;
public:
    BeatItem(const uint16_t tempo, const int num, const BarItem* const barOwner);

    uint16_t getTempo() const;
    void setTempo(const uint16_t newTempo);
    bool isActive() const;
    void setActive(const bool val);
    int ownerBarId() const;
    uint16_t coordinateY() const;
    void setCoordinateY(uint16_t val);
    bool isOwnerBarSelected() const;
    bool isOwnerBarLocked() const;
private:
    uint16_t m_tempo;
    int m_number;
    bool m_active;
    uint16_t m_coordinateY;
    const BarItem* const m_barOwner;
};

} // namespace items

#endif // BEATITEM_H
