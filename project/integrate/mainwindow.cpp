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
    //===================================================================
    //start
    //-----------------------------------
    // My Places
    Path MyPlaces ;
    //auto iter = MyPlaces.begin();
    MyPlaces.push_back(1545694404); //1 Aldi
    MyPlaces.push_back(1544558355); //2 Restaurant Le Fut
    MyPlaces.push_back(1455348628); //3 place schnider
    MyPlaces.push_back(1540689869); //4 Acacias
    MyPlaces.push_back(442028765);  //5 IUT
    MyPlaces.push_back(1387416514); //6 Train Station (Gare du Creusot)
    MyPlaces.push_back(1829507841); //7 Carrefour
    MyPlaces.push_back(2019043458); //8 Condorcet
    MyPlaces.push_back(2258325836); //9 Hospital Creusot
    MyPlaces.push_back(1544079469); //10 BNP PariBank
    MyPlaces.push_back(889114982); //11 Action Store
    MyPlaces.push_back(1540689876);//12 El-Loco Cafe
    MyPlaces.push_back(2244694498);//13 Residence Jean Monnent
    MyPlaces.push_back(1540680545);//14 Crous Office & Restaurant
    MyPlaces.push_back(4846313478);//15 Euro Lav(Laundry)
    MyPlaces.push_back(1540689863);//16 Pharmacie des Acacias
    MyPlaces.push_back(1544558417);//17 centre medico scolaire (Medical school)
    MyPlaces.push_back(1544558167);//18 Driving School
    MyPlaces.push_back(2019027442);//19 Le Poste
    MyPlaces.push_back(6269205284);//20 McDonald's
    //-----------------------------------
    ShortPath route(MyPlaces.at(3),MyPlaces.at(18),*m_model);
    Path anypath =route.getYourPath();
    m_sceneBuilder->drawRoute(anypath);// send your route list here, it will draw
    //End
    //===================================================================
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

