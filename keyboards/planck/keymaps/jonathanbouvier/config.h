#pragma once

#ifdef AUDIO_ENABLE
    #define DEFAULT_LAYER_SONGS { SONG(QWERTY_SOUND), \
                                  SONG(ONE_UP) \
                                }
#endif

#define NO_MUSIC_MODE

#define TAPPING_TERM 200

#define IGNORE_MOD_TAP_INTERRUPT

#define PERMISSIVE_HOLD
