#include "windows.h"
#include <string>

const int UP = 1;
const int RIGHT = 2;
const int DOWN = 3;
const int LEFT = 4;

class Entity {
    public:
        bool isDead;

        int type;
        _COORD position;
        bool uses_gravity;

        bool isMoving;
        bool isJumping;

        int jumpState;
        int jumpHeight;

        bool faceRight;
        int moveDir;

        int animation_frame;
        bool isAttacking;

        int shield_count;

        void tick();

        void move(_COORD pos) {
            position.X = pos.X;
            position.Y = pos.Y;
        }

        void draw(){

        }

        Entity(int t){
            type = t;
            jumpHeight = 4;
            isJumping = false;
            isMoving = false;
            faceRight = true;
            isDead = false;
            isAttacking = false;
            animation_frame = 0;
            shield_count = 0;
            switch(t){
                case 8:
                    {
                        uses_gravity=false;
                        isMoving=true;
                        moveDir= RIGHT;
                        break;
                    }
                case 21:
                case 22:
                    {
                        uses_gravity=false;
                        isMoving=true;
                        break;
                    }
                default:
                    {
                        uses_gravity = true;
                        break;
                    }

            }
        };
};
