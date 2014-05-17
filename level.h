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

        std::vector<Entity> getEntities(){
            _COORD cmd_pointer;
            cmd_pointer.X = 0;
            cmd_pointer.Y = 0;

            std::vector<Entity> entity_list;

            for(int d_y=0;d_y<24;d_y++){
                cmd_pointer.X = 0;
                for(int d_x=0;d_x<95;d_x++){
                    if(level_mesh[d_y][d_x]!= '#' && level_mesh[d_y][d_x]!= ' ' && level_mesh[d_y][d_x]!='\0'){

                        //Point to where that char is located
                        char *entity_char = &level_mesh[d_y][d_x];
                        char entity_type;

                        //We've found an entity -> Create it!
                        switch(level_mesh[d_y][d_x]){
                            case '@':
                                std::cout << "Spawn found at " << d_x << "," << d_y << std::endl;
                                spawn.X = d_x;
                                spawn.Y = d_y;
                                *entity_char = ' ';
                                continue;
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

                        //Create our new entity
                        Entity new_entity(entity_type);
                        new_entity.position.X = d_x;
                        new_entity.position.Y = d_y;
                        entity_list.push_back (new_entity);
                        //Let the level mesh know that we've created the entity
                        *entity_char = ' ';
                    }

                }
                cmd_pointer.Y++;
            }

            //Entity goblin(3);
            //entity_list.push_back(goblin);

            return entity_list;
        };

        Level(){
            for(int ro=0;ro<24;ro++){
                strcpy(level_mesh[ro],level_1[ro]);
            }
        };

};
