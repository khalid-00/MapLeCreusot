#ifndef SCENEBUILDER_H
#define SCENEBUILDER_H
#include <QGraphicsScene>
#include <string>
#include <vector>
#include "model.h"
#include "modeldata.h"
#include <map>
#include <vector>
#include <osmium/osm.hpp>
#include <QGraphicsView>
#include <QPen>
#include <vector>
#include "RenderEnum.h"
#include "RenderItem.h"
#include <QLine>
#include "projection.h"
#include <QGraphicsItem>
#include <QString>
#include <QObject>

using namespace std;

class SceneBuilder : public QObject
{
    Q_OBJECT

    QGraphicsScene *m_scene;
//    QGraphicsView *veiw;
    Model *m_model;
    vector<Multipolygon*> m_polygonList;
    vector<Road*> m_RoadList;
    vector<QGraphicsTextItem *> m_PointText;
    vector<QGraphicsEllipseItem *> m_Point;
    Road *m_route;
    Pin *m_source;
    Pin *m_dest;
    vector<Pin *> m_PinContainer;
    // m_roadList, m_pointList;

    void buildMutipolygonFromWay(vector<idType> nodeRefList);

    void buildMutipolygon(wayData way, idType wayId);

    void buildRoad(wayData way, idType wayId);

    void getBoundingRectCenter();

    void deletePin(Pin *);
    void deletePin(vector<Pin *> &vp);

public:
    SceneBuilder(Model *model);

    ~SceneBuilder();

    void addAllItem();

    void addPolyItem();

    QGraphicsScene *getScene();

    void addRoadItem();

    void drawRoute(std::vector<idType> refList);
    void drawPointText();


    void cancelRoute();

public slots:
    void setSource(Multipolygon* item);
    void setDest(Multipolygon* item);
    //popup input box and display result research
    void searchPlace();
    void cancel();



};

#endif // RENDER_H
