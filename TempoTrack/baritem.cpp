#include "baritem.h"
#include "beatmodel.h"

namespace items {

BarItem::BarItem(const uint8_t numBeats, const uint8_t dimension, const int id)
    : m_dimension(dimension)
    , m_id(id)
    , m_selected(false)
    , m_marked(false)
    , m_markerText("unmarked")
    , m_locked(false)
    , m_held(false)
    , m_beatsPtr(new models::BeatModel())
{

    for(uint8_t i = 0; i < numBeats; ++i)
        m_beatsPtr->add(defaultTempo, this);
}
uint8_t BarItem::getDimension() const { return m_dimension; }
void BarItem::setDimension(const uint8_t newDimension) { m_dimension = newDimension; }
int BarItem::getId() const { return m_id; }
models::BeatModel* BarItem::getBeatModel() { return m_beatsPtr.data(); }
int BarItem::getBarSize() { return m_beatsPtr->rowCount(); }
bool BarItem::isSelected() const { return m_selected; }
void BarItem::select(const bool val) { m_selected = val; }
bool BarItem::isMarked() const { return m_marked; }
void BarItem::mark(const bool val, const QString &text) { m_marked = val; m_markerText = text; }
bool BarItem::isLocked() const { return m_locked; }
void BarItem::lock(const bool val) { m_locked = val; }
bool BarItem::isHeld() const { return m_held; }
void BarItem::hold(const bool val) { m_held = val; }
void BarItem::setMarkerText(const QString &text) { m_markerText = text; }
QString BarItem::getMarkerText() const { return m_markerText; }

} // namespace items
