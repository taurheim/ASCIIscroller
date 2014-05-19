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
"|      +++++++           Gold:           Keys:              Bolts left:               +++++++      |",
"|++++++++++++                                                                          ++++++++++++|",
"@--------------------------------------------------------------------------------------------------@"

};


CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
const int SCREEN_HEIGHT = 23;
const int SCREEN_WIDTH = 95;
CHAR_INFO buffer[SCREEN_HEIGHT][SCREEN_WIDTH];
COORD dwBufferSize = { SCREEN_WIDTH, SCREEN_HEIGHT };
COORD dwBufferCoord = { 0, 0 };
SMALL_RECT rcRegion = { 3, 2, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1 };

void writeLevelName(std::string name){
    _COORD draw_anchor;
    draw_anchor.X = 35;
    draw_anchor.Y = 28;

    SetConsoleCursorPosition(h,draw_anchor);
    std::cout << name;
}

void updateGold(int gold){
    _COORD draw_anchor;
    draw_anchor.X = 30;
    draw_anchor.Y = 31;

    SetConsoleCursorPosition(h,draw_anchor);
    std::cout << gold;
}

void updateKeys(int keys){
    _COORD draw_anchor;
    draw_anchor.X = 46;
    draw_anchor.Y = 31;

    SetConsoleCursorPosition(h,draw_anchor);
    std::cout << keys;
}

void updateAttacks(int attacks){
    _COORD draw_anchor;
    draw_anchor.X = 71;
    draw_anchor.Y = 31;

    SetConsoleCursorPosition(h,draw_anchor);
    std::cout << attacks;
}

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

/*
    for(int d_y=0;d_y<22;d_y++){
        SetConsoleCursorPosition(h,draw_anchor);
        std::cout << layer[d_y] << std::endl;
        draw_anchor.Y++;
    }*/


    //Old draw function
    for(int d_y=0;d_y<22;d_y++){
        draw_anchor.X = 3;
        for(int d_x=0;d_x<94;d_x++){
            if(wipe || (layer[d_y][d_x] != ' ' && layer[d_y][d_x] != '-' && layer[d_y][d_x] != '\0')){
                switch(layer[d_y][d_x]){
                case ' ':
                    {
                        buffer[d_y][d_x].Attributes = 0x00;
                        break;
                    }
                case '#': //Wall
                    {
                        buffer[d_y][d_x].Attributes = 0x88;
                        break;
                    }
                case 'p': //Player
                case 'q':
                    {
                        buffer[d_y][d_x].Attributes = 0x0A;
                        break;
                    }
                case 'm': //Bat
                case '\\':
                case '-':
                case '/':
                    {
                        buffer[d_y][d_x].Attributes = 0x0C;
                        break;
                    }
                case '<': //Projectile
                case '>':
                    {
                        buffer[d_y][d_x].Attributes = 0x0E;
                        break;
                    }
                case '\'': //Shields
                case '"':
                case '*':
                    {
                        buffer[d_y][d_x].Attributes = 0x0F;
                        break;
                    }
                case 'O': //Mage
                    {
                        buffer[d_y][d_x].Attributes = 0x0B;
                        break;
                    }
                case 'i': //Staff
                    {
                        buffer[d_y][d_x].Attributes = 0x09;
                        break;
                    }
                case ')':
                case '(':
                    {
                        buffer[d_y][d_x].Attributes = 0x0B;
                        break;
                    }
                case ':':
                    {
                        buffer[d_y][d_x].Attributes = 0x07;
                        break;
                    }
                default:
                    {
                        buffer[d_y][d_x].Attributes = col;
                        break;
                    }


                }
                buffer[d_y][d_x].Char.AsciiChar = layer[d_y][d_x];
            }
            draw_anchor.X++;
        }
        draw_anchor.Y++;
    }
    WriteConsoleOutput( h, (CHAR_INFO *)buffer, dwBufferSize, dwBufferCoord, &rcRegion );
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
                    if(game_objects[d_y][d_x] != ' '){
                        compressed_layer[d_y][d_x] = game_objects[d_y][d_x];
                    }
                    if(level[d_y][d_x] != ' '){
                        compressed_layer[d_y][d_x] = level[d_y][d_x];
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
        if(!ent.isDead){
        switch(ent.type){
        case 8: //Slow moving bat
            {
                char *entity_char = &l_list.enemies[ent.position.Y][ent.position.X];
                *entity_char = 'm';
                char *leftwing = &l_list.game_objects[ent.position.Y][ent.position.X-1];
                char *rightwing = &l_list.game_objects[ent.position.Y][ent.position.X+1];
                if(ent.animation_frame%3 == 0){
                    *leftwing = '\\';
                    *rightwing = '/';
                } else if(ent.animation_frame%3 == 1){
                    *leftwing = '-';
                    *rightwing = '-';
                } else {
                    *leftwing = '/';
                    *rightwing = '\\';
                }
                break;
            }
        case 25: //Player
            {
                char *entity_char = &l_list.player[ent.position.Y][ent.position.X];
                if(ent.faceRight){
                    *entity_char = 'p';
                } else {
                    *entity_char = 'q';
                }
                if(ent.shield_count == 1){
                    char *leftshield = &l_list.game_objects[ent.position.Y][ent.position.X-1];
                    char *rightshield = &l_list.game_objects[ent.position.Y][ent.position.X+1];
                    *leftshield = '\'';
                    *rightshield = '\'';
                } else if(ent.shield_count == 2){
                    char *leftshield = &l_list.game_objects[ent.position.Y][ent.position.X-1];
                    char *rightshield = &l_list.game_objects[ent.position.Y][ent.position.X+1];
                    *leftshield = '"';
                    *rightshield = '"';
                } else if(ent.shield_count == 3){
                    char *leftshield = &l_list.game_objects[ent.position.Y][ent.position.X-1];
                    char *rightshield = &l_list.game_objects[ent.position.Y][ent.position.X+1];
                    *leftshield = '*';
                    *rightshield = '*';
                }
                break;
            }
        case 21: //Projectile
            {
                char *entity_char = &l_list.game_objects[ent.position.Y][ent.position.X];
                if(ent.faceRight){
                    *entity_char = '>';
                } else {
                    *entity_char = '<';
                }
                break;
            }
        case 22: //Water attack
            {
                char *entity_char = &l_list.game_objects[ent.position.Y][ent.position.X];
                if(ent.faceRight){
                    *entity_char = ')';
                } else {
                    *entity_char = '(';
                }
                if(ent.faceRight){
                    char *tail1 = &l_list.game_objects[ent.position.Y][ent.position.X-1];
                    char *tail2 = &l_list.game_objects[ent.position.Y][ent.position.X-2];
                    *tail1 = ':';
                    *tail2 = ':';
                } else {
                    char *tail1 = &l_list.game_objects[ent.position.Y][ent.position.X+1];
                    char *tail2 = &l_list.game_objects[ent.position.Y][ent.position.X+2];
                    *tail1 = ':';
                    *tail2 = ':';
                }
                break;
            }
        case 3: //Level 1 Mage
            {
                char *entity_char = &l_list.enemies[ent.position.Y][ent.position.X];
                *entity_char = 'O';
                if(ent.faceRight){
                    char *staff = &l_list.game_objects[ent.position.Y][ent.position.X+1];
                    *staff = 'i';
                } else {
                    char *staff = &l_list.game_objects[ent.position.Y][ent.position.X-1];
                    *staff = 'i';
                }
                break;
            }
        default:
            //Do nothing
            break;
        }
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
