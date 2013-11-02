#include <Arduino.h>
void setup();
void loop();
void cmd_led();
void unrecognized(const char *command);
#line 1 "src/sketch.ino"

#include <SerialCommand.h>
#include <Adafruit_NeoPixel.h>

#define P   Serial.print
#define PLN Serial.println

SerialCommand sCmd;

#define PIN 13

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);

void setup() {

    Serial.begin(115200);

    sCmd.setDefaultHandler(unrecognized);
    sCmd.addCommand("l", cmd_led);
//    sCmd.addCommand("help", cmd_help);

    strip.begin();
    strip.show(); // Initialize all pixels to 'off'
}

unsigned char i = 1;
void loop() {

    sCmd.readSerial();

}

void cmd_led() {
    char *arg;
    uint8_t index = 0;
    uint8_t r, g, b = 0;

    arg = sCmd.next();
    index = atoi(arg);

    arg = sCmd.next();
    r = atoi(arg);

    arg = sCmd.next();
    g = atoi(arg);

    arg = sCmd.next();
    b = atoi(arg);

    strip.setPixelColor(index, r, g, b);
    strip.show();

    P("Set led ");
    P(index);
    P(" to color ");
    P(r);
    P(", ");
    P(g);
    P(", ");
    PLN(b);
}

void unrecognized(const char *command) {
    PLN("Command not found !");
}

