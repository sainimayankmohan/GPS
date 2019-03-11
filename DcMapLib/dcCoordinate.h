#ifndef DCCOORDINATE_H
#define DCCOORDINATE_H

#include <QtCore/QtGlobal>

// TODO: Add documentation to specify lat/lng ranges.
//       Latitude is in [-90, 90], and longitude is in [-180, 180]

class DcCoordinate
{
public:
    DcCoordinate();
    DcCoordinate(qreal latitude, qreal longitude);

    qreal latitude() const;
    qreal longitude() const;
    void setLatitude(qreal latitude);
    void setLongitude(qreal longitude);

    bool operator==(const DcCoordinate &other);

private:
    qreal m_Latitude;
    qreal m_Longitude;
};

#endif // DCCOORDINATE_H
