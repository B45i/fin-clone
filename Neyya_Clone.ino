#include <Arduino.h>
#include <BleKeyboard.h> // https://github.com/T-vK/ESP32-BLE-Keyboard/releases

BleKeyboard bleKeyboard("Fin Clone", "B45i", 87);

#define PIN_UP    32
#define PIN_CLICK 33
#define PIN_LEFT  34
#define PIN_DOWN  35
#define PIN_RIGHT 36

void IRAM_ATTR handleUp() {
	Serial.println("Up Pressed!");
	if (!bleKeyboard.isConnected()) {
		return;
	}
	bleKeyboard.write(KEY_MEDIA_VOLUME_UP);
}

void IRAM_ATTR handleRight() {
	Serial.println("Right Pressed!");
	if (!bleKeyboard.isConnected()) {
		return;
	}
	bleKeyboard.write(KEY_MEDIA_NEXT_TRACK);
}

void IRAM_ATTR handleDown() {
	Serial.println("Down Pressed!");
	if (!bleKeyboard.isConnected()) {
		return;
	}
	bleKeyboard.write(KEY_MEDIA_VOLUME_DOWN);
}

void IRAM_ATTR handleLeft() {
	Serial.println("Left Pressed!");
	if (!bleKeyboard.isConnected()) {
		return;
	}
	bleKeyboard.write(KEY_MEDIA_PREVIOUS_TRACK);
}

void IRAM_ATTR handleClick() {
	Serial.println("Click !");
	if (!bleKeyboard.isConnected()) {
		return;
	}
	bleKeyboard.write(KEY_MEDIA_PLAY_PAUSE);
}

void setup() {
	Serial.begin(115200);
	Serial.println("Starting BLE!");

	pinMode(LED_BUILTIN, OUTPUT);

	pinMode(PIN_UP, INPUT_PULLUP);
	pinMode(PIN_RIGHT, INPUT_PULLUP);
	pinMode(PIN_DOWN, INPUT_PULLUP);
	pinMode(PIN_LEFT, INPUT_PULLUP);
	pinMode(PIN_CLICK, INPUT_PULLUP);

	attachInterrupt(PIN_UP, handleUp, FALLING);
	attachInterrupt(PIN_RIGHT, handleRight, FALLING);
	attachInterrupt(PIN_DOWN, handleDown, FALLING);
	attachInterrupt(PIN_LEFT, handleLeft, FALLING);
	attachInterrupt(PIN_CLICK, handleClick, FALLING);

	bleKeyboard.begin();
}

void loop() {
	if (!bleKeyboard.isConnected()) {
		digitalWrite(LED_BUILTIN, LOW);
		return;
	} else {
		digitalWrite(LED_BUILTIN, HIGH);
	}
}
