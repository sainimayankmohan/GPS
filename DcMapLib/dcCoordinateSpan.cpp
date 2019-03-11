#include "dcCoordinateSpan.h"

DcCoordinateSpan::DcCoordinateSpan() : m_LatitudeDelta(0.0), m_LongitudeDelta(0.0)
{
}

DcCoordinateSpan::DcCoordinateSpan(qreal latitudeDelta, qreal longitudeDelta) :
    m_LatitudeDelta(latitudeDelta), m_LongitudeDelta(longitudeDelta)
{
}

qreal DcCoordinateSpan::latitudeDelta() const
{
    return m_LatitudeDelta;
}

void DcCoordinateSpan::setLatitudeDelta(qreal latitudeDelta)
{
    m_LatitudeDelta = latitudeDelta;
}

qreal DcCoordinateSpan::longitudeDelta() const
{
    return m_LongitudeDelta;
}

void DcCoordinateSpan::setLongitudeDelta(qreal longitudeDelta)
{
    m_LongitudeDelta = longitudeDelta;
}

bool DcCoordinateSpan::operator==(const DcCoordinateSpan &other)
{
    return (latitudeDelta() == other.latitudeDelta())
           && (longitudeDelta() == other.longitudeDelta());
}
