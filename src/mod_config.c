#include "mod_config.h"

bool get_config_bool(char str[]) {
    return recomp_get_config_u32(str) == CONFIG_ON;
}
