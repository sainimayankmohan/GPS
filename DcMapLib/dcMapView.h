#ifndef DCMAPVIEW_H
#define DCMAPVIEW_H

#include <QWidget>
#include "dcMapKit.h"
#include "dcCoordinate.h"
#include "dcCoordinateRegion.h"
class DCMapViewPrivate;

class DCMapView : public QWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(DCMapView)

public:
    enum MapType {
        Hybrid,
        RoadMap,
        Satellite,
        Terrain
    };

    DCMapView(MapType mapType, DcCoordinate center, uint zoomLevel,
              QWidget *parent = 0);
    MapType mapType() const;

    DcCoordinateRegion region() const;
    DcCoordinate center() const;

    uint zoomLevel() const;
    qreal heading() const;
    qreal tilt() const;

    void setMapType(MapType type);

    void setCenter(DcCoordinate center, bool animated = true);
    void updateMarker(DcCoordinate center);
    void setZoomLevel(uint zoom);

    void makeRegionVisible(DcCoordinateRegion &region);
    void fitRegion(DcCoordinateRegion &region);

protected:
    void resizeEvent(QResizeEvent *);

signals:
    void mapLoaded();
    void mapBecameIdle();
    void regionChanged(DcCoordinateRegion region);
    void centerChanged(DcCoordinate center);
    void mouseClicked(DcCoordinate coordinate);
    void mouseDoubleClicked(DcCoordinate coordinate);
    void mouseRightClicked(DcCoordinate coordinate);
    void mouseDragged();
    void mouseDragStarted();
    void mouseDragEnded();
    void cursorMoved(DcCoordinate coordinate);
    void cursorEntered(DcCoordinate coordinate);
    void cursorLeaved(DcCoordinate coordinate);
    void headingChanged();
    void mapTypeChanged(MapType type);
    void tilesLoaded();
    void tilesChanged();
    void zoomLevelChanged(uint level);

protected slots:
    void initializeMap();
    void insertNativeObject();
    void regionDidChangeTo(qreal north, qreal south, qreal east, qreal west);
    void centerDidChangeTo(qreal latitude, qreal longitude);
    void mapTypeDidChangeTo(QString typeString);
    void mouseDidClickAt(qreal latitude, qreal longitude);
    void mouseDidDoubleClickAt(qreal latitude, qreal longitude);
    void mouseDidRightClickAt(qreal latitude, qreal longitude);
    void cursorDidMoveTo(qreal latitude, qreal longitude);
    void cursorDidEnterTo(qreal latitude, qreal longitude);
    void cursorDidLeaveFrom(qreal latitude, qreal longitude);

private:
    DCMapViewPrivate *m_pMapViewPvtPtr;
};

#endif // DCMAPVIEW_H
