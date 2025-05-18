#ifndef __MOD_CONFIG__
#define __MOD_CONFIG__

#include <stdbool.h>
#include "global.h"
#include "recompconfig.h"

extern PlayState* gPlayState;

enum config_options_bool {
    CONFIG_ON,
    CONFIG_OFF,
};

bool get_config_bool(char str[]);

#endif
