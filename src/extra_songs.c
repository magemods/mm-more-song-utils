#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "recompconfig.h"
#include "magemods_globals.h"

extern s16 sOcarinaSongFanfares[];

static u32 origQuestItems = 0;

enum config_options_sarias {
    CONFIG_PLAY_SARIAS,
    CONFIG_PLAY_FINAL_HOURS,
};

static void enable_songs() {
    origQuestItems = gSaveContext.save.saveInfo.inventory.questItems;

    if (get_config_bool("extra_song_suns")) {
        SET_QUEST_ITEM(QUEST_SONG_SONATA + OCARINA_SONG_SUNS);
    }
    if (get_config_bool("extra_song_sarias")) {
        SET_QUEST_ITEM(QUEST_SONG_SONATA + OCARINA_SONG_SARIAS);

        if (recomp_get_config_u32("extra_song_sarias_song_id") == CONFIG_PLAY_SARIAS) {
            sOcarinaSongFanfares[5] = NA_BGM_SARIAS_SONG;
        } else {
            sOcarinaSongFanfares[5] = NA_BGM_FINAL_HOURS;
        }
    }
}

static void disable_songs() {
    if (origQuestItems == 0) {
        return;
    }

    if ((origQuestItems & gBitFlags[QUEST_SONG_SONATA + OCARINA_SONG_SUNS]) == 0) {
        REMOVE_QUEST_ITEM(QUEST_SONG_SONATA + OCARINA_SONG_SUNS);
    }

    if ((origQuestItems & gBitFlags[QUEST_SONG_SONATA + OCARINA_SONG_SARIAS]) == 0) {
        REMOVE_QUEST_ITEM(QUEST_SONG_SONATA + OCARINA_SONG_SARIAS);
    }

    origQuestItems = 0;
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
