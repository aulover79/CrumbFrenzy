#include "player.h"
#include <config.h>

player::player(QGraphicsItem *parent) : QGraphicsItem(parent)
{
    for (int k = 1; k < num_images; k++){
        QString s = ":/images/frog" + QString::number(k) + QString(".png");
        images[k] = QPixmap(s);
        images[k] = images[k].scaled(playerwidth, playerheight);
    }

    index = 0;
    offset = 0;
    froggo = true;
}

player::~player() {

}
// sets username
void player::setUsername(QString inputUsername)
{
   username = inputUsername;
}
// Sets if player is frog
void player::setFrog(bool froggystomp)
{

    froggo = froggystomp;

}

void player::goLeft() {

    if(froggo == false) {
        dx = -player_dx_fly;
        dy = 0.0;
        //offset
        // For testing only

    }
    else {
        dx = -player_dx_frog;
        dy = 0.0;
        //offset
    }

}

void player::goRight() {
    if(froggo == false) {
        dx = player_dx_fly;
        dy = 0.0;
        //add offset
    }
    else {
        dx = player_dx_frog;
        dy = 0.0;
        //add offset
    }
}

void player::goUp() {
    if(froggo == false) {
        dx = 0.0;
        dy = -player_dy_fly;
        //add offset
    }
    else {
        dx = 0.0;
        dy = -player_dy_frog;
        //add offset
    }
}

void player::goDown() {
    if(froggo == false) {
        dx = 0.0;
        dy = player_dy_fly;
        //add offset
    }
    else {
        dx = 0.0;
        dy = player_dy_frog;
        //add offset
    }
}

void player::stop() {
    if(froggo == false) {
        dx = 0.0;
        dy = 0.0;
        //add offset
    }
    else {
        dx = 0.0;
        dy = 0.0;
        //add offset
    }
}

QRectF player::boundingRect() const
{
    return QRectF(-playerwidth/2, -playerheight/2, playerwidth, playerheight);
}

QPainterPath player::shape() const
{
    QPainterPath path;
    path.addRect(-playerwidth/2, -playerheight/2, playerwidth, playerheight);
    return path;
}

void player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    index = (index + 1) % num_images;
    painter->drawPixmap(-playerwidth/2, -playerheight/2, images[index + offset]);
}

void player::advance(int step)
{
    if (step == 0)
    {
        return;
    }

    // Compute new coordinates
    x = this->pos().rx();
    y = this->pos().ry();
    x = x + dx;
    y = y + dy;



//insert bounds here
//example in Day14code
    if (x < -screenWidth/2 + playerwidth/2)
    {
        x = -screenWidth/2 + playerwidth/2;
    }
    else if (x > screenWidth/2 - playerwidth/2)
    {
        x = screenWidth/2 - playerwidth/2;
    }

    if (y < -screenHeight/2 + playerheight/2)
    {
        y = -screenHeight/2 + playerheight/2;
    }
    else if (y > screenHeight/2 - playerheight/2)
    {
        y = screenHeight/2 - playerheight/2;
    }
    // Move player to new coordinates
    this->setPos(x,y);

    // Detect any collisions
    QList<QGraphicsItem*> list = collidingItems();
    if(!list.isEmpty())
    {
        qDebug() << "Player detects collision";
    }
}

bool player::isFrog()
{
    return froggo;
}
