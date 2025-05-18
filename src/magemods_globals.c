#include "magemods_globals.h"

PlayState* gPlayState;

RECOMP_HOOK("Play_Init") void on_Play_Init(GameState* thisx) {
    gPlayState = (PlayState*)thisx;
}

bool get_config_bool(char str[]) {
    return recomp_get_config_u32(str) == CONFIG_ON;
}
