#include <SwitchControlLibrary.h>

extern const uint8_t image_data[0x12c1] PROGMEM;

const uint16_t PRESS_WAIT_TIME   = 96;
const uint16_t RELEASE_WAIT_TIME = 96;
int xpos = 0;
int ypos = 0;

void pushHat(uint8_t hat, unsigned int delay_time = PRESS_WAIT_TIME);
void pushHat(uint8_t hat, unsigned int delay_time) {
	SwitchControlLibrary().pressHatButton(hat);
	SwitchControlLibrary().sendReport();
	delay(delay_time);
	SwitchControlLibrary().releaseHatButton(hat);   
	SwitchControlLibrary().sendReport();   
	delay(RELEASE_WAIT_TIME);
}

void pushButton(uint16_t button, unsigned int delay_time = PRESS_WAIT_TIME);
void pushButton(uint16_t button, unsigned int delay_time) {
	SwitchControlLibrary().pressButton(button);
	SwitchControlLibrary().sendReport();
	delay(delay_time);
	SwitchControlLibrary().releaseButton(button);
	SwitchControlLibrary().sendReport();
	delay(RELEASE_WAIT_TIME);
}

void tiltLeftStick(uint8_t lx, uint8_t ly, unsigned long tilt_time) {
	SwitchControlLibrary().moveLeftStick(lx, ly);
	SwitchControlLibrary().sendReport();
	delay(tilt_time);
	SwitchControlLibrary().moveLeftStick(Stick::NEUTRAL, Stick::NEUTRAL);
	SwitchControlLibrary().sendReport();
	delay(RELEASE_WAIT_TIME);
}

void pushdot() {
    if (pgm_read_byte(&(image_data[(xpos / 8) + (ypos * 40)])) & 1 << (xpos % 8)) {
		pushButton(Button::A);
    }
}

void setup() {
	SwitchControlLibrary();
	for(int i=0;i<50;i++) pushButton(Button::A, 24);
	delay(500);
	tiltLeftStick(Stick::MIN, Stick::MIN, 5000);
	delay(500);
	pushButton(Button::L, 24);
	delay(500);
	pushButton(Button::LCLICK);
}

void loop() {
	if (ypos < 120) {
		if (ypos % 2) {
			pushdot();
			for ( xpos=318; xpos>=0; xpos-- ) {
				pushHat(HatButton::LEFT);
				pushdot();
			}
			for(int i=0;i<12;i++) pushHat(HatButton::LEFT, 24);
		} else {
			pushdot();
			for ( xpos=1; xpos<320; xpos++ ) {
				pushHat(HatButton::RIGHT);
				pushdot();
			}
			for(int i=0;i<12;i++) pushHat(HatButton::RIGHT, 24);
		}
		pushHat(HatButton::DOWN);
		ypos++;
	} else if (ypos = 120) {
		pushButton(Button::MINUS);
		ypos++;
	}
}
