#ifndef CRUMB_H
#define CRUMB_H

#include <QGraphicsObject>
#include <QGraphicsScene>
#include <QPainter>
#include <QBrush>
#include <QPen>
#include <QtDebug>

class crumb : public QGraphicsObject

{

    Q_OBJECT

public:

    crumb(QGraphicsItem* parent = nullptr);
    ~crumb() override;

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
    void advance(int phase) override;

private:

    QPixmap image;


signals:

    void ate();

};

#endif // CRUMB_H
