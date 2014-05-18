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


        int shield_count;

        std::string ai_type;

        std::string current_action;
        std::string current_frame;

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
            animation_frame = 0;
            switch(t){
                case 8:
                    {
                        uses_gravity=false;
                        isMoving=true;
                        moveDir= RIGHT;
                        break;
                    }
                case 21:
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
