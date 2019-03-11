#ifndef DCCOORDINATESPAN_H
#define DCCOORDINATESPAN_H

#include <QtCore/QtGlobal>

class DcCoordinateSpan
{
public:
    DcCoordinateSpan();
    DcCoordinateSpan(qreal latitudeDelta, qreal longitudeDelta);
    qreal latitudeDelta() const;
    qreal longitudeDelta() const;
    void setLatitudeDelta(qreal latitudeDelta);
    void setLongitudeDelta(qreal longitudeDelta);

    bool operator==(const DcCoordinateSpan &other);

private:
    qreal m_LatitudeDelta;
    qreal m_LongitudeDelta;
};

#endif // DCCOORDINATESPAN_H
