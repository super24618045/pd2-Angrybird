#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QList>
#include <QDesktopWidget>
#include <QTimer>
#include <Box2D/Box2D.h>
#include <QMouseEvent>
#include <iostream>
#include<QPixmap>
#include <gameitem.h>
#include <land.h>
#include "bird.h"
#include "box.h"
#include "rectangle.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow,public b2ContactListener
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void showEvent(QShowEvent *);
    bool eventFilter(QObject *,QEvent *event);
    void closeEvent(QCloseEvent *);
    void create();
    void deletething();
    //void killpig();
    /*int screenW=960;
    int screenH=540;
    int cons=20;*/
    //int i;
    float posx;
    float posy;
    float shootx=5.0f;
    float shooty=8.0f;
    Bird* birdie[5];
    Box *pig;
    bool onetime=true;
    bool checkrelease=false;
    bool checkkeep=false;
    bool fatguy=false;
    bool yellow_rush=false;
    bool blueone=false;
    QGraphicsPixmapItem * shoot;
    QGraphicsPixmapItem * buttons;
    void BeginContact(b2Contact *contact);
    bool shooting=false;
    int enemycount=1;/*an enemy*/
    int birdcount=-1;
    int collitime=0;
signals:
    // Signal for closing the game
    void quitGame();

private slots:
    void tick();
    // For debug slot
    void QUITSLOT();
private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    b2World *world;
    QList<GameItem *> itemList;
    QList<GameItem*> deletelist;
    QTimer timer;
};

#endif // MAINWINDOW_H
