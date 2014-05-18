#include <vector>
#include <iostream>

void runPhysics(Entity& ent, char mesh[][95]){
    SHORT *posx = &ent.position.X;
    SHORT *posy = &ent.position.Y;
    bool *jumping = &ent.isJumping;
    int *jumpState = &ent.jumpState;
    bool *faceRight = &ent.faceRight;
    int *moveDir = &ent.moveDir;


    if(ent.isJumping && mesh[*posy-1][*posx] == ' '){
        *jumpState = *jumpState + 1;
        if(ent.jumpState < ent.jumpHeight){
            *posy = *posy-2;
        } else {
            *jumping = false;
        }
    } else if(ent.isJumping){
        *jumping = false;
    }

    if(ent.uses_gravity) {
        if(mesh[*posy+1][*posx] == ' '){
            *posy = *posy + 1;
        } else {
            *jumping = false;
            *jumpState = 0;
        }
    }

    if(ent.isMoving){
        if(ent.moveDir==LEFT && mesh[*posy][*posx-1] == ' '){
            *posx = *posx-1;
            *faceRight = false;
        } else if(ent.moveDir==RIGHT && mesh[*posy][*posx+1] == ' '){
            *posx = *posx+1;
            *faceRight = true;
        } else if(ent.type == 8){
            if(*faceRight){
                *moveDir = LEFT;
            } else {
                *moveDir = RIGHT;
            }
        }
    }


    //std::cout << "(" << *posx << "," << *posy << ")";
}
