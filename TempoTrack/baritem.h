#ifndef BARITEM_H
#define BARITEM_H

#include <QScopedPointer>
#include <QString>

namespace models { class BeatModel; }

namespace items {

class BarItem
{
public:
    const static uint8_t defaultTempo = 120;

    BarItem(const uint8_t numBeats, const uint8_t dimension, const int id);
    uint8_t getDimension() const;
    void setDimension(const uint8_t newDimension);
    int getId() const;
    models::BeatModel* getBeatModel();
    int getBarSize();
    bool isSelected() const;
    void select(const bool val);
    bool isMarked() const;
    void mark(const bool val, const QString &text = QString());
    bool isLocked() const;
    void lock(const bool val);
    bool isHeld() const;
    void hold(const bool val);
    void setMarkerText(const QString& text);
    QString getMarkerText() const;
private:
    uint8_t m_dimension;
    int m_id;
    bool m_selected;
    bool m_marked;
    QString m_markerText;
    bool m_locked;
    bool m_held;
    QScopedPointer<models::BeatModel> m_beatsPtr;
};

} // namespace items

#endif // BARITEM_H
