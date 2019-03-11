#include "dcMapView.h"
#include <QHBoxLayout>
#include <QHash>
#include <QVariantMap>
#include <QWebFrame>
#include <QWebView>
#include <QtDebug>

class CustomWebPage : public QWebPage
{
    public:
        CustomWebPage(QObject *parent = 0) : QWebPage(parent) {}

    protected:
        virtual void javaScriptConsoleMessage(
                const QString &message, int lineNumber,
                const QString &sourceID);
};

void CustomWebPage::javaScriptConsoleMessage(
        const QString &message, int lineNumber, const QString &sourceID)
{
    qDebug() << "JavaScript" << sourceID << "line" << lineNumber <<
                ":" << message;
}


class DCMapViewPrivate
{
    Q_DECLARE_PUBLIC(DCMapView)

public:
    DCMapViewPrivate(DCMapView *q) : q_ptr(q), loaded(false)
    {
        webView = new QWebView();
        webView->setPage(new CustomWebPage());
        webView->load(QUrl("qrc:///dcmapkit/gmap/gmap.html"));
    }
    ~DCMapViewPrivate() {}
    DCMapView *q_ptr;

    bool loaded;
    QWebView *webView;
    struct {
        DcCoordinate centerCoordinate;
        DCMapView::MapType mapType;
        uint zoomLevel;
    } initialValues;

    inline QWebFrame *frame() { return webView->page()->mainFrame(); }
    inline QVariant evaluateJavaScript(const QString &script,
                                       bool force = false)
    {
        if (loaded || force)
            return frame()->evaluateJavaScript(script);
        else
            return QVariant();
    }
    inline QString toJsMapType(DCMapView::MapType type)
    {
        QString typeName;
        switch (type)
        {
        case DCMapView::Hybrid:
            typeName = "HYBRID";
            break;
        case DCMapView::RoadMap:
            typeName = "ROADMAP";
            break;
        case DCMapView::Satellite:
            typeName = "SATELLITE";
            break;
        case DCMapView::Terrain:
            typeName = "TERRAIN";
            break;
        }
        return QString("google.maps.MapTypeId.%1").arg(typeName);
    }
    inline DCMapView::MapType fromJsMapType(QString &type)
    {
        static QHash<QString, DCMapView::MapType> types;
        if (types.isEmpty())
        {
            types.insert("hybrid", DCMapView::Hybrid);
            types.insert("roadmap", DCMapView::RoadMap);
            types.insert("satellite", DCMapView::Satellite);
            types.insert("terrain", DCMapView::Terrain);
        }
        return types.value(type, initialValues.mapType);
    }
};

DCMapView::DCMapView(MapType mapType, DcCoordinate center, uint zoomLevel,
                     QWidget *parent) :
    QWidget(parent), m_pMapViewPvtPtr(new DCMapViewPrivate(this))
{
    Q_D(DCMapView);

    QHBoxLayout *mainLayout = new QHBoxLayout();
    mainLayout->addWidget(d->webView);
    setLayout(mainLayout);

    d->initialValues.centerCoordinate = center;
    d->initialValues.mapType = mapType;
    d->initialValues.zoomLevel = zoomLevel;
    connect(d->frame(), SIGNAL(javaScriptWindowObjectCleared()),
            this, SLOT(insertNativeObject()));
    connect(d->webView, SIGNAL(loadFinished(bool)),
            this, SLOT(initializeMap()));
}

void DCMapView::insertNativeObject()
{
    Q_D(DCMapView);
    d->frame()->addToJavaScriptWindowObject("qMapView", this);
}

void DCMapView::initializeMap()
{
    Q_D(DCMapView);
    if (d->loaded)
        return;
    DcCoordinate &center = d->initialValues.centerCoordinate;
    QString js = QString("initialize(%1, %2, %3, %4);").arg(
                QString::number(center.longitude()),
                QString::number(center.latitude()),
                d->toJsMapType(d->initialValues.mapType),
                QString::number(d->initialValues.zoomLevel));
    d->evaluateJavaScript(js, true);

    d->loaded = true;
    emit mapLoaded();
}

void DCMapView::resizeEvent(QResizeEvent *)
{
    Q_D(DCMapView);
    d->evaluateJavaScript("google.maps.event.trigger(map, 'resize');");
}

DCMapView::MapType DCMapView::mapType() const
{
    QString res = m_pMapViewPvtPtr->evaluateJavaScript("map.getMapTypeId();").toString();
    return m_pMapViewPvtPtr->fromJsMapType(res);
}

