#ifndef PLAYERITEM_H
#define PLAYERITEM_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>

class PlayerItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(qreal rotation READ rotation WRITE setRotation)
    Q_PROPERTY(qreal y READ y WRITE setY)
public:
    explicit PlayerItem(QPixmap pixmap);
    qreal x() const;
    qreal y() const;
    void shootUp();
    void moveLeftSide();
    void moveRightSide();
    void startRunning();
    void freezeInPlace();

signals:

public slots:

    void setX(qreal x);
    void setY(qreal y);
    void fallToGroundIfNecessary();
    
private:
    enum LegsPosition{
        Up,
        Middle,
        Down
    };
    void updatePixmap();

    LegsPosition legsPosition;
    bool legsDirection ; // 0:down, 1:up
    qreal m_x;
    qreal m_y;
    QPropertyAnimation * xAnimation;
    QPropertyAnimation * yAnimation;
    qreal groundPosition;
    qreal startingPosition;
};

#endif // PLAYERITEM_H
