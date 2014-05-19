#include <vector>
#include <iostream>

void runPhysics(Entity& ent, char mesh[][95]){
    SHORT *posx = &ent.position.X;
    SHORT *posy = &ent.position.Y;
    bool *jumping = &ent.isJumping;
    int *jumpState = &ent.jumpState;
    bool *faceRight = &ent.faceRight;
    int *moveDir = &ent.moveDir;
    bool *isDead = &ent.isDead;


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
        if(ent.moveDir==LEFT && mesh[*posy][*posx-1] != '#'){
            *posx = *posx-1;
            *faceRight = false;
        } else if(ent.moveDir==RIGHT && mesh[*posy][*posx+1] != '#'){
            *posx = *posx+1;
            *faceRight = true;
        } else if(ent.type == 8){
            if(*faceRight){
                *moveDir = LEFT;
            } else {
                *moveDir = RIGHT;
            }
        } else if(ent.type == 21 || ent.type == 22){
            //Projectile is hitting a wall
            *isDead = true;
        }
    }


    //std::cout << "(" << *posx << "," << *posy << ")";
}

class gameState {
public:
    std::vector<_COORD> enemy_positions;
    std::vector<_COORD> projectile_positions;
    _COORD player;


    void wipe_gamestate(){
        enemy_positions.clear();
        projectile_positions.clear();
    }

    void add_enemy(_COORD enemy) {
        enemy_positions.push_back(enemy);
    }

    void add_projectile(_COORD projectile){
        projectile_positions.push_back(projectile);
    }

    void update_player(_COORD p){
        player = p;
    }
};
