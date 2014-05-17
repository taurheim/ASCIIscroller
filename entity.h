#include "windows.h"
#include <string>

class Entity {
    public:
        std::string type;
        _COORD position;
        bool isMoving;
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

        Entity(std::string t){
            type = t;
        };
};
