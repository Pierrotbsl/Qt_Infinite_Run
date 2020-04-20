#include "playeritem.h"
#include <QObject>
#include <QTimer>
#include <QGraphicsScene>

PlayerItem::PlayerItem(QPixmap pixmap) :
    legsPosition(LegsPosition::Up),
    legsDirection(0)
{
    setPixmap(pixmap);

    QTimer * playerLegsTimer = new QTimer(this);
    connect(playerLegsTimer, &QTimer::timeout,[=](){
        updatePixmap();
    });

    playerLegsTimer->start(80);

    startingPosition = scenePos().x();
    groundPosition = scenePos().y()+145;

    xAnimation = new QPropertyAnimation(this, "x", this);
    setX(startingPosition);

    yAnimation = new QPropertyAnimation(this, "y", this);
    yAnimation->setStartValue(scenePos().y()+100);
    yAnimation->setEndValue(groundPosition);
    yAnimation->setEasingCurve(QEasingCurve::InQuad);
    yAnimation->setDuration(500);

//    yAnimation->start();

}

qreal PlayerItem::x() const
{
    return m_x;
}

qreal PlayerItem::y() const
{
    return m_y;
}

void PlayerItem::shootUp()
{
    yAnimation->stop();

    qreal curPosY = y();

    yAnimation->setStartValue(curPosY);
    yAnimation->setEndValue(curPosY - scene()->sceneRect().height()/2);
    yAnimation->setEasingCurve(QEasingCurve::InQuad);
    yAnimation->setDuration(200);

    connect(yAnimation, &QPropertyAnimation::finished, [=](){
        fallToGroundIfNecessary();
    });

    yAnimation->start();
}

void PlayerItem::moveLeftSide()
{
    xAnimation->stop();

    setPos(QPoint(0,0) + QPoint(0,0));

    xAnimation = new QPropertyAnimation(this, "x", this);
    xAnimation->setStartValue(scenePos().x());
    xAnimation->setEndValue(-200);
    xAnimation->setEasingCurve(QEasingCurve::Linear);
    xAnimation->setDuration(200);

    xAnimation->start();
}

void PlayerItem::moveRightSide()
{

}

void PlayerItem::startRunning()
{
    yAnimation->start();
}

void PlayerItem::freezeInPlace()
{
    yAnimation->stop();
}

void PlayerItem::setX(qreal x)
{
    moveBy(x-m_x,0);
    m_x = x;
}

void PlayerItem::setY(qreal y)
{
    moveBy(0,y-m_y);
    m_y = y;
}

void PlayerItem::fallToGroundIfNecessary()
{
    if( y() < groundPosition){
        yAnimation->stop();

        yAnimation->setStartValue(y());
        yAnimation->setEasingCurve(QEasingCurve::InQuad);
        yAnimation->setEndValue(groundPosition);
        yAnimation->setDuration(400);

        yAnimation->start();
    }
}

void PlayerItem::updatePixmap()
{
    if(legsPosition == LegsPosition::Middle){
        if(legsDirection){
            //Up
            setPixmap(QPixmap(":/img/perso_up.png"));
            legsPosition = LegsPosition::Up;
            legsDirection = 0;
        }else {
            //Down
            //Up
            setPixmap(QPixmap(":/img/perso_down.png"));
            legsPosition = LegsPosition::Down;
            legsDirection = 1;
        }
    }else{
        setPixmap(QPixmap(":/img/perso_run.png"));
        legsPosition = LegsPosition::Middle;
    }
}
