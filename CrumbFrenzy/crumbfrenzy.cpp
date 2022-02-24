#include "crumbfrenzy.h"
#include "ui_crumbfrenzy.h"

// Config header
#include "config.h"
// Entity objects
#include <player.cpp>
#include <crumb.cpp>

// Included Libraries
#include <QPushButton>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QtGlobal>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QString>

// includes for popup boxes
#include <QLabel>
#include <QVBoxLayout>
#include <QApplication>
#include <QGridLayout>
#include <QWidget>
#include <QTimer>
#include <QToolBox>

CrumbFrenzy::CrumbFrenzy(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CrumbFrenzy)
{
    ui->setupUi(this);

    // Setup menus
    setupMenus();

}

CrumbFrenzy::~CrumbFrenzy()
{
    // Deconstructs buttons
    delete hostLobbyButton;
    delete hostLobbyBackButton;
    delete joinLobbyBackButton;
    delete controlsBackButton;
    delete joinLobbyButton;
    delete controlsMenuButton;
    delete startGameButton;
    delete quitGameButton;
    delete quitGameLobby;
    delete quitGameHost;
    delete addPlayerButton;
    delete actor;
    delete scoreboard;
    delete scoreHeader;
    delete crumbPiece;
    // Delete controls menu
    delete controlsMenuButton;
    delete controlsMenuButtons;
    delete controlsMenuButtonz;
    delete controls;
    // Deconstructs menus
    delete mainMenu;
    delete lobbyMenu;
    delete joinLobbyMenu;
    delete controlsMenu;
    delete gameScene;
    // Delete menuview
    delete menuView;
    // Deconsructs UI
    delete ui;
}

