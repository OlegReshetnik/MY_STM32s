#include "system.h"
#include "ws2812_TIM14.h"
#include "sensor.h"

typedef struct {
	void (*p_effect)(void);
	uint32_t fps;
} effect_t;

const effect_t effects[] = {
	{wsFire, 80},
	{wsWeel, 30},
	{wsBugs, 40},
	{wsColors, 60},
	{wsSparkles, 60},
	{wsWeel, 20}
};


#define N_EFF	(sizeof(effects)/sizeof(effects[0]))

int main(void) {
	uint32_t oldT = 0, oldFps = 0, tSens = 20;
	uint16_t i_effect = 0;

	SysInit();
	WsInit();
	SensorInit();

	for(;;) {

		if ((millis-oldT) >= tSens) {
			oldT = millis;
			if (SensorTouch()) {
				tSens = 1000;
				i_effect++;
				if (i_effect == N_EFF) { i_effect = 0; }
			} else { tSens = 20; }
		}

		if ((millis-oldFps) >= effects[i_effect].fps) {
			oldFps = millis;
			effects[i_effect].p_effect();
			WsSend();
		}
	}
}
