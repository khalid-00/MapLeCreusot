/*
* @author Deng Jianning
* @contact Jianning_Deng@etu.u-bourgogne.fr
* @date  30-11-2019
*/
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
#define MIN_SCALE 0.00000001
#define ZOOM_STEP 1.2

#include <QMouseEvent>
#include <QGraphicsView>
#include <QObject>

class MapView : public QGraphicsView
{
    Q_OBJECT
private:
    enum userState{init, sourceSel, destSel, routing, search, null};
    qreal m_scale;
    Multipolygon* m_selectedItem;
    bool m_isBuilding;
    userState m_state;
    QPoint m_pressPos;
    idType m_srcId;
    idType m_destId;

    void mousePressEvent(QMouseEvent *event);

    void contextMenuEvent(QContextMenuEvent *event);

    void wheelEvent(QWheelEvent *event);

signals:
    void setSource(Multipolygon *item);
    void setDest(Multipolygon *item);
    void searchPlace();
    void canecl(); //delete all temporary render item
    void makeRoute();

public slots:
    void changeToSearch();
    void changeToInit();

public:
    MapView();

    ~MapView();
};



#endif // MAPVIEW_H
