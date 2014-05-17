#include <vector>
#include <iostream>

const int UP = 1;
const int RIGHT = 2;
const int DOWN = 3;
const int LEFT = 4;

void runPhysics(Entity& ent, char mesh[][95]){
    SHORT *posx = &ent.position.X;
    SHORT *posy = &ent.position.Y;

    if(ent.isJumping && mesh[*posy+1][*posx] != ' '){
        *posy = *posy-3;
    }

    if(ent.uses_gravity) {
        if(mesh[*posy+1][*posx] == ' '){
            *posy = *posy + 1;
        } else {
            ent.isJumping = false;
        }
    }

    if(ent.isMoving){
        if(ent.moveDir==LEFT && mesh[*posy][*posx-1] == ' '){
            *posx = *posx-1;
        } else if(ent.moveDir==RIGHT && mesh[*posy][*posx+1] == ' '){
            *posx = *posx+1;
        }
    }


    //std::cout << "(" << *posx << "," << *posy << ")";
}
