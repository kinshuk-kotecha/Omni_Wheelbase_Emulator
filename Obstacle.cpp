#include "Obstacle.h"


Obstacle::Obstacle(float size_x, float size_y, float pos_x, float pos_y) {
    setRect(0,0,size_x,size_y);
    setPos(pos_x,pos_y);
}
