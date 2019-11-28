#ifndef MAPVIEW_H
#define MAPVIEW_H
#include <QGraphicsView>
#include <QMouseEvent>
#include <QWheelEvent>
#include <iostream>
#include <QGraphicsItem>
#include "RenderItem.h"
#include <iostream>
#include <QContextMenuEvent>

#define MAX_SCALE 10
#define MIN_SCALE 0.0001
#define ZOOM_STEP 1.2

#include <QMouseEvent>
#include <QGraphicsView>

class MapView : public QGraphicsView
{
private:
    qreal m_scale;

    void mousePressEvent(QMouseEvent *event)
    {
        if(event->button() == Qt::LeftButton)
            QGraphicsView::mousePressEvent(event);
        else if(event->button() == Qt::RightButton)
        {
            auto pos = event->pos();
            auto scenePos = mapToScene(pos);
            std::cout << "mouse press" << std::endl;
//            std::cout << "position from mapview is " << pos.x() << ", " << pos.y() << std::endl;
            auto item = this->scene()->itemAt(scenePos, QTransform());
            if(qgraphicsitem_cast<Multipolygon *>(item))
            {
                auto casted = qgraphicsitem_cast<Multipolygon *>(item);
                std::cout << "type cast and selection success, with id num = " << casted->getId() << std::endl;
            }
            QGraphicsView::mousePressEvent(event);
        }
        else
            QGraphicsView::mousePressEvent(event);
    }

    void contextMenuEvent(QContextMenuEvent *event)
    {
        std::cout << "menu pop out" << std::endl;

        QMenu menu;
        menu.addAction("Action 1");
        menu.addAction("Action 2");
        QAction *a = menu.exec(event->globalPos());
        if(a != nullptr)
            qDebug("User clicked %s", qPrintable(a->text()));
    }

    void wheelEvent(QWheelEvent *event)
    {
        if(event->delta()>0)
        {
            if(m_scale < MAX_SCALE)
            {
                std::cout << m_scale << std::endl;
                this->scale(ZOOM_STEP, ZOOM_STEP);
                m_scale *= ZOOM_STEP;
            }
        }
        else if(event->delta() < 0)
        {
            if(m_scale >= MIN_SCALE)
            {
                std::cout << m_scale << std::endl;
                this->scale(1/ZOOM_STEP, 1/ZOOM_STEP);
                m_scale *= 1/ZOOM_STEP;
            }
        }
//        this->update();
    }

public:
    MapView()
    {
        m_scale = 0.001;
    }
    ~MapView(){}
};



#endif // MAPVIEW_H
