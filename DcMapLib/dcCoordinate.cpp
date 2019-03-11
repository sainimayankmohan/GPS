#include "dcCoordinate.h"

DcCoordinate::DcCoordinate() : m_Latitude(0.0), m_Longitude(0.0)
{
}

DcCoordinate::DcCoordinate(qreal latitude, qreal longitude) :
    m_Latitude(latitude), m_Longitude(longitude)
{
}

qreal DcCoordinate::latitude() const
{
    return m_Latitude;
}

void DcCoordinate::setLatitude(qreal latitude)
{
    m_Latitude = latitude;
}

qreal DcCoordinate::longitude() const
{
    return m_Longitude;
}

void DcCoordinate::setLongitude(qreal longitude)
{
    m_Longitude = longitude;
}

bool DcCoordinate::operator==(const DcCoordinate &other)
{
    return (latitude() == other.latitude())
           && (longitude() == other.longitude());
}
