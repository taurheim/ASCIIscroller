#include "windows.h"
#include <vector>
#include <iostream>


char level_1[23][95] = {
"                  ########################################################                  ",
"                  #     @                                                #                  ",
"                  #                 #############                        #                  ",
"                  #                             #                        #                  ",
"                  #        #####                #                        #                  ",
"                  #                 #####       #                        #                  ",
"                  #                      ##     #                        #                  ",
"                  #           h                 #                        #                  ",
"                  #                             #                        #                  ",
"                  #                  ####################                #                  ",
"                  #                     #               #                #                  ",
"                  #        ######       #               #                #                  ",
"                  #######################               #                #                  ",
"                                                        #                #                  ",
"                                                        #                #                  ",
"                                                        #                #                  ",
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

        void pushEntitiesTo(std::vector<Entity> & dest){
            /*
            for(int bk=0;bk<23;bk++){
            std::cout << level_mesh[bk] << std::endl;
            }
            Sleep(10000);*/

            _COORD cmd_pointer;
            cmd_pointer.X = 0;
            cmd_pointer.Y = 0;


            for(int d_y=0;d_y<23;d_y++){
                cmd_pointer.X = 0;
                for(int d_x=0;d_x<93;d_x++){
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
                                std::cout << "Spawn found at " << d_x << "," << d_y << std::endl;
                                spawn.X = d_x;
                                spawn.Y = d_y;
                                *entity_char = ' ';
                                break;
                            case 'h':
                                std::cout << "Level 1 bat found at " << d_x << "," << d_y << std::endl;
                                entity_type = 8;
                                //entity_list.push_back (new_entity);
                                break;
                            default:
                                std::cout << "Unknown entity found named: " << level_mesh[d_y][d_x];
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

        Level(){
            for(int ro=0;ro<24;ro++){
                strcpy(level_mesh[ro],level_1[ro]);
            }
        };

};
