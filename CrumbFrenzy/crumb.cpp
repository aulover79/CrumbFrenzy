#include <crumb.h>
#include <config.h>
#include <QGraphicsPixmapItem>
#include <player.h>

crumb::crumb(QGraphicsItem* parent) : QGraphicsObject(parent)
{
    image = QPixmap(":/images/crumbicon");
}

crumb::~crumb()
{

}

QRectF crumb::boundingRect() const
{

    return QRectF(-crumbswidth/2, -crumbsheight/2, crumbswidth, crumbsheight);

}

QPainterPath crumb::shape() const
{
    QPainterPath path;
    path.addEllipse(-crumbswidth/2, -crumbsheight/2, crumbswidth, crumbsheight);
    return path;

}

void crumb::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    painter->drawPixmap(-crumbswidth/2, -crumbsheight/2, image);
}

void crumb::advance(int phase)
{

    if (phase == 0)
    {
        return;
    }

    // If crumb is interacted with, emit signal and remove from scene
    QList<QGraphicsItem*> list = collidingItems();
    if (!list.isEmpty())
    {
        foreach (QGraphicsItem* i, list)
        {

            player* ignoreEverything= dynamic_cast<player * >(i);

            if (ignoreEverything)
            {
                // Emit collide signal
                emit ate();

                // Remove item from scene
                this->scene()->removeItem(this);

                // Deallocate memory
                this->deleteLater();
            }
        }
    }
}
