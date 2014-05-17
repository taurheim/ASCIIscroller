#include <iostream>
#include <winnt.h>
/*
Layers:
-player-
-enemies-
-objects-
-level-
-text_overlay-
  -game_gui-

*/
static char empty_layer[23][95] {
   "                                                                                             ",
   "                                                                                             ",
   "                                                                                             ",
   "                                                                                             ",
   "                                                                                             ",
   "                                                                                             ",
   "                                                                                             ",
   "                                                                                             ",
   "                                                                                             ",
   "                                                                                             ",
   "                                                                                             ",
   "                                                                                             ",
   "                                                                                             ",
   "                                                                                             ",
   "                                                                                             ",
   "                                                                                             ",
   "                                                                                             ",
   "                                                                                             ",
   "                                                                                             ",
   "                                                                                             ",
   "                                                                                             ",
   "                                                                                             "
};

char game_gui[34][101]{
"@--------------------------------------------------------------------------------------------------@",
"|                                                                                                  |",
"|                                                                                                  |",
"|                                                                                                  |",
"|                                                                                                  |",
"|                                                                                                  |",
"|                                                                                                  |",
"|                                                                                                  |",
"|                                                                                                  |",
"|                                                                                                  |",
"|                                                                                                  |",
"|                                                                                                  |",
"|                                                                                                  |",
"|                                                                                                  |",
"|                                                                                                  |",
"|                                                                                                  |",
"|                                                                                                  |",
"|                                                                                                  |",
"|                                                                                                  |",
"|                                                                                                  |",
"|                                                                                                  |",
"|                                                                                                  |",
"|                                                                                                  |",
"|                                                                                                  |",
"|                                                                                                  |",
"|               +++                                                                                |",
"|             +++++++                                                                              |",
"|            +++  +++++   ++++++++++++++++++++++++++++++++++++++++++++++++                         |",
"|    +++++   ++     ++++++                                                ++++++          +++++    |",
"|   ++ ++++     +++++                                                          +++++     ++++ ++   |",
"|      +++++  +++                                                                  +++  +++++      |",
"|      +++++++                                                                        +++++++      |",
"|++++++++++++                                                                          ++++++++++++|",
"@--------------------------------------------------------------------------------------------------@"

};

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

CONSOLE_SCREEN_BUFFER_INFO bufferInfo;


void drawGUI(){
    //SetConsoleTextAttribute(h, BACKGROUND_BLUE);
    for(int display=0;display<34;display++){
        std::cout << game_gui[display] << std::endl;
    };
}

void drawLayer(char layer[][95]){

    std::cout << layer[0][0];

    GetConsoleScreenBufferInfo(h, &bufferInfo);

    _COORD draw_anchor;
    draw_anchor.X = 4;
    draw_anchor.Y = 1;

    for(int d_y=0;d_y<22;d_y++){
        draw_anchor.Y++;
        draw_anchor.X = 4;
        for(int d_x=0;d_x<94;d_x++){
            draw_anchor.X++;
            if(layer[d_y][d_x] != ' ' && layer[d_y][d_x] != '-' && layer[d_y][d_x] != '\0'){
                SetConsoleCursorPosition(h,draw_anchor);
                std::cout << layer[d_y][d_x];
            }
        }
    }
}

class layers {
    public:
        char player[23][95];
        //char game_objects[23][95];
        char enemies[23][95];

        layers(){
            for(int i=0;i<23;i++){
                //strcpy(game_objects[i],empty_layer[i]);
                strcpy(player[i],empty_layer[i]);
                strcpy(enemies[i],empty_layer[i]);
            }
            /*
            enemies = empty_layer;
            objects = empty_layer;
            level = empty_layer;
            game_overlay = game_gui;*/
        }
};

void draw_all_layers(layers l){
    //drawLayer(l.game_objects);
    drawLayer(l.player);
    //drawLayer(l.enemies);
}
/*
    // This code makes the screen write itself over instead of refreshing


    _COORD draw_anchor;
    draw_anchor = currentlevel.level_anchor;
    //Draw level
    for(int display=0;display<15;display++){
        draw_anchor.Y+=1;
        SetConsoleCursorPosition(h,draw_anchor);
        std::cout << level_1[display] << std::endl;
    };


        SetConsoleCursorPosition(h,player.position);
        std::cout << '@';
*/
