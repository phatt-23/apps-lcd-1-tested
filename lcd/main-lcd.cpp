
#include <stdio.h>
#include <stdlib.h>

#include "mbed.h"
#include "lcd_lib.h"
#include "graph_class.hpp"

DigitalOut g_led_PTA1( PTA1, 0 );
DigitalOut g_led_PTA2( PTA2, 0 );

DigitalIn g_but_PTC9( PTC9 );
DigitalIn g_but_PTC10( PTC10 );
DigitalIn g_but_PTC11( PTC11 );
DigitalIn g_but_PTC12( PTC12 );


// two dimensional array with fixed size font
int main() {
    lcd_init();  // LCD initialization

    Circle circle({50, 50}, 30, {255, 255, 255}, {255, 0, 0});
    circle.draw();

    Line line1({50, 50}, {100, 100}, {0, 255, 0}, {0, 0, 0});
    line1.draw();

    Line line2({100, 110}, {50, 60}, {255, 0, 0}, {0, 0, 0});
    line2.draw();

    Line line3({50, 70}, {50, 170}, {0, 0, 255}, {0, 0, 0});
    line3.draw();

    Line line4({60, 170}, {60, 70}, {180, 190, 254}, {0, 0, 0});
    line4.draw();

    circle.hide();

    Character character({170, 170}, 'a', {180, 190, 254}, {0, 0, 0});
    character.draw(true);

	while(1) {};
	return 0;
}