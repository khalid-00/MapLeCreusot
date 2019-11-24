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


using namespace std;

class SceneBuilder
{

    QGraphicsScene *m_scene;
//    QGraphicsView *veiw;
    Model *m_model;
    vector<Multipolygon*> m_polygonList;
    vector<Road*> m_RoadList;
    // m_roadList, m_pointList;

    void buildMutipolygonFromWay(vector<idType> nodeRefList)
    {
        //loop over the nodelist for form a multpolygon item
        QPolygonF polygon;

//        for(uint64_t i = 0; i != nodeRefList.size(); i++)
//            std::cout << nodeRefList[i] << std::endl;
        for(vector<idType>::iterator it = nodeRefList.begin();it != nodeRefList.end()-1;it++)
        {
//            std::cout << it << std::endl;
            auto point = projection(m_model->getNodeLoaction(*(it)).lon(), m_model->getNodeLoaction(*(it)).lat());
            polygon << point;
        }
//        Multipolygon *polyItem = new Multipolygon;
        Multipolygon *polyItem = new Multipolygon;
//        polyItem->setFlag(QGraphicsItem::ItemIsSelectable);
        polyItem->setPolygon(polygon);
        m_polygonList.emplace_back(polyItem);
        m_scene->addItem(polyItem);
    }

    void buildMutipolygon(wayData way, idType wayId)
    {
        QPolygonF polygon;
        auto nodeRefList = way.nodeRefList;
//        for(uint64_t i = 0; i != nodeRefList.size(); i++)
//            std::cout << nodeRefList[i] << std::endl;
        for(vector<idType>::iterator it = nodeRefList.begin();it != nodeRefList.end();it++)
        {
//            std::cout << it << std::endl;
            auto point = projection(m_model->getNodeLoaction(*(it)).lon(), m_model->getNodeLoaction(*(it)).lat());
            polygon << point;
        }
        Multipolygon *polyItem = new Multipolygon;
        polyItem->setId(wayId);
//        polyItem->setFlag(QGraphicsItem::ItemIsSelectable);
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
//            std::cout << it << std::endl;
            auto point = projection(m_model->getNodeLoaction(*(it)).lon(), m_model->getNodeLoaction(*(it)).lat());
            polyLine << point;
        }
//        Multipolygon *polyItem = new Multipolygon;
        Road *roadItem = new Road;
        roadItem->setId(wayId);
        roadItem->setPenStyle(way.rType);
        roadItem->setPolygon(polyLine);
        m_RoadList.emplace_back(roadItem);
        m_scene->addItem(roadItem);
    }

    void markDrawn(idType wayId)
    {
        m_model->getWayData(wayId);

    }

//    void buildRelation(relationData relation)
//    {
//        vector<relationMember>::iterator it;
//        QPolygonF polygon;
//        for(it = relation.memberList.begin(); it != relation.memberList.end(); it ++)
//        {
//            if(it->type == osmium::item_type::way)
//            {
//                auto wayId = it->ref;
//                auto way = m_model->getWayData(wayId);
//                auto refList = way.nodeRefList;
//                m_model->setRelation(wayId);
//                for(vector<idType>::iterator nod = nodeRefList.begin();nod != nodeRefList.end();nod++)
//                {
//        //            std::cout << it << std::endl;
//                    auto point = projection(m_model->getNodeLoaction(*(nod)).lon(), m_model->getNodeLoaction(*(nod)).lat());
//                    polyLine << point;
//                }
//            }
//        }
//    }


public:
    SceneBuilder(Model *model)
    {
        m_scene = new QGraphicsScene;
        m_model = model;
//        getInitScale();
//        QPolygon test;
//        test << QPoint(1,1);
//        test << QPoint(1,30);
//        test << QPoint(30,40);
//        m_scene->addPolygon(test);
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

    void addRelationItem()
    {

    }

};

#endif // RENDER_H
