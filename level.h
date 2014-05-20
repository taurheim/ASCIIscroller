#include "windows.h"
#include <vector>
#include <iostream>
#include <sstream>


char level_1[23][95] = {
"                  ########################################################                  ",
"                  #     @                               m          3     #                  ",
"                  #     #               #########                        #                  ",
"                  #                #            #                        #                  ",
"                  #        #####                #                        #                  ",
"                  #                 #####       #                        #                  ",
"                  #                      ##     #                        #                  ",
"                  #           m            #    #                        #                  ",
"                  #                                   3                  #                  ",
"                  #                  ####################     #######    #                  ",
"                  #                     #               #                #                  ",
"                  #        ######       #               #              ###                  ",
"                  #######################               #                #                  ",
"                                                        #           ##   #                  ",
"                                                        #                #                  ",
"                                                        #         #      #                  ",
"                          ##  ##                        ##################                  ",
"                          ##  ##                        ##################                  ",
"                                                        ##################                  ",
"                          #     #                       ##################                  ",
"                           #####                        ######### ########                  ",
"                                                        ########  ########                  ",
"                                                        #######    #######                  "
};

class Level {
    public:
        _COORD level_anchor;
        _COORD spawn;
        char level_mesh[23][95];
        int shields;
        int bolts;
        int enemy_count = 0;

        void pushEntitiesTo(std::vector<Entity> & dest){
            /*
            for(int bk=0;bk<23;bk++){
            std::cout << level_mesh[bk] << std::endl;
            }
            Sleep(10000);*/

            _COORD cmd_pointer;
            cmd_pointer.X = 0;
            cmd_pointer.Y = 0;


            for(int d_y=0;d_y<21;d_y++){
                cmd_pointer.X = 0;
                for(int d_x=0;d_x<92;d_x++){
/*
                    int entity_type;
                    char *entity_char = &level_mesh[d_y][d_x];

                    if(level_mesh[d_y][d_x] == '@'){
                        std::cout<< "Player!";
                    } else if (level_mesh[d_y][d_x] == 'h'){
                        std::cout << "Level 1 bat found at " << d_x << "," << d_y << std::endl;
                        entity_type = 8;
                        Entity new_entity(entity_type);
                        entity_list.push_back (new_entity);
                        //entity_char = ' ';
                    }*/

                    if(level_mesh[d_y][d_x]!= '#' && level_mesh[d_y][d_x]!= ' ' && level_mesh[d_y][d_x]!='\0'){

                        //Point to where that char is located
                        char *entity_char = &level_mesh[d_y][d_x];
                        int entity_type;

                        //We've found an entity -> Create it!
                        switch(level_mesh[d_y][d_x]){
                            case '@':
                                spawn.X = d_x;
                                spawn.Y = d_y;
                                *entity_char = ' ';
                                break;
                            case 'm':
                                entity_type = 8;
                                enemy_count++;
                                //entity_list.push_back (new_entity);
                                break;
                            case '3':
                                entity_type = 3;
                                enemy_count++;
                                break;
                            default:
                                std::cout << "Unknown entity found named: " << level_mesh[d_y][d_x] << " at (" << d_x << "," << d_y << ")";
                                break;
                        }
                        if(*entity_char != '@'){
                        //Create our new entity
                        Entity new_entity(entity_type);
                        new_entity.position.X = d_x;
                        new_entity.position.Y = d_y;
                        dest.push_back (new_entity);
                        //Let the level mesh know that we've created the entity
                        *entity_char = ' ';
                        }
                    }

                }
                cmd_pointer.Y++;
            }
        }

        Level(int currentlevel){
            std::string result;
            std::stringstream levelstream;
            levelstream << "files/" << "level" << currentlevel << ".txt";
            result = levelstream.str();

            FILE * load_level;
            std::cout << result.c_str();
            load_level = fopen (result.c_str(),"r");

            char loaded_level[21][95];

            for(int r = 0; r < 21; ++r) // go through each line
            {
                for(int c = 0; c < 93; ++c) // go through each item
                {
                    char cha = fgetc(load_level);
                    if(cha!= '\n'){
                        level_mesh[r][c] = cha;
                    }
                }
            }
            char line[256];
            shields = atoi(fgets(line, sizeof(line),load_level));
            bolts = atoi(fgets(line, sizeof(line),load_level));


/*
            for(int ro=0;ro<24;ro++){
                strcpy(level_mesh[ro],load_level[ro]);
            }*/
        };

};