void CrumbFrenzy::setupMenus()
{
    // Configure Buttons
    hostLobbyButton = new QPushButton("Host Lobby");
    joinLobbyButton = new QPushButton("Join Lobby");
    startGameButton = new QPushButton("Start Game");

    //Control Buttons
    controlsMenuButton  = new QPushButton("Controls");
    controlsMenuButtons  = new QPushButton("Controls");
    controlsMenuButtonz  = new QPushButton("Controls");

    //Quit Buttons
    quitGameButton = new QPushButton("Quit"); //main menu
    quitGameLobby = new QPushButton("Quit"); //host
    quitGameHost = new QPushButton("Quit"); //join

    // Back Buttons
    hostLobbyBackButton = new QPushButton("Back");
    joinLobbyBackButton = new QPushButton("Back");
    controlsBackButton = new QPushButton("Back");

    // Ties host lobby menu button to displayLobbyMenu()
    connect(hostLobbyButton, &QPushButton::clicked, this, &CrumbFrenzy::displayLobbyMenu);
    connect(joinLobbyButton, &QPushButton::clicked, this, &CrumbFrenzy::displayJoinLobbyMenu);
    connect(startGameButton, &QPushButton::clicked, this, &CrumbFrenzy::setupGameScene);

    //Control Game Connects
    connect(controlsMenuButton, &QPushButton::clicked, this, &CrumbFrenzy::displayControlsMenu);
    connect(controlsMenuButtons, &QPushButton::clicked, this, &CrumbFrenzy::displayControlsMenu);
    connect(controlsMenuButtonz, &QPushButton::clicked, this, &CrumbFrenzy::displayControlsMenu);

    //Quit Game Controls
    connect(quitGameButton, &QPushButton::clicked, this, &CrumbFrenzy::quitGame);
    connect(quitGameHost, &QPushButton::clicked, this, &CrumbFrenzy::quitGame);
    connect(quitGameLobby, &QPushButton::clicked, this, &CrumbFrenzy::quitGame);

    // Ties back button to displayMainMenu()
    connect(hostLobbyBackButton, &QPushButton::clicked, this, &CrumbFrenzy::displayMainMenu);
    connect(joinLobbyBackButton, &QPushButton::clicked, this, &CrumbFrenzy::displayMainMenu);
    connect(controlsBackButton, &QPushButton::clicked, this, &CrumbFrenzy::displayMainMenu);

    //Image Manipulation
    QImage img1(":/images/mainmenu.png"); //main menu frog image
    QImage mainmenu = img1.scaled(900, 900, Qt::KeepAspectRatio);

    // Menu Initializations
    // Main Menu
    mainMenu = new QGraphicsScene(-screenWidth, -screenHeight, screenWidth, screenHeight);
    mainMenu->setBackgroundBrush(QBrush(QImage(mainmenu)));

    // Setting position of menu buttons
    hostLobbyButton->setGeometry(-screenWidth/4, (-screenHeight/4) - 156, 100, 50);
    joinLobbyButton->setGeometry(-screenWidth/4, (-screenHeight/4) - 104, 100, 50);
    controlsMenuButton->setGeometry(-screenWidth/4, (-screenHeight/4) - 52, 100, 50);
    quitGameButton->setGeometry(-screenWidth/4, (-screenHeight/4), 100, 50);

    // Adding Buttons to main menu
    mainMenu->addWidget(hostLobbyButton);
    mainMenu->addWidget(joinLobbyButton);
    mainMenu->addWidget(controlsMenuButton);
    mainMenu->addWidget(quitGameButton);

    // Lobby Menu
    lobbyMenu = new QGraphicsScene(-screenWidth, -screenHeight, screenWidth, screenHeight);
    hostLobbyBackButton->setGeometry(-screenHeight/4, (-screenHeight/4), 100, 50);
    quitGameLobby->setGeometry(-screenWidth/4, (-screenHeight/4) - 52, 100, 50);
    controlsMenuButtons->setGeometry(-screenWidth/4, (-screenHeight/4) - 104, 100, 50);
    startGameButton->setGeometry(-screenWidth/4, (-screenHeight/4) - 156, 100, 50);
    lobbyMenu->addWidget(startGameButton);
    lobbyMenu->addWidget(hostLobbyBackButton);
    lobbyMenu->addWidget(controlsMenuButtons);
    lobbyMenu->addWidget(quitGameLobby);
    lobbyMenu->setBackgroundBrush(QBrush(QImage(mainmenu)));

    // Join Lobby Menu
    joinLobbyMenu = new QGraphicsScene(-screenWidth, -screenHeight, screenWidth, screenHeight);
    joinLobbyBackButton->setGeometry(-screenHeight/4, -screenHeight/4, 100, 50);
    quitGameHost->setGeometry(-screenWidth/4, (-screenHeight/4) - 104, 100, 50);
    controlsMenuButtonz->setGeometry(-screenWidth/4, (-screenHeight/4) - 156, 100, 50);
    joinLobbyMenu->addWidget(joinLobbyBackButton);
    joinLobbyMenu->addWidget(controlsMenuButtonz);
    joinLobbyMenu->addWidget(quitGameHost);
    joinLobbyMenu->setBackgroundBrush(QBrush(QImage(mainmenu)));

    // Controls Menu
    controlsMenu = new QGraphicsScene(-screenWidth, -screenHeight, screenWidth, screenHeight);
    controlsBackButton->setGeometry((-screenHeight/4) - 52, 600, 100, 50);
    controlsMenu->addWidget(controlsBackButton);

    // Game Scene
    gameScene = new QGraphicsScene(-screenWidth/2, -screenHeight/2, screenWidth, screenHeight);
    gameScene->setItemIndexMethod(QGraphicsScene::NoIndex);

    QPixmap picnicTableImage(":/images/picnictable.png");
    QGraphicsPixmapItem* picnic = new QGraphicsPixmapItem;
    picnic->setPixmap(picnicTableImage);
    picnic->setPos(-screenWidth/2, -screenHeight/2);
    // Add pixmap to scene
    gameScene->addItem(picnic); 

    // Menu View Initialization
    menuView = new QGraphicsView(mainMenu);

    // Anchors view to center
    menuView->setResizeAnchor(QGraphicsView::AnchorViewCenter);
    menuView->setRenderHint(QPainter::Antialiasing);
    //menuView->setBackgroundBrush(Qt::black);
    setCentralWidget(menuView);

}

void CrumbFrenzy::setupGameScene()
{
    QImage img1(":/images/grass.png"); //In game Grass background
    QImage gamebg = img1.scaled(900, 900, Qt::KeepAspectRatio);

    // All of this is for testing only
    // Spawn players
    addPlayer("chiru");
    // Spawn starter crumbs
    for (int i = 0; i < 5; i++)
    {
        spawnCrumbs();
    }

    drawBoundary();

    // Add scoreboard to scene
    scoreHeader = new QGraphicsTextItem("Crumbs Eaten");
    scoreHeader->setDefaultTextColor(Qt::black);
    //scoreHeader->setPos(-screenWidth/2 + 420, -screenHeight/2 - 40);
    scoreHeader->setPos(-screenWidth/2 + 920, -screenHeight/2 - 20);
    gameScene->addItem(scoreHeader);
    // Show score display
    scoreboard = new QGraphicsTextItem(QString::number(score));
    scoreboard->setDefaultTextColor(Qt::black);
    //scoreboard->setPos(-screenWidth/2 + 459, -screenHeight/2 - 25);
    scoreboard->setPos(-screenWidth/2 + 959, -screenHeight/2);
    gameScene->addItem(scoreboard);
    gameScene->setBackgroundBrush(QBrush(gamebg));

    // All of this is for testing only
    QTimer* timer = new QTimer;
    timer->setInterval(60);
    connect(timer, &QTimer::timeout, gameScene, &QGraphicsScene::advance);
    timer->start();
    qDebug() << "Timer Started";

    menuView->setScene(gameScene);
}

