#include "scene.h"
#include <QKeyEvent>
#include <QDebug>

Scene::Scene(QObject *parent) : QGraphicsScene(parent), gameOn(false), score(-1), bestScore(0)
{
    setUpSpikeTimer();
}

void Scene::addPlayer()
{
    player = new PlayerItem(QPixmap(":/img/perso_up.png"));
    addItem(player);
}

void Scene::startGame()
{
    //Player
    player->startRunning();
    //Spikes
    if(!spikeTimer->isActive()){
        cleanSpikes();
        setGameOn(true);
        setScore(0);
        hideGameOverGraphics();
        spikeTimer->start(1000);
    }
}

void Scene::setUpSpikeTimer()
{
    spikeTimer = new QTimer(this);
    connect(spikeTimer,&QTimer::timeout,[=](){

        SpikeItem * spikeItem = new SpikeItem();
        connect(spikeItem,&SpikeItem::collideFail,[=](){
            spikeTimer->stop();
            freezePlayerAndSpikesInPlace();
            setGameOn(false);
            showGameOverGraphics();
        });
        addItem(spikeItem);
    });
//    spikeTimer->start(1000);
}

void Scene::freezePlayerAndSpikesInPlace()
{
    //Freeze player
    player->freezeInPlace();

    //Freeze spikes
    QList<QGraphicsItem *> sceneItems = items();
    foreach (QGraphicsItem *item, sceneItems) {
        SpikeItem * spike = dynamic_cast<SpikeItem *>(item);
        if(spike){
            spike->freezeInPlace();
        }
    }
}

void Scene::setScore(int value)
{
    score = value;
}

bool Scene::getGameOn() const
{
    return gameOn;
}

void Scene::setGameOn(bool value)
{
    gameOn = value;
}

void Scene::incrementScore()
{
    score++;
    if(score > bestScore){
        bestScore = score;
    }
    qDebug() << "Score : " << score << "Best Score : " << bestScore;
}

void Scene::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Up){
//        if(gameOn){
            player->shootUp();
//        }
    }
    if(event->key() == Qt::Key_Left){
        if(gameOn){
            player->moveLeftSide();
        }
    }
    if(event->key() == Qt::Key_Right){
        if(gameOn){
            player->moveRightSide();
        }
    }
    QGraphicsScene::keyPressEvent(event);
}

void Scene::showGameOverGraphics()
{
    gameOverPix = new QGraphicsPixmapItem(QPixmap(":/img/game_over.png"));
    addItem(gameOverPix);
    gameOverPix->setPos(QPointF(0,0) - QPointF(gameOverPix->boundingRect().width()/2,
                                               gameOverPix->boundingRect().height()/2));
    scoreTextItem = new QGraphicsTextItem();

    QString htmlString = "<p> Score : " + QString::number(score) + "</p>"
            + "<p> Best Score : " + QString::number(bestScore) + "</p>";
    QFont mFont("Consolas", 30, QFont::Bold);

    scoreTextItem->setHtml(htmlString);
    scoreTextItem->setFont(mFont);
    scoreTextItem->setDefaultTextColor(Qt::red);
    addItem(scoreTextItem);

    scoreTextItem->setPos(QPointF(0,0) - QPointF(scoreTextItem->boundingRect().width()/2,
                                                 -gameOverPix->boundingRect().height()/2));
}

void Scene::hideGameOverGraphics()
{
    if(gameOverPix){
        removeItem(scoreTextItem);
        delete gameOverPix;
        gameOverPix = nullptr;
    }
    if(scoreTextItem){
        removeItem(scoreTextItem);
        delete scoreTextItem;
        scoreTextItem = nullptr;
    }
}

void Scene::cleanSpikes()
{
    QList<QGraphicsItem *> sceneItems = items();
    foreach (QGraphicsItem *item, sceneItems){
        SpikeItem * spike = dynamic_cast<SpikeItem *>(item);
        if(spike){
            removeItem(spike);
            delete spike;
        }
    }
}
