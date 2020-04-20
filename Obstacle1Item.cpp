#include "Obstacle1Item.h"
#include "PlayerItem.h"

Obstacle1Item::Obstacle1Item()
{

}

bool Obstacle1Item::collidesWithPlayer()
{
    QList<QGraphicsItem * > items = wood_up->collidingItems();
    items.append(wood_down->collidingItems());

    foreach (QGraphicsItem * item, items){
        PlayerItem * player = dynamic_cast<PlayerItem *>(item);
        if(player){
            return true;
        }
    }
    return false;
}
