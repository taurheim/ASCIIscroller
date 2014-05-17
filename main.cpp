#include "windows.h"
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
#include "entity.h"
#include "level.h"
#include <string>
#include "gfx.h"
#include <vector>
#include "physics.h"


static int UP = 1;
static int RIGHT = 2;
static int DOWN = 3;
static int LEFT = 4;

std::vector<Entity> all_entities;


bool isEmpty(_COORD pos){
    if(level_1[pos.Y+2][pos.X+2] == ' '){
        return true;
    } else {
        return false;
    }
}


bool isRunning = true;

int main() {


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
    all_entities = currentlevel.getEntities();

    //Initialize Player
    Entity player(25); //Create the entity (25 is player type)
    player.position.X = currentlevel.spawn.X; //Set player's position to the spawn
    player.position.Y = currentlevel.spawn.Y;
    all_entities.push_back (player); //Put player in our entity vector

    //This object holds all of our gfx layers
    layers all_layers;

    //Put level mesh into a layer
    all_layers.load_level(currentlevel.level_mesh);

    //Game loop
    while(isRunning){
        //Check for inputs (BROKEN)
        //if(GetAsyncKeyState(VK_LEFT)){
        //    std::cout << "Rah";
        //}

        //Run physics (for now, just move everything down)
        for(Entity& ent : all_entities){
            runPhysics(ent,currentlevel.level_mesh);
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