// Sets current scene as main menu
void CrumbFrenzy::displayMainMenu()
{
    menuView->setScene(mainMenu);
}

// Sets current scene as lobby
void CrumbFrenzy::displayLobbyMenu()
{
    menuView->setScene(lobbyMenu);

}

// Sets current scene as the join lobby screen
void CrumbFrenzy::displayJoinLobbyMenu()
{
    menuView->setScene(joinLobbyMenu);

}

void CrumbFrenzy::addPlayer(QString username)
{
    actor = new player;
    actor->setPos(-screenWidth/2, -screenHeight/2);
    gameScene->addItem(actor);
}

void CrumbFrenzy::spawnCrumbs()
{
    crumbPiece = new crumb;
    crumbPiece->setPos(-(qrand() % (screenWidth / 4)), -(qrand() % (screenHeight / 4)));
    gameScene->addItem(crumbPiece);
    connect(crumbPiece, &crumb::ate, this, &CrumbFrenzy::crumbAte);
}
// Actions taken after a crumb has been eaten
void CrumbFrenzy::crumbAte()
{
    score++;
    scoreboard->setPlainText(QString::number(score));
    spawnCrumbs();
}

// Sets current scene as controls menu
void CrumbFrenzy::displayControlsMenu()
{
    controls = new QMessageBox();
    //controls->setText(QString("Flies collect crumbs to increase your team score. Frog eats the flies as the enemy to win. Get the fruit to attack him before he gets all of you."));
    controls->setStandardButtons(QMessageBox::Ok);
    controls->setGeometry(-screenWidth/2, -screenHeight/2, 100, 50);
    controls->setIconPixmap(QPixmap(":/images/controls.png"));
    
    menuView->scene()->addWidget(controls);
    controls->exec();
    if (controls->clickedButton()->text() == "Okay") {
        QCoreApplication::quit();
    }
}

// Quits game
void CrumbFrenzy::quitGame()
{
   // Creating the confirm quit dialog
   confirmQuitDialog = new QMessageBox();
   // Adds text to dialog
   confirmQuitDialog->setText(QString("Are you sure you want to quit?"));
   // Adds default buttons
   confirmQuitDialog->setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
   // Moves dialog to specific position (x, y. box width, box height)
   confirmQuitDialog->setGeometry(-screenWidth/4, -screenHeight/4, 100, 50);
   // Adds to current scene
   menuView->scene()->addWidget(confirmQuitDialog);
   // Shows dialog
   confirmQuitDialog->exec();
   // If "OK", exit. If "Cancel", don't
   if (confirmQuitDialog->clickedButton()->text() == "OK")
   {
        //socket->close();
        QApplication::quit();
   }

   else if (confirmQuitDialog->clickedButton()->text() == "Cancel")
   {

       confirmQuitDialog->hide();
   }
}

void CrumbFrenzy::keyPressEvent(QKeyEvent *e)
{
    if (e)
    {
        switch (e->key())
        {
            case Qt::Key_A:
            case Qt::Key_J:         actor->goLeft();
                                    break;

            case Qt::Key_D:
            case Qt::Key_L:         actor->goRight();
                                    break;

            case Qt::Key_W:
            case Qt::Key_I:         actor->goUp();
                                    break;

            case Qt::Key_S:
            case Qt::Key_K:         actor->goDown();
                                    break;

            //case Qt::Key_Space:     actor->attack();
            //                        break;

            case Qt::Key_Escape:    quitGame();
                                    break;

            case Qt::Key_C:         displayControlsMenu();
                                    break;

            default:                actor->stop();
                                    break;
        }
    }

    QMainWindow::keyPressEvent(e);
}

void CrumbFrenzy::drawBoundary()
{

    int w = screenWidth;    // Define w,h shortcuts names
    int h = screenHeight;

    QGraphicsLineItem* topline = gameScene->addLine(-w/2, -h/2, w/2, -h/2);
    topline->setPen(QPen(Qt::white));

    QGraphicsLineItem* bottomline = gameScene->addLine(-w/2, h/2, w/2, h/2);
    bottomline->setPen(QPen(Qt::white));

    QGraphicsLineItem* leftline = gameScene->addLine(-w/2, -h/2, -w/2, h/2);
    leftline->setPen(QPen(Qt::white));

    QGraphicsLineItem* rightline = gameScene->addLine(w/2, -h/2, w/2, h/2);
    rightline->setPen(QPen(Qt::white));

}


