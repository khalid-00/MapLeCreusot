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

using namespace std;

class SceneBuilder
{

    QGraphicsScene *m_scene;
//    QGraphicsView *veiw;
    Model *m_model;

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
        m_scene -> addPolygon(polygon);
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

    QGraphicsScene *getScene()
    {
        return m_scene;
    }

    qreal getInitScale()
    {
        m_scene->setSceneRect(m_model->m_left, m_model->m_top, m_model->m_width, m_model->m_height);

    }

};

#endif // RENDER_H
