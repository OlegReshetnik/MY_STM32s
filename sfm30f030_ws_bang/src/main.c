#include "system.h"
#include "ws2812.h"

typedef struct {
    void (*p_effect)(void);
    uint32_t fps;
    uint32_t len;
} effect_t;

const effect_t effects[] = {
    {wsWeel, 25, 8000},
    {wsFire, 80, 8000},
    {wsColors, 30, 8000},
    {wsSparkles, 30, 8000}
};
#define N_EFF	(sizeof(effects)/sizeof(effects[0]))

int main(void) {
    uint32_t oldLen = 0, oldFps = 0;
    uint16_t i_effect = 0;

    SysInit();
    WsInit();

    for(;;) {
        if ((millis-oldLen) >= effects[i_effect].len) {
            oldLen = millis;
            i_effect++;
            if (i_effect == N_EFF) { i_effect = 0; }
        }

        if ((millis-oldFps) >= effects[i_effect].fps) {
            oldFps = millis;
            effects[i_effect].p_effect();
            WsSend();
        }

    }
}
