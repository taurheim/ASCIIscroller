void run_ai(Entity& ent, _COORD player_pos){
    if(ent.type==8){
        int *animation_frame = &ent.animation_frame;
        *animation_frame = *animation_frame + 1;
    } else if(ent.type==3){
        int *animation_frame = &ent.animation_frame;
        *animation_frame = *animation_frame + 1;

        if(player_pos.X > ent.position.X){
            bool *fr = &ent.faceRight;
            *fr = true;
        } else {
            bool *fr = &ent.faceRight;
            *fr = false;
        }

        if(player_pos.Y == ent.position.Y && ent.animation_frame>20){
            *animation_frame = 0;
            bool *ia = &ent.isAttacking;
            *ia = true;
        }
    }
}
