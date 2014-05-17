#include "windows.h"
#include <string>

class Entity {
    public:
        int type;
        _COORD position;
        bool uses_gravity;

        bool isMoving;
        bool isJumping;

        int jumpState;
        int faceDir;
        int moveDir;


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
            if(t==8){
                uses_gravity = false;
            } else {
                uses_gravity = true;
            }
        };
};
