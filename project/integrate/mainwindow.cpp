/*
* @author Deng Jianning
* @contact Jianning_Deng@etu.u-bourgogne.fr
* @date  30-11-2019
*/
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
#include <QInputDialog>
#include <QMessageBox>

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
    //  loadFile("G:/QT/Projects/database/Le_Creusot.osm.pbf");

    //m_scale is on longer used, relative code will be deleted soon
    m_scale = 1;

    QLayout *map = layout();
    map->addWidget(m_mapView);
    this->setLayout(map);

//    connecting signals and slots for UI
    connect(m_mapView, &MapView::setSource, m_sceneBuilder, &SceneBuilder::setSource);
    connect(m_mapView, &MapView::setDest, m_sceneBuilder, &SceneBuilder::setDest);
    connect(this, &MainWindow::sendSearchName, m_sceneBuilder, &SceneBuilder::searchPlace);
    connect(m_mapView, &MapView::searchPlace, this, &MainWindow::getSearchName);
    connect(m_mapView, &MapView::canecl, m_sceneBuilder, &SceneBuilder::cancel);
    connect(m_mapView, &MapView::makeRoute, m_sceneBuilder, &SceneBuilder::getSrcDestId);
    connect(m_sceneBuilder, &SceneBuilder::routeSrcAndDest, this, &MainWindow::getRoutePath);
    connect(this, &MainWindow::changeToInit, m_mapView, &MapView::changeToInit);
    connect(this, &MainWindow::changeToSearch, m_mapView, &MapView::changeToSearch);
//    connect(this, )

    // this function should be connected to the UI tool bar
    // I keep this here just for debug
    // just comment this line when Belal finish the tool bar
    loadFile("/home/dj/git/cpp_project/data/Le_Creusot.pbf");

}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_model;
}

void MainWindow::loadFile(string filePath)
{

    // =================== load file ==========================
    clock_t start = clock();
    m_model->setFilePath(filePath);
    auto mpMap = m_model->getMPMap();
    std::cout << "number of multipolygon found: " << mpMap.size() << std::endl;

    float_t t = (clock() - start + 0.0)/CLOCKS_PER_SEC;
    std::cout << "time used for loading file: " << t << "s" << std::endl;
    emit changeToInit();

    // =================== render map ==========================
    start = clock();

    m_sceneBuilder->addPolyItem();
    m_sceneBuilder->addRoadItem();
//    m_sceneBuilder->drawPointText();

    t = (clock() - start + 0.0)/CLOCKS_PER_SEC;
    std::cout << "time used for rendering the map: " << t << "s" << std::endl;

    // ============ generate catalog for searching =============
    start = clock();

    m_model->buildAmenityCatalog();

    t = (clock() - start + 0.0)/CLOCKS_PER_SEC;
    std::cout << "time used for generating the catalog: " << t << "s" << std::endl;

    m_mapView->setScene(m_sceneBuilder->getScene());

    m_mapView->setBackgroundBrush(QBrush(QColor(230,230,230)));

    m_mapView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

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
}

// place belal's routing function in this slot
void MainWindow::getRoutePath(idType src, idType dest)
{
    vector<idType> route;
    // belal's function to get path, and assigned it to route vector;

    emit drawRoute(route);
}

void MainWindow::getSearchName()
{
    bool ok;

    QString text = QInputDialog::getText(this, tr("Search"),
                                        tr("place name:"), QLineEdit::Normal,
                                        "aldi", &ok);

    std::cout << text.toStdString() << std::endl;

    if(ok && text.size() != 0)
    {
        //do all the things in sceneBuilder and then decide if we should change to Search state;
        if(m_sceneBuilder->searchPlace(text))
        {
            emit changeToSearch();

            //qmsgBox for debug
            QMessageBox msgBox;
            msgBox.setText("found!");
            msgBox.setInformativeText(text);
            msgBox.exec();
        }
        else
        {
            emit changeToInit();

            //qmsgBox for debug
            QMessageBox msgBox;
            msgBox.setText("didn't find the place named:");
            msgBox.setInformativeText(text);
            msgBox.exec();
        }
    }
}

