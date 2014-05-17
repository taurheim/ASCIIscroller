#include "windows.h"
#include <vector>


char level_1[17][57] = {
"########################################################",
"#                                                      #",
"#                 #############                        #",
"#                             #                        #",
"#        #####                #                        #",
"#                 #####       #                        #",
"#                      ##     #                        #",
"#                             #                        #",
"#   @                         #                        #",
"#                  ####################                #",
"#                     #               #                #",
"#        ######       #               #                #",
"#######################               #                #",
"                                      #                #",
"                                      #                #",
"                                      #                #",
"                                      ##################"
};

class Level {
    public:
        _COORD level_anchor;
        _COORD spawn;

        std::vector<Entity> getEntities(){
            std::vector<Entity> entity_list;
            Entity goblin("goblin");
            entity_list.push_back(goblin);

            return entity_list;
        }
};
