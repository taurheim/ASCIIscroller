#include "windows.h"
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
#include "entity.h"
#include "level.h"
#include <string>
#include "gfx.h"
#include <vector>
#include "physics.h"
#include "ai.h"




std::vector<Entity> all_entities;


bool isEmpty(_COORD pos){
    if(level_1[pos.Y+2][pos.X+2] == ' '){
        return true;
    } else {
        return false;
    }
}



int main() {
    //Game loop setup
    const int TICKS_PER_SECOND = 20;
    const int SKIP_TICKS = 1000/ TICKS_PER_SECOND;
    const int MAX_FRAMESKIP = 5;
    DWORD next_game_tick = GetTickCount();
    int loops;
    float interpolation;
    bool isRunning = true;

    //Initialize the game:
    //  - Set up window
    //  - Draw the GUI
    //  - Load level 1
    //  - Initialize Player
    //     - Move player to spawn


    //Set up Window
    _COORD coord;
    coord.X = 101;
    coord.Y = 37;
    _SMALL_RECT Rect;
    Rect.Top = 0;
    Rect.Left = 0;
    Rect.Bottom = 37 - 1;
    Rect.Right = 101 - 1;
    SetConsoleScreenBufferSize(h, coord);            // Set Buffer Size
    SetConsoleWindowInfo(h, TRUE, &Rect);            // Set Window Size

    //Hide cursor

    CONSOLE_CURSOR_INFO ConCurInf;
    ConCurInf.dwSize = 10;
    ConCurInf.bVisible = FALSE;
    SetConsoleCursorInfo(h, &ConCurInf);

    //Draw the GUI
    drawGUI();

    //Load level 1
    Level currentlevel;

    //Get things on screen
    currentlevel.pushEntitiesTo(all_entities);

    //Initialize Player
    Entity player(25); //Create the entity (25 is player type)
    player.position.X = currentlevel.spawn.X; //Set player's position to the spawn
    player.position.Y = currentlevel.spawn.Y;
    player.shield_count = 1;
    all_entities.push_back (player); //Put player in our entity vector

    //This object holds all of our gfx layers
    layers all_layers;

    //Put level mesh into a layer
    all_layers.load_level(currentlevel.level_mesh);

    while(isRunning){
        loops = 0;
        while(GetTickCount() > next_game_tick && loops < MAX_FRAMESKIP){
            for(Entity& ent : all_entities){
                if(!ent.isDead){
                runPhysics(ent,currentlevel.level_mesh);
                run_ai(ent);
                if(ent.type == 8){
                } else if(ent.type == 21){
                }
                 else if(ent.type == 25){ //Player Input Handling
                    ent.isMoving = false;
                    if(GetAsyncKeyState(VK_LEFT)){
                        ent.isMoving = true;
                        ent.moveDir = LEFT;
                    }
                    if(GetAsyncKeyState(VK_RIGHT)){
                        ent.isMoving = true;
                        ent.moveDir = RIGHT;
                    }
                    if(GetAsyncKeyState(VK_UP) && !ent.isJumping && ent.jumpState==0){
                        ent.isJumping = true;
                        ent.jumpState = 0;
                    }
                    if(GetAsyncKeyState(VK_SPACE)){
                        Entity projectile(21);
                        projectile.faceRight = ent.faceRight;
                        if(ent.faceRight){
                            projectile.moveDir = RIGHT;
                            projectile.position.X = ent.position.X+1;
                        } else {
                            projectile.moveDir = LEFT;
                            projectile.position.X = ent.position.X-1;
                        }
                        projectile.position.Y = ent.position.Y;
                        all_entities.push_back(projectile);
                    }
                }
                }
            }

            //Now that we've updated the movement of all entities, do a collision check.
            for(Entity& proj : all_entities){
                if((proj.type==21 || proj.type==25 )&& !proj.isDead){
                    //Projectile, check against all other entities for collisions
                    for(Entity& ent : all_entities){
                        if(!ent.isDead && ent.type==8 && (ent.position.X == proj.position.X || (ent.position.X == proj.position.X-1 && proj.faceRight) || (ent.position.X == proj.position.X+1 && !proj.faceRight)) && ent.position.Y == proj.position.Y){
                            //std::cout << "Collision" << rand();
                            ent.isDead = true;
                            proj.isDead = true;
                        }
                    }
                }
            }

            next_game_tick += SKIP_TICKS;
            loops++;
        }


        //The following three functions will:
        // 1. Empty our 3 layers (player, enemies, objects)
        // 2. Draw all of our entities on to their respective layers
        // 3. Compress all 3 of the layers (+level layer) into one layer
        all_layers.wipe_layers();
        parseGFX(all_entities,all_layers);
        all_layers.compress_layers();


        //Draw our compressed layer
        drawLayer(all_layers.compressed_layer, 0x0B,true);


/*
        if(GetAsyncKeyState(VK_LEFT)){
            _COORD left;
            left.X = player.position.X-1;
            left.Y = player.position.Y;
            if(isEmpty(left)){
                player.move(left);
            }
        }

        if(GetAsyncKeyState(VK_RIGHT)){
            _COORD right;
            right.X = player.position.X+1;
            right.Y = player.position.Y;
            if(isEmpty(right)){
                player.move(right);
            }
        }*/


    };
    return 0;
}

