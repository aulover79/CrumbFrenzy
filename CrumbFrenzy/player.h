#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsItem>
#include <QRegularExpressionValidator>
#include <QPixmap>
#include <QPainter>
#include <QtDebug>
#include "config.h"

const int num_images = 8;

class player : public QGraphicsItem
{
public:
    // Constructor
    // Construct without username provided
    player(QGraphicsItem *parent = nullptr);
    // Deconstructor
    ~player() override;
    // Returns bool of if player is frog
    bool isFrog();
    // Returns username
    QRegularExpressionValidator getUsername();
    // username
    void setUsername(QString inputUsername);
    // Frog type
    void setFrog(bool froggystomp);

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    //movements
    void goLeft();
    void goRight();
    void goUp();
    void goDown();
    void stop();
    void attack();
    void advance(int step) override;

private:
    // Stores if the player is frog
    // Connection Information
    QString username;
    // Froggy
    bool froggo;

    //animation
    QPixmap images[num_images];
    int index;
    int offset;

    //current position
    qreal x = 0.0;
    qreal y = 0.0;

    //fixed increments
    qreal player_dx_frog = 5.5;
    qreal player_dy_frog = 5.5;
    qreal player_dx_fly = 3.0;
    qreal player_dy_fly = 3.0;

    //direction of travel
    qreal dx = 0.0;
    qreal dy = 0.0;
};

#endif // PLAYER_H
