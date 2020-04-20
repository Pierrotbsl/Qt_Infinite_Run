#include "widget.h"
#include "ui_widget.h"
#include <QGraphicsPixmapItem>
#include "playeritem.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);

    scene = new Scene(this);
    scene->setSceneRect(-250, -100, 500, 200);

    QGraphicsPixmapItem * pixItem = new QGraphicsPixmapItem(QPixmap(":/img/panorama.jpg"));
    scene->addItem(pixItem);
    pixItem->setPos(QPointF(0,0) - QPointF(pixItem->boundingRect().width()/2, pixItem->boundingRect().height()/2));
    scene->addLine(-750,0,750,0,QPen(Qt::blue));
    scene->addLine(-0,-315,0,315,QPen(Qt::blue));

    ui->graphicsView->setScene(scene);

    scene->addPlayer();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_startGameButton_clicked()
{
    scene->startGame();
}
