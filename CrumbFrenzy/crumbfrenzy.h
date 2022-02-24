#ifndef CRUMBFRENZY_H
#define CRUMBFRENZY_H

#include <QMainWindow>
// Included Libraries
#include <QPushButton>
#include <QGraphicsScene>
#include <QMessageBox>
#include <QKeyEvent>
#include "player.h"
#include <crumb.h>

namespace Ui {
class CrumbFrenzy;
}

class CrumbFrenzy : public QMainWindow {
    Q_OBJECT

public:
    explicit CrumbFrenzy(QWidget *parent = nullptr);
    ~CrumbFrenzy();

private:
    Ui::CrumbFrenzy *ui;

    // Custom buttons
    QPushButton* hostLobbyButton;
    QPushButton* joinLobbyButton;
    QPushButton* startGameButton;

    //Control Buttons
    QPushButton* controlsLobbyButton;
    QPushButton* controlsHostButton;
    QPushButton* controlsMenuButton;
    QPushButton* controlsMenuButtons;
    QPushButton* controlsMenuButtonz;
    //Quit Buttons
    QPushButton* quitGameButton;
    QPushButton* quitGameLobby;
    QPushButton* quitGameHost;
    QPushButton* addPlayerButton;
    // Back Buttons
    QPushButton* hostLobbyBackButton;
    QPushButton* joinLobbyBackButton;
    QPushButton* controlsBackButton;

    // Menus
    QGraphicsScene* mainMenu = nullptr;
    QGraphicsScene* lobbyMenu = nullptr;
    QGraphicsScene* joinLobbyMenu = nullptr;
    QGraphicsScene* controlsMenu = nullptr;
    // Play Area scene
    QGraphicsScene* gameScene = nullptr;

    player* actor = nullptr;
    // Crumb object
    crumb* crumbPiece = nullptr;

    //QGraphicsScene* controlsMenu = nullptr;
    // Confirm quit game dialog
    QMessageBox* confirmQuitDialog = nullptr;
    // Control Pop-up
    QMessageBox* controls = nullptr;
    QPixmap* pm = nullptr;
    // Main window
    QGraphicsView* menuView = nullptr;
    //add player non-modal pop up
    QDialog* addplayerMenu = nullptr;

    // Score
    uint score = 0;
    QGraphicsTextItem* scoreboard = nullptr;
    QGraphicsTextItem* scoreHeader = nullptr;

    // Misc Functions
    // Called at boot to build the menus
    void setupMenus();
    // Sets up game scene
    void setupGameScene();
    // Actions for when crumb is eaten
    void crumbAte();
    // Function to add player
    void addPlayer(QString username);
    //crumb randomized in maze
    void spawnCrumbs();
    // Draw bounds
    void drawBoundary();


private slots:
    // Function to render main menu
    void displayMainMenu();
    // Function to render lobby menu
    void displayLobbyMenu();
    // Function to render join lobby menu
    void displayJoinLobbyMenu();
    // Function to render controls menu
    void displayControlsMenu();
    // Function to quit game
    void quitGame();

protected:

    void keyPressEvent(QKeyEvent *e);
};

#endif // CRUMBFRENZY_H
