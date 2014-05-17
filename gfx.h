#include <iostream>
#include <winnt.h>
#include <string>
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


CONSOLE_SCREEN_BUFFER_INFO bufferInfo;


void drawGUI(){
    //SetConsoleTextAttribute(h,0x70);
    for(int display=0;display<34;display++){
        std::cout << game_gui[display] << std::endl;
    };
}

void drawLayer(char layer[][95], WORD col,bool wipe){

    GetConsoleScreenBufferInfo(h, &bufferInfo);


    _COORD draw_anchor;
    draw_anchor.X = 3;
    draw_anchor.Y = 2;
    //New Draw function

    //USE THIS: http://www.tomshardware.com/forum/65918-13-technique-fast-win32-console-drawing

    for(int d_y=0;d_y<22;d_y++){
        SetConsoleCursorPosition(h,draw_anchor);
        std::cout << layer[d_y] << std::endl;
        draw_anchor.Y++;
    }

    /*Old draw function
    for(int d_y=0;d_y<22;d_y++){
        draw_anchor.X = 3;
        for(int d_x=0;d_x<94;d_x++){
            if(wipe || (layer[d_y][d_x] != ' ' && layer[d_y][d_x] != '-' && layer[d_y][d_x] != '\0')){
                switch(layer[d_y][d_x]){
                case ' ':
                    {
                        SetConsoleTextAttribute(h,0x00);
                        break;
                    }
                case '#':
                    {
                        SetConsoleTextAttribute(h,0x88);
                        break;
                    }
                default:
                    {
                        SetConsoleTextAttribute(h,col);
                        break;
                    }


                }
                SetConsoleCursorPosition(h,draw_anchor);
                std::cout << layer[d_y][d_x];
            }
            draw_anchor.X++;
        }
        draw_anchor.Y++;
    }
    */

    SetConsoleTextAttribute(h, 0x0A);
}
class layers {
    public:
        char compressed_layer[24][95];
        char player[24][95];
        char game_objects[24][95];
        char enemies[24][95];
        char level[24][95];

        layers(){
            wipe_layers();
            /*
            enemies = empty_layer;
            objects = empty_layer;
            level = empty_layer;
            game_overlay = game_gui;*/
        }

        void load_level(char lay[][95]){
            for(int i=0;i<24;i++){
                strcpy(level[i],lay[i]);
            }
        }
        void wipe_layers(){
            for(int i=0;i<24;i++){
                strcpy(game_objects[i],empty_layer[i]);
                strcpy(player[i],empty_layer[i]);
                strcpy(enemies[i],empty_layer[i]);
            }
        }
        void compress_layers(){
            for(int d_y=0;d_y<24;d_y++){
                for(int d_x=0;d_x<94;d_x++){
                    compressed_layer[d_y][d_x] = ' ';
                    if(level[d_y][d_x] != ' '){
                        compressed_layer[d_y][d_x] = level[d_y][d_x];
                    }
                    if(game_objects[d_y][d_x] != ' '){
                        compressed_layer[d_y][d_x] = game_objects[d_y][d_x];
                    }
                    if(enemies[d_y][d_x] != ' '){
                        compressed_layer[d_y][d_x] = enemies[d_y][d_x];
                    }
                    if(player[d_y][d_x] != ' '){
                        compressed_layer[d_y][d_x] = player[d_y][d_x];
                    }
                }
            }
        }
};

void draw_all_layers(layers l){
    drawLayer(l.game_objects, 0x0E, false);
    drawLayer(l.enemies, 0x04, false);
    drawLayer(l.player, 0x0F, false);
    //std::cout << l.player[11][22] << "<";
}

void parseGFX(std::vector<Entity> e_list, layers& l_list) {
    for(Entity ent : e_list){
        switch(ent.type){
        case 8: //Slow moving bat
            {
                char *entity_char = &l_list.enemies[ent.position.Y][ent.position.X];
                *entity_char = 'm';
                break;
            }
        case 25: //Player
            {
                char *entity_char = &l_list.player[ent.position.Y][ent.position.X];
                *entity_char = 'p';
                break;
            }
        default:
            //Do nothing
            break;
        }
    };
};
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
