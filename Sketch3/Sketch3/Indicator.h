#pragma once
#include <Adafruit_NeoPixel-master\Adafruit_NeoPixel.h>
#include <Arduino.h>;
#define IdentifyingLEDs 0

class Indicator
{
	Adafruit_NeoPixel Neopixel;
	int16_t CurrHeading;
	int8_t CurrentDistanceLevel;
	int8_t RadialLEDs[16];
public:
	Indicator();
	~Indicator();
	void Initialize();
	void UpdateDisplay(int HeadingDegrees, int DistanceInFeet);
	void LEDActivateByDistance(int HeadingCenterLED, int DistanceInFeet);
	void WipeLEDs();
#if IdentifyingLEDs
	void ActivateLED(int LED);
	int NeopixelLEDcount();
#endif
};

