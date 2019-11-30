#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "model.h"
#include <map>
#include "modelDataStructure.h"
#include <iostream>
#include <QResizeEvent>
#include <QTime>
#include <time.h>
#include "SceneBuilder.h"
#include "MapView.h"
#include <QVBoxLayout>
#include <QLayout>
#include <mygraphbuilder.h>
#include <myalgorithm.h>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_model(new Model)
//    , m_layoutView(new QVBoxLayout)
{
    ui->setupUi(this);
    m_mapView = new MapView();
    m_sceneBuilder = new SceneBuilder(m_model);
    m_mapView->setDragMode(QGraphicsView::ScrollHandDrag);
    m_mapView->setGeometry(QRect(0,50,100,100));
//    ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
//    loadFile("/home/dj/git/cpp_project/data/small.xml");
//    loadFile("/home/dj/git/cpp_project/data/test.xml");
    loadFile("/home/dj/git/cpp_project/data/Le_Creusot.pbf");
    //  loadFile("G:/QT/Projects/database/Le_Creusot.osm.pbf");
    m_scale = 1;

//    connecting signals and slots for UI
    connect(m_mapView, &MapView::setSource, m_sceneBuilder, &SceneBuilder::setSource);
    connect(m_mapView, &MapView::setDest, m_sceneBuilder, &SceneBuilder::setDest);
    connect(m_mapView, &MapView::searchPlace, m_sceneBuilder, &SceneBuilder::searchPlace);
    connect(m_mapView, &MapView::canecl, m_sceneBuilder, &SceneBuilder::cancel);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_model;
}

void MainWindow::loadFile(string filePath)
{

    clock_t start = clock();
    m_model->setFilePath(filePath);
    auto mpMap = m_model->getMPMap();
    std::cout << "number of multipolygon found: " << mpMap.size()/*m_model->getMPMap().size()*/ << std::endl;

    float_t t = (clock() - start + 0.0)/CLOCKS_PER_SEC;
    std::cout << "time used for loading file: " << t << "s" << std::endl;


    start = clock();
    m_sceneBuilder->addPolyItem();
    m_sceneBuilder->addRoadItem();

    t = (clock() - start + 0.0)/CLOCKS_PER_SEC;
    std::cout << "time used for rendering the map: " << t << "s" << std::endl;

    m_mapView->setScene(m_sceneBuilder->getScene());

    m_mapView->setBackgroundBrush(QBrush(QColor(230,230,230)));
//    m_mapView->scale(2,2);

    m_mapView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    QLayout *map = layout();
    map->addWidget(m_mapView);
    this->setLayout(map);

}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    viewSizeAdjust(event);
}


void MainWindow::viewSizeAdjust(QResizeEvent *event)
{
    int newWidth, newHeight;
    newWidth = event->size().width();
    newHeight = event->size().height() - m_mapView->pos().y();
    m_mapView->setGeometry(QRect(0,m_mapView->pos().y(),newWidth,newHeight));
    osmium::Location test = m_model->getNodeLoaction(1703604687);
    auto pos = projection(test.lon(), test.lat());
    QTransform empty;
    QGraphicsItem *testitem = m_mapView->scene()->itemAt(pos, empty);

    //============== example code for retreiving an object base on position ============
    Multipolygon *casttest = new Multipolygon;
    std::cout << qgraphicsitem_cast<Multipolygon *>(testitem) << std::endl;
    std::cout <<"item type num: " << testitem->type() << std::endl;
    std::cout << "type for Multipoligon is " << casttest->type() << std::endl;
    std::cout << "the id of the way is " << casttest->getId() << std::endl;
    //==================================================================================

}

//void MainWindow::wheelEvent(QWheelEvent *event)
//{
//    if(event->delta()>0)
//    {
//        ui->graphicsView->scale(1.25,1.25);
//    }
//    else if(event->delta() < 0)
//    {
//        ui->graphicsView->scale(0.75,0.75);
//    }
//    ui->graphicsView->update();
//}
