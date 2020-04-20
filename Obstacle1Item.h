#ifndef OBSTACLE1ITEM_H
#define OBSTACLE1ITEM_H
#include <QObject>
#include <QGraphicsItemGroup>
#include <QPropertyAnimation>


class Obstacle1Item :public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX)
public:
    Obstacle1Item();
    ~Obstacle1Item();
    qreal x() const;
    void freezeInPace();

signals :
    void collideFail();


public slots:
    void setX(qreal x);

private :
    bool collidesWithPlayer();
    QGraphicsPixmapItem * wood_up;
    QGraphicsPixmapItem * wood_down;
    QPropertyAnimation * xAnimation;
    qreal m_x;
    qreal ypos;
    bool pastPlayer;
};

#endif // OBSTACLE1ITEM_H
