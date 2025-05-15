#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "recompconfig.h"
#include "mod_config.h"

#include "overlays/actors/ovl_En_Kakasi/z_en_kakasi.c"

bool scarecrowSpawnSongSet;

RECOMP_HOOK("Sram_SaveEndOfCycle") void on_Sram_SaveEndOfCycle(PlayState* play) {
    scarecrowSpawnSongSet = gSaveContext.save.saveInfo.scarecrowSpawnSongSet;
}

RECOMP_HOOK_RETURN("Sram_SaveEndOfCycle") void after_Sram_SaveEndOfCycle() {
    if (!get_config_bool("scarecrow_persist")) {
        return;
    }
    gSaveContext.save.saveInfo.scarecrowSpawnSongSet |= scarecrowSpawnSongSet;
}

RECOMP_HOOK_RETURN("Sram_OpenSave") void after_Sram_OpenSave() {
    if (!get_config_bool("scarecrow_persist")) {
        return;
    }
    if (!gSaveContext.save.isOwlSave && gSaveContext.save.saveInfo.scarecrowSpawnSongSet) {
        Lib_MemCpy(gScarecrowSpawnSongPtr, gSaveContext.save.saveInfo.scarecrowSpawnSong,
                   sizeof(gSaveContext.save.saveInfo.scarecrowSpawnSong));
        for (s32 i = 0; i != ARRAY_COUNT(gSaveContext.save.saveInfo.scarecrowSpawnSong); i++) {}
    }
}

RECOMP_HOOK("EnKakasi_IdleUnderground") void on_EnKakasi_IdleUnderground(EnKakasi* this, PlayState* play) {
    if (!get_config_bool("scarecrow_auto")) {
        return;
    }
    if (this->picto.actor.xzDistToPlayer < this->songSummonDist && play->msgCtx.ocarinaMode == OCARINA_MODE_ACTIVE) {
        this->picto.actor.flags &= ~ACTOR_FLAG_LOCK_ON_DISABLED;
        play->msgCtx.ocarinaMode = OCARINA_MODE_END;
        this->actionFunc = EnKakasi_SetupRiseOutOfGround;

        AudioOcarina_SetInstrument(OCARINA_INSTRUMENT_OFF);
        Message_CloseTextbox(play);
    }
}
