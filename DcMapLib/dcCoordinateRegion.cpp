#include "dcCoordinateRegion.h"
#include <QtDebug>

DcCoordinateRegion::DcCoordinateRegion() :
    m_East(0.0), m_West(0.0), m_North(0.0), m_South(0.0)
{
}

DcCoordinateRegion::DcCoordinateRegion(DcCoordinate southWest,
                                       DcCoordinate northEast) :
    m_East(northEast.longitude()),
    m_West(southWest.longitude()),
    m_North(northEast.latitude()),
    m_South(southWest.latitude())
{
}

DcCoordinateRegion::DcCoordinateRegion(qreal north, qreal south,
                                       qreal east, qreal west) :
    m_East(east), m_West(west), m_North(north), m_South(south)
{
}

DcCoordinateRegion::DcCoordinateRegion(DcCoordinate center,
                                       DcCoordinateSpan span) :
    m_East(center.longitude() + span.longitudeDelta() / 2),
    m_West(center.longitude() - span.longitudeDelta() / 2),
    m_North(center.latitude() + span.latitudeDelta() / 2),
    m_South(center.latitude() - span.latitudeDelta() / 2)
{
}

bool DcCoordinateRegion::contains(DcCoordinate &point, bool proper) const
{
    qreal lng = point.longitude();
    qreal lat = point.latitude();

    bool r = false;
    if (proper)
        r = lat > west() && lat < east() && lng > south() && lng < north();
    else
        r = lat >= west() && lat <= east() && lng >= south() && lng <= north();

    return r;
}

bool DcCoordinateRegion::intersects(DcCoordinateRegion &span) const
{
    Q_UNUSED(span)
    qWarning("DcCoordinateRegion::intersects not implemented; false returned");
    return false;
}

bool DcCoordinateRegion::isEmpty() const
{
    return (east() == west()) || (north() == south());
}

qreal DcCoordinateRegion::east() const
{
    return m_East;
}

qreal DcCoordinateRegion::west() const
{
    return m_West;
}

qreal DcCoordinateRegion::north() const
{
    return m_North;
}

qreal DcCoordinateRegion::south() const
{
    return m_South;
}

void DcCoordinateRegion::setEast(qreal value)
{
    m_East = value;
}

void DcCoordinateRegion::setWest(qreal value)
{
    m_West = value;
}

void DcCoordinateRegion::setNorth(qreal value)
{
    m_North = value;
}

void DcCoordinateRegion::setSouth(qreal value)
{
    m_South = value;
}

DcCoordinate DcCoordinateRegion::southWest() const
{
    return DcCoordinate(south(), west());
}

DcCoordinate DcCoordinateRegion::northEast() const
{
    return DcCoordinate(north(), east());
}

DcCoordinate DcCoordinateRegion::southEast() const
{
    return DcCoordinate(south(), east());
}

DcCoordinate DcCoordinateRegion::northWest() const
{
    return DcCoordinate(north(), west());
}

DcCoordinate DcCoordinateRegion::center() const
{
    return DcCoordinate((north() + south()) / 2, (east() + west()) / 2);
}

DcCoordinateSpan DcCoordinateRegion::span() const
{
    return DcCoordinateSpan(north() - south(), east() - west());
}

bool DcCoordinateRegion::operator ==(const DcCoordinateRegion &other)
{
    return (east() == other.east())
            && (west() == other.west())
            && (north() == other.north())
            && (south() == other.south());
}
