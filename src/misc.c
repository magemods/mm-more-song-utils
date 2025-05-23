#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "recompconfig.h"
#include "magemods_globals.h"

static s32 timeSpeedOffset;

RECOMP_HOOK("Sram_SaveEndOfCycle") void on_Sram_SaveEndOfCycle_misc() {
    timeSpeedOffset = gSaveContext.save.timeSpeedOffset;
}

RECOMP_HOOK_RETURN("Sram_SaveEndOfCycle") void after_Sram_SaveEndOfCycle_misc() {
    if (!get_config_bool("time_speed_persist")) {
        return;
    }
    gSaveContext.save.timeSpeedOffset = timeSpeedOffset;
}
