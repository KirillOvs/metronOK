#include "beatitem.h"
#include "barmodel.h"
#include "baritem.h"

namespace items {

BeatItem::BeatItem(const uint16_t tempo, const int num, const items::BarItem* const barOwner)
    : m_tempo(tempo)
    , m_number(num)
    , m_active(false)
    , m_coordinateY(260)
    , m_barOwner(barOwner)
{}
uint16_t BeatItem::getTempo() const { return m_tempo; }
void BeatItem::setTempo(const uint16_t newTempo) { m_tempo = newTempo; }
bool BeatItem::isActive() const { return m_active; }
void BeatItem::setActive(const bool val) { m_active = val; }
int BeatItem::ownerBarId() const { return m_barOwner->getId(); }
uint16_t BeatItem::coordinateY() const { return m_coordinateY; }
void BeatItem::setCoordinateY(uint16_t val) { m_coordinateY = val; }
bool BeatItem::isOwnerBarSelected() const { return m_barOwner->isSelected(); }
bool BeatItem::isOwnerBarLocked() const { return m_barOwner->isLocked(); }

}
