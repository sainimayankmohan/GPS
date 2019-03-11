#ifndef DCCOORDINATEREGION_H
#define DCCOORDINATEREGION_H

#include "dcCoordinate.h"
#include "dcCoordinateSpan.h"

class DcCoordinateRegion
{
public:
    DcCoordinateRegion();
    DcCoordinateRegion(DcCoordinate southWest, DcCoordinate northEast);
    DcCoordinateRegion(qreal north, qreal south, qreal east, qreal west);
    DcCoordinateRegion(DcCoordinate center, DcCoordinateSpan span);

    bool contains(DcCoordinate &point, bool proper = false) const;
    bool intersects(DcCoordinateRegion &span) const;
    bool isEmpty() const;

    void extend(const DcCoordinate &point);
    void unite(const DcCoordinateRegion &other);

    qreal east() const;
    qreal west() const;
    qreal north() const;
    qreal south() const;

    void setEast(qreal value);
    void setWest(qreal value);
    void setNorth(qreal value);
    void setSouth(qreal value);

    DcCoordinate southWest() const;
    DcCoordinate northEast() const;
    DcCoordinate southEast() const;
    DcCoordinate northWest() const;

    DcCoordinate center() const;
    DcCoordinateSpan span() const;

    bool operator ==(const DcCoordinateRegion &other);

private:
    qreal m_East;
    qreal m_West;
    qreal m_North;
    qreal m_South;
};

#endif // DCCOORDINATEREGION_H
