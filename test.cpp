extern "C" {
#include "libs/rpi_ws281x/gpio.h"
#include "libs/rpi_ws281x/ws2811.h"
#include "libs/rpi_ws281x/clk.h"
#include "libs/rpi_ws281x/dma.h"
#include "libs/rpi_ws281x/pwm.h"
}
//#include "libs/rpi_ws281x/version.h"
#include <cstdio>

// defaults for cmdline options
#define TARGET_FREQ             WS2811_TARGET_FREQ
#define GPIO_PIN                18
#define DMA                     10
//#define STRIP_TYPE            WS2811_STRIP_RGB		// WS2812/SK6812RGB integrated chip+leds
#define STRIP_TYPE              WS2811_STRIP_GBR		// WS2812/SK6812RGB integrated chip+leds
//#define STRIP_TYPE            SK6812_STRIP_RGBW		// SK6812RGBW (NOT SK6812RGB)

#define WIDTH                   32
#define HEIGHT                  8
#define LED_COUNT               (WIDTH * HEIGHT)


int width = WIDTH;
int height = HEIGHT;
int led_count = LED_COUNT;

int clear_on_exit = 0;

ws2811_t ledstring =
{
    .freq = TARGET_FREQ,
    .dmanum = DMA,
    .channel =
    {
        [0] =
        {
            .gpionum = GPIO_PIN,
            .invert = 0,
	    .count = LED_COUNT,
            .strip_type = STRIP_TYPE,
	    .brightness = 32,
        },
        [1] =
        {
            .gpionum = 0,
            .invert = 0,
            .count = 0,
	    .brightness = 0,
        },
    },
};

int main(){
	ws2811_init(&ledstring);
	ledstring.channel[0].leds[0] = 255;
	ledstring.channel[0].leds[255] = 0x00100010;

        if (ws2811_render(&ledstring) != WS2811_SUCCESS)
        {
            fprintf(stderr, "ws2811_render failed\n");
        }

	ws2811_fini(&ledstring);


	return 0;
}

