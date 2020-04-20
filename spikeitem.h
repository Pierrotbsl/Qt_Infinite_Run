#ifndef SPIKEITEM_H
#define SPIKEITEM_H
#include <QObject>
#include <QGraphicsItemGroup>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>


class SpikeItem : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX)
public:
    explicit SpikeItem();
    ~SpikeItem();

    qreal x() const;
    void freezeInPlace();

signals :
    void collideFail();

public slots:
    void setX(qreal x);

private :
    bool collidesWithPlayer();

    QGraphicsPixmapItem * wood_floor;
    QGraphicsPixmapItem * wood_up;
    QPropertyAnimation * xAnimation;
    int yPos;
    qreal m_x;
    bool pastPlayer;
};
#endif // SPIKEITEM_H
