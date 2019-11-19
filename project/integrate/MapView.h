#ifndef MAPVIEW_H
#define MAPVIEW_H
#include <QGraphicsView>
#include <QMouseEvent>
#include <QWheelEvent>
#include <iostream>


#define MAX_SCALE 10
#define MIN_SCALE 0.0002
#define ZOOM_STEP 1.2

class MapView : public QGraphicsView
{
private:
    qreal m_scale;


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
        m_scale = 0.01;
    }
    ~MapView(){}
};



#endif // MAPVIEW_H
