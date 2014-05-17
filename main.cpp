#include "windows.h"
#include "entity.h"
#include "level.h"
#include <string>
#include "gfx.h"
#include <vector>


static int UP = 1;
static int RIGHT = 2;
static int DOWN = 3;
static int LEFT = 4;

std::vector<Entity> entities;


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

    //Draw the GUI
    drawGUI();



    //Load level 1
    Level currentlevel;
    currentlevel.spawn.X = 5;
    currentlevel.spawn.Y = 5;

    //Get things on screen
    entities = currentlevel.getEntities();

    //Initialize Player
    Entity player("player");
    entities.push_back (player);

    layers all_layers;

    char *player_char = &all_layers.player[5][10];
    *player_char = 'P';

    char *enemy_char = &all_layers.enemies[5][10];
    *enemy_char = 'Q';

    draw_all_layers(all_layers);


    //Game loop
    while(isRunning){
        //Check for inputs

        /*if(GetAsyncKeyState(VK_UP)){
            _COORD above;
            above.X = player.position.X;
            above.Y = player.position.Y;
            if(isEmpty(above)){
                player.move(above);
            }
        }

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


        // Check for collisions

        // Draw current states





        Sleep(30);
    };

    return 0;
}

