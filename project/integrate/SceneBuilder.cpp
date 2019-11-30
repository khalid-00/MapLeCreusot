#include "SceneBuilder.h"


void SceneBuilder::buildMutipolygonFromWay(vector<idType> nodeRefList)
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

void SceneBuilder::buildMutipolygon(wayData way, idType wayId)
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

void SceneBuilder::buildRoad(wayData way, idType wayId)
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


SceneBuilder::SceneBuilder(Model *model)
{
    m_scene = new QGraphicsScene;
    m_model = model;
    m_route = nullptr;
    m_dest = nullptr;
    m_source = nullptr;

}

SceneBuilder::~SceneBuilder()
{
    delete m_scene;
}

void SceneBuilder::addAllItem()
{
    addPolyItem();
    addRoadItem();
}

void SceneBuilder::addPolyItem()
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

QGraphicsScene* SceneBuilder::getScene()
{
    return m_scene;
}

void SceneBuilder::addRoadItem()
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

void SceneBuilder::drawRoute(std::vector<idType> refList)
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

void SceneBuilder::drawPointText()
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

void SceneBuilder::cancelRoute()
{
    m_route->setVisible(false);
}

void SceneBuilder::setSource(Multipolygon *item)
{

    QPointF centerPos = item->boundingRect().center();
    m_source = new Pin(Pin::pinType::source);
    m_source->setPos(centerPos);
    m_scene->addItem(m_source);
    std::cout << "setSource slot connected" << std::endl;
}

void SceneBuilder::setDest(Multipolygon *item)
{
    QPointF centerPos = item->boundingRect().center();
    m_source = new Pin(Pin::pinType::dest);
    m_source->setPos(centerPos);
    m_scene->addItem(m_source);
    std::cout << "setDestination slot connected" << std::endl;
}

void SceneBuilder::searchPlace()
{
    std::cout << "searchPlace slot connected" << std::endl;
}

void SceneBuilder::cancel()
{
    deletePin(m_source);
    deletePin(m_dest);
    deletePin(m_PinContainer);
    std::cout << "cancel slot connected" << std::endl;
}

void SceneBuilder::deletePin(Pin *p)
{
    if(p != nullptr)
        delete p;
}

void SceneBuilder::deletePin(vector<Pin *> &vp)
{
    for(auto it = vp.begin(); it != vp.end(); it ++)
    {
        if(*it != nullptr)
        {
            delete (*it);
        }
    }
}


