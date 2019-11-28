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


using namespace std;

class SceneBuilder
{

    QGraphicsScene *m_scene;
//    QGraphicsView *veiw;
    Model *m_model;
    vector<Multipolygon*> m_polygonList;
    vector<Road*> m_RoadList;
    vector<QGraphicsTextItem *> m_PointText;
    vector<QGraphicsEllipseItem *> m_Point;
    Road *m_route;
    // m_roadList, m_pointList;

    void buildMutipolygonFromWay(vector<idType> nodeRefList)
    {
        //loop over the nodelist for form a multpolygon item
        QPolygonF polygon;

        for(vector<idType>::iterator it = nodeRefList.begin();it != nodeRefList.end()-1;it++)
        {
            auto point = projection(m_model->getNodeLoaction(*(it)).lon(), m_model->getNodeLoaction(*(it)).lat());
            polygon << point;
        }
        Multipolygon *polyItem = new Multipolygon;
        polyItem->setPolygon(polygon);
        m_polygonList.emplace_back(polyItem);
        m_scene->addItem(polyItem);
    }

    void buildMutipolygon(wayData way, idType wayId)
    {
        QPolygonF polygon;
        auto nodeRefList = way.nodeRefList;
        for(vector<idType>::iterator it = nodeRefList.begin();it != nodeRefList.end();it++)
        {
            auto point = projection(m_model->getNodeLoaction(*(it)).lon(), m_model->getNodeLoaction(*(it)).lat());
            polygon << point;
        }
        Multipolygon *polyItem = new Multipolygon;
        polyItem->setId(wayId);
        polyItem->setPolygon(polygon);
        polyItem->setPolyType(way.pType);
        m_polygonList.emplace_back(polyItem);
        m_scene->addItem(polyItem);
    }

    void buildRoad(wayData way, idType wayId)
    {
        QPolygonF polyLine;
        auto nodeRefList = way.nodeRefList;
        for(vector<idType>::iterator it = nodeRefList.begin();it != nodeRefList.end();it++)
        {
            auto point = projection(m_model->getNodeLoaction(*(it)).lon(), m_model->getNodeLoaction(*(it)).lat());
            polyLine << point;
        }
        Road *roadItem = new Road;
        roadItem->setId(wayId);
        roadItem->setPenStyle(way.rType);
        roadItem->setPolygon(polyLine);
        m_RoadList.emplace_back(roadItem);
        m_scene->addItem(roadItem);
    }


public:
    SceneBuilder(Model *model)
    {
        m_scene = new QGraphicsScene;
        m_model = model;
        m_route = nullptr;
    }

    ~SceneBuilder()
    {
        delete m_scene;
    }

    void addAllItem()
    {
        addPolyItem();
        addRoadItem();
    }

    void addPolyItem()
    {
        auto wayMap = m_model->getWayMap();
        map<idType, wayData>::iterator it;
        for(it = wayMap.begin(); it != wayMap.end(); it++)
        {
            auto way = it -> second;
            if(way.isPolygon)
                buildMutipolygon(way, it -> first );
        }
    }

    QGraphicsScene *getScene()
    {
        return m_scene;
    }

    void addRoadItem()
    {
        auto wayMap = m_model->getWayMap();
        map<idType, wayData>::iterator it;
        for(it = wayMap.begin(); it != wayMap.end(); it++)
        {
            auto way = it -> second;
            if(!way.isPolygon)
                buildRoad(way, it->first);
        }
    }

    void drawRoute(std::vector<idType> refList)
    {
        if(m_route == nullptr)
            m_route = new Road;
        else
            m_route->setVisible(true);
        QPolygonF polyLine;
        for(vector<idType>::iterator it = refList.begin();it != refList.end();it++)
        {
//            std::cout << it << std::endl;
            auto point = projection(m_model->getNodeLoaction(*(it)).lon(), m_model->getNodeLoaction(*(it)).lat());
            polyLine << point;
        }
        m_route->setPolygon(polyLine);
        m_route->setZValue(200);
        m_scene->addItem(m_route);
    }

    void drawPointText()
    {
        auto nodeMap = m_model->getNodeMap();
        for(auto it = nodeMap.begin();it != nodeMap.end();it ++)
        {
            auto node = it -> second;
            auto tagList = node.tagList;
            for(const auto &tag:tagList)
            {
                if(tag.first == "name")
                {
                    QGraphicsTextItem *Text = new QGraphicsTextItem;
//                    QGraphicsEllipseItem *Point = new QGraphicsEllipseItem;
                    string name = tag.second;
                    Text->setPlainText(QString::fromStdString(name));
                    auto geoPos = m_model->getNodeLoaction(it -> first);
                    auto pos = projection(geoPos.lon(), geoPos.lat());
                    Text->setPos(pos);
                    Text->setZValue(100);
                    m_PointText.emplace_back(Text);
                    m_scene->addItem(Text);
                }
            }
        }
    }

    void cancelRoute()
    {
       m_route->setVisible(false);
    }

//    void getItemByPos()
//    {
//        osmium::Location test = m_model->getNodeLoaction(1703604687);
//        auto pos = projection(test.lon(), test.lat());
//        QTransform empty;
//        auto item = m_scene->itemAt(pos,empty);
//        std::cout << item->isVisible() << std::endl;
//    }

};

#endif // RENDER_H
