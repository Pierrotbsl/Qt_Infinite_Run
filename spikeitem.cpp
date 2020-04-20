#include "spikeitem.h"
#include "playeritem.h"
#include "scene.h"
#include <QGraphicsScene>
#include <QRandomGenerator>
#include <QDebug>

SpikeItem::SpikeItem() :
//    wood_floor(new QGraphicsPixmapItem(QPixmap(":/img/spike3.png"))),
    wood_up(new QGraphicsPixmapItem(QPixmap(":/img/spike2.png"))),
    pastPlayer(false)
{
//    wood_floor->setPos(QPointF(900,150) + QPointF(-wood_floor->boundingRect().width()/2, 60));
    wood_up->setPos(QPointF(800,300) - QPointF(wood_up->boundingRect().width()/10, wood_up->boundingRect().height() -20));

//    addToGroup(wood_floor);
    addToGroup(wood_up);

    int xRandomizer = QRandomGenerator::global()->bounded(800);

    setPos(QPoint(0,0) + QPoint(0/* + xRandomizer*/,0));

    xAnimation = new QPropertyAnimation(this, "x", this);
    xAnimation->setStartValue(0/* + xRandomizer*/);
    xAnimation->setEndValue(-2000);
    xAnimation->setEasingCurve(QEasingCurve::Linear);
    xAnimation->setDuration(4000);

    connect(xAnimation, &QPropertyAnimation::finished,[=](){
        qDebug() << "Animation finished" ;
        scene()->removeItem(this);
        delete this;
    });

    xAnimation->start();
}

SpikeItem::~SpikeItem()
{
    qDebug() << "Deleting Spikes";
    delete wood_up;
//    delete wood_floor;
}

qreal SpikeItem::x() const
{
    return m_x;
}

void SpikeItem::freezeInPlace()
{
    xAnimation->stop();
}

void SpikeItem::setX(qreal x)
{
//    qDebug() << "Spike position :" << x;
    m_x = x;

    if(x < 0 && !pastPlayer){
        pastPlayer = true;
        QGraphicsScene * mScene = scene();
        Scene * myScene = dynamic_cast<Scene *>(mScene);
        if(myScene){
            myScene->incrementScore();
        }
    }
    if (collidesWithPlayer()){
        emit collideFail();
    }
    setPos(QPointF(0,0) + QPointF(x, 0));
}

bool SpikeItem::collidesWithPlayer()
{
    QList<QGraphicsItem * > collidingItems = wood_up->collidingItems();
//    collidingItems.append(wood_floor->collidingItems());

    foreach (QGraphicsItem * item, collidingItems){
        PlayerItem * playerItem = dynamic_cast<PlayerItem*>(item);
        if(playerItem){
            return true;
        }
    }
    return false;
}

