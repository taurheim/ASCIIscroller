void run_ai(Entity& ent){
    if(ent.type==8){
        int *animation_frame = &ent.animation_frame;
        *animation_frame = *animation_frame + 1;
    }
}
