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


using namespace std;

class SceneBuilder
{

    QGraphicsScene *m_scene;
//    QGraphicsView *veiw;
    Model *m_model;
    vector<Multipolygon*> m_polygonList;
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
            QPointF point(m_model->getNodeLoaction(*(it)).x()/100, m_model->getNodeLoaction(*(it)).y()/100);
            polygon << point;
        }
//        Multipolygon *polyItem = new Multipolygon;
        Multipolygon *polyItem = new Multipolygon;
        polyItem->setPolygon(polygon);
        m_polygonList.emplace_back(polyItem);
        m_scene->addItem(polyItem);
    }

    void buildMutipolygon(wayData way)
    {
        QPolygonF polygon;
        auto nodeRefList = way.nodeRefList;
//        for(uint64_t i = 0; i != nodeRefList.size(); i++)
//            std::cout << nodeRefList[i] << std::endl;
        for(vector<idType>::iterator it = nodeRefList.begin();it != nodeRefList.end()-1;it++)
        {
//            std::cout << it << std::endl;
            QPointF point(m_model->getNodeLoaction(*(it)).x()/10, m_model->getNodeLoaction(*(it)).y()/10);
            polygon << point;
        }
        Multipolygon *polyItem = new Multipolygon;
        polyItem->setPolygon(polygon);
        polyItem->setPolyType(way.pType);
        m_polygonList.emplace_back(polyItem);
        m_scene->addItem(polyItem);
    }


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
        auto pathMap = m_model->getMPMap();
        map<idType,vector<idType>>::iterator it;
        for(it = pathMap.begin(); it != pathMap.end(); it++)
        {
            buildMutipolygonFromWay(it->second);
        }
    }

    void addPolyItem()
    {
        auto wayMap = m_model->getWayMap();
        map<idType, wayData>::iterator it;
        for(it = wayMap.begin(); it != wayMap.end(); it++)
        {
            auto way = it -> second;
            if(way.isClosed)
                buildMutipolygon(way);
        }
    }

    QGraphicsScene *getScene()
    {
        return m_scene;
    }

//    qreal getInitScale()
//    {
//        m_scene->setSceneRect(m_model->m_left, m_model->m_top, m_model->m_width, m_model->m_height);

//    }

};

#endif // RENDER_H
