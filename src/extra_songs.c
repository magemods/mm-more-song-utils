#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "recompconfig.h"
#include "magemods_globals.h"

static u32 questItems = 0;

static void enable_songs() {
    questItems = gSaveContext.save.saveInfo.inventory.questItems;

    if (get_config_bool("extra_song_suns")) {
        SET_QUEST_ITEM(QUEST_SONG_SONATA + OCARINA_SONG_SUNS);
    }
    if (get_config_bool("extra_song_sarias")) {
        SET_QUEST_ITEM(QUEST_SONG_SONATA + OCARINA_SONG_SARIAS);
    }
}

static void disable_songs() {
    if (questItems == 0) {
        return;
    }
    if ((questItems & gBitFlags[QUEST_SONG_SONATA + OCARINA_SONG_SUNS]) == 0) {
        REMOVE_QUEST_ITEM(QUEST_SONG_SONATA + OCARINA_SONG_SUNS);
    }
    if ((questItems & gBitFlags[QUEST_SONG_SONATA + OCARINA_SONG_SARIAS]) == 0) {
        REMOVE_QUEST_ITEM(QUEST_SONG_SONATA + OCARINA_SONG_SARIAS);
    }

    questItems = 0;
}

RECOMP_HOOK("Message_DisplayOcarinaStaffImpl") void on_DisplayOcarinaStaffImpl() {
    enable_songs();
}
RECOMP_HOOK_RETURN("Message_HandleOcarina") void after_HandleOcarina() {
    disable_songs();
}
RECOMP_HOOK_RETURN("Message_CloseTextbox") void after_CloseTextbox() {
    disable_songs();
}
RECOMP_HOOK_RETURN("AudioOcarina_SetPlaybackSong") void after_SetPlaybackSong() {
    disable_songs();
}
