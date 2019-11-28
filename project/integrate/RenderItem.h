#ifndef RENDERITEM_H
#define RENDERITEM_H

#include <QGraphicsPolygonItem>
#include <QGraphicsPathItem>
#include <QGraphicsLayoutItem>
#include <QPen>
#include <QPainter>
#include <vector>
#include <string>
#include "modelDataHandler.h"
#include <QMouseEvent>
#include <QGraphicsView>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>

//================================ use color reference from P0267_RefImpl
static QColor getPolygonColor(polygonType type)
{
    switch (type) {
    case building:
        return QColor(255, 190, 190);
    case water:
        return QColor(0, 201, 215);
    case grass:
        return QColor(197, 236, 148);
    case forest:
        return QColor(46, 139, 87);
    case industrial:
        return QColor(223, 197, 220);
    case leisure:
        return QColor(189, 252, 193);
    case railway:
        return QColor(193, 193, 193);
    case commercial:
        return QColor(233, 195, 196);
    case residential:
        return QColor(209, 209, 209);
    default:
        return QColor(100, 100, 100);

    }
}

static QColor getPathColor(roadType type)
{
    switch(type) {
        case Railway:       return QColor{100, 100, 100};
        case Motorway:      return QColor{226, 122, 143};
        case Trunk:         return QColor{245, 161, 136};
        case Primary:       return QColor{249, 207, 144};
        case Secondary:     return QColor{244, 251, 173};
        case Tertiary:      return QColor{244, 251, 173};
        case Residential:   return QColor{254, 254, 254};
        case Service:       return QColor{254, 254, 254};
        case Footway:       return QColor{241, 106, 96};
        case Unclassified:  return QColor{254, 254, 254};
        default:            return QColor(190, 190, 190);
    }
}

static float getPathWidth(roadType type)
{
    switch( type ) {
        case Railway:       return 6.f;
        case Motorway:      return 6.f;
        case Trunk:         return 6.f;
        case Primary:       return 5.f;
        case Secondary:     return 5.f;
        case Tertiary:      return 4.f;
        case Residential:   return 2.5f;
        case Unclassified:  return 2.5f;
        case Service:       return 1.f;
        case Footway:       return 0.f;
        default:            return 1.f;
    }
}

// test for drawing multipolygon in relations
class Multipolygon : public QGraphicsItem/*QGraphicsPolygonItem*/
{

    polygonType m_PolygonType;    //this will determin the z-value
    QColor m_brushColor;
    idType m_wayId;
    QPolygonF m_poly;

public:
    Multipolygon(){}
    ~Multipolygon(){}
    enum { Type = UserType + 1 };

    int type() const
    {
       // Enable the use of qgraphicsitem_cast with this item.
       return Type;
    }
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override
    {
        painter->setBrush(m_brushColor);
        painter->drawPolygon(this->m_poly);
    }

    QRectF boundingRect() const
    {
        return m_poly.boundingRect();
    }

    void setPolyType(polygonType type)
    {

        m_PolygonType = type;
        m_brushColor = getPolygonColor(m_PolygonType);

        setZValue(type);
    }
    void setId(idType id)
    {
        m_wayId = id;
    }

    idType getId()
    {
        return m_wayId;
    }

//    void mousePressEvent(QGraphicsSceneMouseEvent *event)
//    {
//        if(event->button() == Qt::RightButton)
//        {
//            std::cout << "selected item id: " << m_wayId << std::endl;
//            auto pos = this->scenePos();
//            std::cout << "pos of the item is: " << this->scenePos().x() << ", " << this->scenePos().y() << std::endl;
//        }
//        else
//            QGraphicsItem::mousePressEvent(event);
//    }
    void setPolygon(QPolygonF poly)
    {
        m_poly = poly;
    }

//    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
//    {

//        QMenu menu;
//        menu.addAction("Action 1");
//        menu.addAction("Action 2");
//        QAction *a = menu.exec(event->screenPos());
//        qDebug("User clicked %s", qPrintable(a->text()));
//    }

};

class Road : public QGraphicsPolygonItem
{
    roadType m_rtype;
    QColor m_RoadStyle;
    idType m_wayId;
    QPen m_pen;

public:
    Road(){}

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
    QWidget *widget) override
    {
        m_pen.setCapStyle(Qt::RoundCap);
        painter->setPen(m_pen);
        painter->drawPolyline(this->polygon());
    }
    idType const getId()
    {
        return m_wayId;
    }
    void setId(idType id)
    {
        m_wayId = id;
    }

    void setPenStyle(roadType rType)
    {
        m_pen.setBrush(getPathColor(rType));
        m_pen.setWidth(getPathWidth(rType)+3.0);
        setZValue(leisure + static_cast<int>(rType) * 0.1);
    }

//    void mousePressEvent(QGraphicsSceneMouseEvent *event)
//    {
////        this->setSelected(true);
//        if(event->button() == Qt::RightButton)
//            std::cout << "selected item id: " << m_wayId << std::endl;
//        else
//            QGraphicsItem::mousePressEvent(event);

//    }
};


#endif // RENDERITEM_H
