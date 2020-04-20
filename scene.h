#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QTimer>
#include "spikeitem.h"
#include "playeritem.h"

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = nullptr);

    void addPlayer();

    void startGame();

    bool getGameOn() const;
    void setGameOn(bool value);

    void incrementScore();

    void setScore(int value);

signals:

public slots:

    // QGraphicsScene interface
protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    void showGameOverGraphics();
    void hideGameOverGraphics();
    void cleanSpikes();
    void setUpSpikeTimer();
    void freezePlayerAndSpikesInPlace();

    QTimer * spikeTimer;
    PlayerItem * player;
    bool gameOn;
    int score;
    int bestScore;

    QGraphicsPixmapItem * gameOverPix;
    QGraphicsTextItem * scoreTextItem;

};

#endif // SCENE_H