/** Returns the map's current visible region.
 * Corresponds to `getBounds()`. Due to the limitation in the Google Map
 * JavaScript API, this method works only after the first `regionChanged()`
 * signal is sent. The result of any invocation of this method before that is
 * undifined.
 */
DcCoordinateRegion DCMapView::region() const
{
    QVariantMap result = m_pMapViewPvtPtr->evaluateJavaScript("getMapBounds();").toMap();
    return DcCoordinateRegion(DcCoordinate(result["south"].toReal(),
                                           result["west"].toReal()),
                              DcCoordinate(result["north"].toReal(),
                                           result["east"].toReal()));
}

DcCoordinate DCMapView::center() const
{
    QVariantMap result = m_pMapViewPvtPtr->evaluateJavaScript("getMapCenter();").toMap();
    return DcCoordinate(result["latitude"].toReal(),
                        result["longitude"].toReal());
}

uint DCMapView::zoomLevel() const
{
    return m_pMapViewPvtPtr->evaluateJavaScript("map.getZoom();").toUInt();
}

qreal DCMapView::heading() const
{
    return m_pMapViewPvtPtr->evaluateJavaScript("map.getHeading();").toReal();
}

qreal DCMapView::tilt() const
{
    return m_pMapViewPvtPtr->evaluateJavaScript("map.getTilt();").toReal();
}

void DCMapView::setMapType(MapType type)
{
    Q_D(DCMapView);
    QString typeName = d->toJsMapType(type);
    QString script = QString("map.setMapTypeId(%1);").arg(typeName);
    d->evaluateJavaScript(script);
}

void DCMapView::setCenter(DcCoordinate center, bool animated)
{
    Q_D(DCMapView);
    QString format = QString("setMapCenter(%1, %2, %3);");
    QString js = format.arg(QString::number(center.latitude()),
                            QString::number(center.longitude()),
                            animated ? "true" : "false");
    d->evaluateJavaScript(js);
}

void DCMapView::updateMarker(DcCoordinate center)
{
    Q_D(DCMapView);
    QString format = QString("updateMarker(%1, %2);");
    QString js = format.arg(QString::number(center.latitude()),
                            QString::number(center.longitude()));
    d->evaluateJavaScript(js);
}

void DCMapView::setZoomLevel(uint zoom)
{
    Q_D(DCMapView);
    d->evaluateJavaScript(QString("map.setZoom(%1);").arg(zoom));
}

void DCMapView::makeRegionVisible(DcCoordinateRegion &region)
{
    Q_D(DCMapView);
    QString format = QString("panMapToBounds(%1, %2, %3, %4);");
    QString js = format
            .arg(region.north())
            .arg(region.south())
            .arg(region.east())
            .arg(region.west());
    d->evaluateJavaScript(js);
}

void DCMapView::fitRegion(DcCoordinateRegion &region)
{
    Q_D(DCMapView);
    QString format = QString("fitMapToBounds(%1, %2, %3, %4);");
    QString js = format
            .arg(region.north())
            .arg(region.south())
            .arg(region.east())
            .arg(region.west());
    d->evaluateJavaScript(js);
}

void DCMapView::regionDidChangeTo(qreal north, qreal south,
                                  qreal east, qreal west)
{
    emit regionChanged(DcCoordinateRegion(north, south, east, west));
}

void DCMapView::centerDidChangeTo(qreal latitude, qreal longitude)
{
    emit centerChanged(DcCoordinate(latitude, longitude));
}

void DCMapView::mapTypeDidChangeTo(QString typeString)
{
    Q_D(DCMapView);
    emit mapTypeChanged(d->fromJsMapType(typeString));
}

void DCMapView::mouseDidClickAt(qreal latitude, qreal longitude)
{
    emit mouseClicked(DcCoordinate(latitude, longitude));
}

void DCMapView::mouseDidDoubleClickAt(qreal latitude, qreal longitude)
{
    emit mouseDoubleClicked(DcCoordinate(latitude, longitude));
}

void DCMapView::mouseDidRightClickAt(qreal latitude, qreal longitude)
{
    emit mouseRightClicked(DcCoordinate(latitude, longitude));
}

void DCMapView::cursorDidMoveTo(qreal latitude, qreal longitude)
{
    emit cursorMoved(DcCoordinate(latitude, longitude));
}

void DCMapView::cursorDidEnterTo(qreal latitude, qreal longitude)
{
    emit cursorEntered(DcCoordinate(latitude, longitude));
}

void DCMapView::cursorDidLeaveFrom(qreal latitude, qreal longitude)
{
    emit cursorLeaved(DcCoordinate(latitude, longitude));
}
