#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Enable the event Filter

    qApp->installEventFilter(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showEvent(QShowEvent *)
{
    // Setting the QGraphicsScene
    scene = new QGraphicsScene(0,0,width(),ui->graphicsView->height());
    ui->graphicsView->setScene(scene);

    //shooter
    shoot=new QGraphicsPixmapItem();
    shoot->setPixmap(QPixmap(":/image/B_ATRAIN_1.png").scaled(57,150));
    shoot->setPos(150,320);
    scene->addItem(shoot);
    //restart
    buttons=new QGraphicsPixmapItem();
    buttons->setPixmap(QPixmap(":/image/DUMBELL").scaled(57,57));
    buttons->setPos(800,100);
    scene->addItem(buttons);
    // Create world
    world = new b2World(b2Vec2(0.0f, -9.8f));
    // Setting Size
    GameItem::setGlobalSize(QSizeF(32,18),size());
    // Create ground (You can edit here)
    /*0*/itemList.push_back(new Land(16,1.5f,32,3,QPixmap(":/ground.png").scaled(960,90),world,scene));
    /*1*/itemList.push_back(new Land(32,12,3,18,QPixmap(":/ground.png").scaled(90,540),world,scene));
    /*1.5*/itemList.push_back(new Land(0.1f,12,1,18,QPixmap(":/ground.png").scaled(30,540),world,scene));
    /*1.75*/itemList.push_back(new Land(8,3.5f,6,1.0f,QPixmap(":/ground.png").scaled(180,30),world,scene));
    //width 960 height 540
    // Create bird (You can edit here)
    birdie[0] = new Bird(5.0f,7.0f,0.8f,&timer,QPixmap(":/bird.png").scaled(48,48),world,scene);
    birdie[0]->g_body->SetGravityScale(0);
    birdie[1] = new Bird(3.0f,3.0f,0.6f,&timer,QPixmap(":/image/BIRD_YELLOW.png").scaled(36,36),world,scene);
    birdie[2] = new Bird(2.0f,3.0f,1.0f,&timer,QPixmap(":/image/BIRD_BIG_BROTHER_YELL.png").scaled(60,60),world,scene);
    birdie[3] = new Bird(5.0f,3.5f,0.4f,&timer,QPixmap(":/image/BIRD_BLUE_YELL.png").scaled(24,24),world,scene);
    Rectangle *rectangle = new Rectangle(18.0f,2.5f,1.8f,1.9f,&timer,QPixmap(":/image/box.png").scaled(57,57),world,scene);
    Rectangle *rectangle1 = new Rectangle(18.0f,6.0f,1.8f,1.9f,&timer,QPixmap(":/image/box.png").scaled(57,57),world,scene);
    Rectangle *rectangle2 = new Rectangle(22.0f,2.5f,1.8f,1.9f,&timer,QPixmap(":/image/box.png").scaled(57,57),world,scene);
    Rectangle *rectangle3 = new Rectangle(22.0f,6.0f,1.8f,1.9f,&timer,QPixmap(":/image/box.png").scaled(57,57),world,scene);
    pig = new Box(20.0f,5.0f,1.0f,&timer,QPixmap(":/image/pig1.png").scaled(60,60),world,scene);
    /*2*/itemList.push_back(pig);
    /*3*/itemList.push_back(rectangle);
    /*4*/itemList.push_back(rectangle1);
    /*5*/itemList.push_back(rectangle2);
    /*6*/itemList.push_back(rectangle3);
    /*7*/itemList.push_back(birdie[0]);
    /*8*/itemList.push_back(birdie[1]);
    /*9*/itemList.push_back(birdie[2]);
    /*10*/itemList.push_back(birdie[3]);
    //set contact
    world->SetContactListener(this);
    // Timer
    connect(&timer,SIGNAL(timeout()),this,SLOT(tick()));
    connect(this,SIGNAL(quitGame()),this,SLOT(QUITSLOT()));
    timer.start(100/6);
}

bool MainWindow::eventFilter(QObject *, QEvent *event)
{
    // Hint: Notice the Number of every event!
    if(event->type() == QEvent::MouseButtonPress)
    {
        /* TODO : add your code here */
        QMouseEvent* e=static_cast<QMouseEvent*>(event);
        posx=e->x();
        posy=e->y();

        if(onetime==true)
        {

            checkrelease=false;
            /*bird ability*/
            if(yellow_rush==true)
            {
                yellow_rush=false;
                float newvol_x;
                float newvol_y;
                newvol_x=birdie[1]->g_body->GetLinearVelocity().x;
                newvol_y=birdie[1]->g_body->GetLinearVelocity().y;
                birdie[1]->setLinearVelocity(b2Vec2(newvol_x*3,newvol_y*3));
            }
            if(fatguy==true)
            {
                fatguy=false;
                float new2vol_x;
                float new2vol_y;
                new2vol_x=birdie[2]->g_body->GetLinearVelocity().x;
                new2vol_y=abs(birdie[2]->g_body->GetLinearVelocity().y);
                birdie[2]->setLinearVelocity(b2Vec2(new2vol_x,new2vol_y*-5));

            }
            if(blueone==true)
            {
                blueone=false;
                birdie[3]->g_body->SetAngularDamping(0.8);
                birdie[3]->g_body->SetAngularVelocity(100);

            }
            /*the first bird*/
            if(checkrelease==false&&checkkeep==false&&birdcount==0)
            {
            birdie[0]->g_body->SetTransform(b2Vec2(posx/30,(540-posy)/30),0);
            }
            /*the second bird*/
            if(checkrelease==false&&checkkeep==false&&birdcount==1)
            {
            birdie[1]->g_body->SetTransform(b2Vec2(posx/30,(540-posy)/30),0);
            yellow_rush=true;
            }
            /*the third bird*/
            if(checkrelease==false&&checkkeep==false&&birdcount==3)
            {
            birdie[2]->g_body->SetTransform(b2Vec2(posx/30,(540-posy)/30),0);
            fatguy=true;
            }
            if(checkrelease==false&&checkkeep==false&&birdcount==5)
            {
            birdie[3]->g_body->SetTransform(b2Vec2(posx/30,(540-posy)/30),0);
            blueone=true;
            }
            checkkeep=true;
            /*check shooting*/
            if(posx<850&&posx>750&&posy>120&&posy<160)
            {
                shooting=true;
                std::cout << posx<< std::endl ;
                timer.stop();
                deletething();
            }
            //std::cout << "Press !" << std::endl ;
        // std::cout << posx << std::endl ;
        onetime=false;
        }
        //count++;
    }

    if(event->type() == QEvent::MouseMove)
    {
        /* TODO : add your code here */
        QMouseEvent* f=static_cast<QMouseEvent*>(event);
        posx=f->x();
        posy=f->y();

        if(checkkeep==true&&checkrelease==false)
        {
            if((posx>100&&posx<280)&&(posy>210&&posy<440)&&birdcount==0)
            {
                birdie[0]->g_body->SetTransform(b2Vec2(posx/30,(540-posy)/30),0);
            }
            if((posx>100&&posx<280)&&(posy>210&&posy<440)&&birdcount==1)
            {
                birdie[1]->g_body->SetTransform(b2Vec2(posx/30,(540-posy)/30),0);
            }
            if((posx>100&&posx<280)&&(posy>210&&posy<440)&&birdcount==3)
            {
                birdie[2]->g_body->SetTransform(b2Vec2(posx/30,(540-posy)/30),0);
            }
            if((posx>100&&posx<280)&&(posy>210&&posy<440)&&birdcount==5)
            {
                birdie[3]->g_body->SetTransform(b2Vec2(posx/30,(540-posy)/30),0);
            }

        }
        //std::cout << "Move !" << std::endl ;

    }
    if(event->type() == QEvent::MouseButtonRelease)
    {
        /* TODO : add your code here */
        if(onetime==false)
       {
           checkrelease=true;
           checkkeep=false;
           if(birdcount==0)
           {
                birdie[0]->setLinearVelocity(b2Vec2((shootx-posx/30)*3,(shooty-(540-posy)/30)*3));
                birdie[0]->g_body->SetGravityScale(1);

           }
           if(birdcount==1)
           {
                birdie[1]->setLinearVelocity(b2Vec2((shootx-posx/30)*3,(shooty-(540-posy)/30)*3));
           }
           if(birdcount==3)
           {
                birdie[2]->setLinearVelocity(b2Vec2((shootx-posx/30)*3,(shooty-(540-posy)/30)*5));
           }
           if(birdcount==5)
           {
                birdie[3]->setLinearVelocity(b2Vec2((shootx-posx/30)*3,(shooty-(540-posy)/30)*3));
           }           
           std::cout << "Release !" << std::endl;
        birdcount++;
       }
       onetime=true;
    }
    return false;
}

void MainWindow::closeEvent(QCloseEvent *)
{
    // Close event
    emit quitGame();
}

void MainWindow::tick()
{
    world->Step(1.0/60.0,6,2);
    scene->update();
}

void MainWindow::QUITSLOT()
{
    // For debug
    std::cout << "Quit Game Signal receive !" << std::endl ;

}
/*void MainWindow::BeginContact(b2Contact *contact)
{

    //ya=contact->GetFixtureB()->GetBody()->GetLinearVelocity().x*30;
    //b2Vec2 v2=contact->GetFixtureB()->GetBody()->GetLinearVelocity();
    GameItem *athing=static_cast<GameItem *>(contact->GetFixtureA()->GetUserData());
    GameItem *bthing=static_cast<GameItem *>(contact->GetFixtureB()->GetUserData());
        for(i=0;i<8;i)
        std::cout << "sss" << std::endl ;
}*/
void MainWindow::create()
{
    /*0*/itemList.push_back(new Land(16,1.5f,32,3,QPixmap(":/ground.png").scaled(960,90),world,scene));
    /*1*/itemList.push_back(new Land(32,12,3,18,QPixmap(":/ground.png").scaled(90,540),world,scene));
    /*1.5*/itemList.push_back(new Land(0.1f,12,1,18,QPixmap(":/ground.png").scaled(30,540),world,scene));
    /*1.75*/itemList.push_back(new Land(8,3.5f,6,1.0f,QPixmap(":/ground.png").scaled(180,30),world,scene));
    birdie[0] = new Bird(5.0f,7.0f,0.8f,&timer,QPixmap(":/bird.png").scaled(48,48),world,scene);
    birdie[0]->g_body->SetGravityScale(0);
    birdie[1] = new Bird(3.0f,3.0f,0.6f,&timer,QPixmap(":/image/BIRD_YELLOW.png").scaled(36,36),world,scene);
    birdie[2] = new Bird(2.0f,3.0f,1.0f,&timer,QPixmap(":/image/BIRD_BIG_BROTHER_YELL.png").scaled(60,60),world,scene);
    birdie[3] = new Bird(5.0f,3.5f,0.4f,&timer,QPixmap(":/image/BIRD_BLUE_YELL.png").scaled(24,24),world,scene);
    Rectangle *rectangle = new Rectangle(18.0f,2.5f,1.8f,1.9f,&timer,QPixmap(":/image/box.png").scaled(57,57),world,scene);
    Rectangle *rectangle1 = new Rectangle(18.0f,6.0f,1.8f,1.9f,&timer,QPixmap(":/image/box.png").scaled(57,57),world,scene);
    Rectangle *rectangle2 = new Rectangle(22.0f,2.5f,1.8f,1.9f,&timer,QPixmap(":/image/box.png").scaled(57,57),world,scene);
    Rectangle *rectangle3 = new Rectangle(22.0f,6.0f,1.8f,1.9f,&timer,QPixmap(":/image/box.png").scaled(57,57),world,scene);
    pig = new Box(20.0f,5.0f,1.0f,&timer,QPixmap(":/image/pig1.png").scaled(60,60),world,scene);
    /*2*/itemList.push_back(pig);
    /*3*/itemList.push_back(rectangle);
    /*4*/itemList.push_back(rectangle1);
    /*5*/itemList.push_back(rectangle2);
    /*6*/itemList.push_back(rectangle3);
    /*7*/itemList.push_back(birdie[0]);
    /*8*/itemList.push_back(birdie[1]);
    /*9*/itemList.push_back(birdie[2]);
    /*10*/itemList.push_back(birdie[3]);
}

void MainWindow::deletething()
{

    if(shooting==true)
    {

        for(int i=0;i<itemList.length();i++)
        {
        deletelist.push_back(itemList.at(i));
        }
        for(int i=0;i<deletelist.length();i++)
        {
        GameItem *temp=deletelist.at(i);
        delete temp;
        }
        deletelist.clear();
        itemList.clear();
        shooting=false;
        birdcount=-1;
        create();
        timer.start(100/6);
    }
}
/*void MainWindow::killpig()
{
    deletelist.push_back(pig);
    for(i=0;i<deletelist.length();i++)
    {
    GameItem *temp=deletelist.at(i);
    delete temp;
    }
}*/

