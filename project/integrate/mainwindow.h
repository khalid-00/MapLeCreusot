#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "model.h"
#include <QGraphicsView>
#include <string>
#include <MapView.h>
#include <QVBoxLayout>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    vector <idType> mypath;
    bool m_leftMousePressed;
    Ui::MainWindow *ui;
    MapView *m_mapView;
//    QVBoxLayout *m_layoutView;
    Model *m_model;
    qreal m_scale;
    void loadFile(string );
    void resizeEvent(QResizeEvent *event);
    void viewSizeAdjust(QResizeEvent *event);
//    void wheelEvent(QWheelEvent *event);

};
#endif // MAINWINDOW_H
