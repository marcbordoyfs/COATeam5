#include "Indicator.h"
#include <Arduino.h>

#define NEOPIXELPIN 6
#define LEDArraySize 16
#define COLORRED Neopixel.Color(255, 0, 0)
#define COLORYELLOW Neopixel.Color(255, 255, 0)
#define COLORGREEN Neopixel.Color(0, 255, 0)

Indicator::Indicator()
{
}


Indicator::~Indicator()
{
}

void Indicator::Initialize()
{
	Neopixel = Adafruit_NeoPixel(60, NEOPIXELPIN, NEO_GRB + NEO_KHZ800);
	Neopixel.begin();
	Neopixel.setBrightness(3);
	Neopixel.show();
	CurrHeading = 500;
	CurrentDistanceLevel = 1;
#pragma region LED Array Initialization
	RadialLEDs[0] = 31;
	RadialLEDs[1] = 39;
	RadialLEDs[2] = 38;
	RadialLEDs[3] = 37;
	RadialLEDs[4] = 36;
	RadialLEDs[5] = 35;
	RadialLEDs[6] = 27;
	RadialLEDs[7] = 19;
	RadialLEDs[8] = 11;
	RadialLEDs[9] = 3;	
	RadialLEDs[10] = 4;	
	RadialLEDs[11] = 5;
	RadialLEDs[12] = 6;
	RadialLEDs[13] = 7;
	RadialLEDs[14] = 15;	
	RadialLEDs[15] = 23;
#pragma endregion
}

int LEDSafeIndex(int index)
{
	int i = index;
	while (i >= LEDArraySize)
	{
		i -= LEDArraySize;
	}
	while (i < 0)
	{
		i += LEDArraySize;
	}
	return i;
}

void Indicator::UpdateDisplay(int HeadingDegrees, int DistanceInFeet)
{
	int16_t Headingdif = CurrHeading - HeadingDegrees;
	int16_t NewHeading = -1;
	if (Headingdif > 20 || Headingdif < 20);
	{
		NewHeading = map(HeadingDegrees, 0, 360, 0, 16);
		CurrHeading = map(NewHeading, 0, 16, 0, 360);
	}
	int16_t Mindist = 1;
	int16_t Maxdist = 10;
	switch (CurrentDistanceLevel)
	{
		//All Green
	case 1:
		Mindist = 0;
		Maxdist = 5;
		break;
		//Center Yellow
	case 2:
		Mindist = 5;
		Maxdist = 25;
		break;
		//Inner Yellow
	case 3:
		Mindist = 25;
		Maxdist = 100;
		break;
		//All Yellow
	case 4:
		Mindist = 100;
		Maxdist = 250;
		break;
		//Center Red;
	case 5:
		Mindist = 250;
		Maxdist = 500;
		break;
		//Inner Red
	case 6:
		Mindist = 500;
		Maxdist = 750;
		break;
		//All Red
	case 7:
		Mindist = 750;
		Maxdist = 1000;
		break;
		//Outer off
	case 8:
		Mindist = 1000;
		Maxdist = 1250;
		break;
		//Center Only
	case 9:
		Mindist = 1250;
		Maxdist = 5000;
		break;
	}
	bool DistChange = false;
	if (DistanceInFeet > Maxdist)
	{
		CurrentDistanceLevel += 1;
		DistChange = true;
	}
	else if (DistanceInFeet < Mindist)
	{
		CurrentDistanceLevel -= 1;
		DistChange = true;
	}
	if (DistChange || NewHeading >= -1)
	{
		Neopixel.clear();
		LEDActivateByDistance(NewHeading, CurrentDistanceLevel);
		Neopixel.show();
	}
}

void Indicator::LEDActivateByDistance(int HeadingCenterLEDINDEX, int DistanceLevel)
{
	switch (DistanceLevel)
	{
	case 1:
		for (int8_t i = HeadingCenterLEDINDEX - 2; i <= HeadingCenterLEDINDEX + 2; i++)
		{
			Neopixel.setPixelColor(RadialLEDs[LEDSafeIndex(i)], COLORGREEN);
		}
		break;
	case 2:
		for (int8_t i = HeadingCenterLEDINDEX - 2; i <= HeadingCenterLEDINDEX + 2; i++)
		{
			Neopixel.setPixelColor(RadialLEDs[LEDSafeIndex(i)], COLORGREEN);
		}
		Neopixel.setPixelColor(RadialLEDs[LEDSafeIndex(HeadingCenterLEDINDEX)], COLORYELLOW);
		break;				   
	case 3:
		for (int8_t i = HeadingCenterLEDINDEX - 2; i <= HeadingCenterLEDINDEX + 2; i++)
		{
			Neopixel.setPixelColor(RadialLEDs[LEDSafeIndex(i)], COLORYELLOW);
		}
		Neopixel.setPixelColor(RadialLEDs[LEDSafeIndex(HeadingCenterLEDINDEX + 2)], COLORGREEN);
		Neopixel.setPixelColor(RadialLEDs[LEDSafeIndex(HeadingCenterLEDINDEX - 2)], COLORGREEN);
		break;				   
	case 4:
		for (int8_t i = HeadingCenterLEDINDEX - 2; i <= HeadingCenterLEDINDEX + 2; i++)
		{
			Neopixel.setPixelColor(RadialLEDs[LEDSafeIndex(i)], COLORYELLOW);
		}
		break;				   
	case 5:
		for (int8_t i = HeadingCenterLEDINDEX - 2; i <= HeadingCenterLEDINDEX + 2; i++)
		{
			Neopixel.setPixelColor(RadialLEDs[LEDSafeIndex(i)], COLORYELLOW);
		}
		Neopixel.setPixelColor(RadialLEDs[LEDSafeIndex(HeadingCenterLEDINDEX)], COLORRED);
		break;				   
	case 6:
		for (int8_t i = HeadingCenterLEDINDEX - 2; i <= HeadingCenterLEDINDEX + 2; i++)
		{
			Neopixel.setPixelColor(RadialLEDs[LEDSafeIndex(i)], COLORRED);
		}
		Neopixel.setPixelColor(RadialLEDs[LEDSafeIndex(HeadingCenterLEDINDEX + 2)], COLORYELLOW);
		Neopixel.setPixelColor(RadialLEDs[LEDSafeIndex(HeadingCenterLEDINDEX - 2)], COLORYELLOW);
		break;				   
	case 7:					   
		for (int8_t i = HeadingCenterLEDINDEX - 2; i <= HeadingCenterLEDINDEX + 2; i++)
		{
			Neopixel.setPixelColor(RadialLEDs[LEDSafeIndex(i)], COLORRED);
		}
		break;				   
	case 8:					   
		for (int8_t i = HeadingCenterLEDINDEX - 1; i <= HeadingCenterLEDINDEX + 1; i++)
		{
			Neopixel.setPixelColor(RadialLEDs[LEDSafeIndex(i)], COLORRED);
		}
		break;				   
	case 9:					   
		Neopixel.setPixelColor(RadialLEDs[LEDSafeIndex(HeadingCenterLEDINDEX)], COLORRED);
		break;
	}
}

void Indicator::WipeLEDs()
{
	Neopixel.clear();
	Neopixel.show();
	}

#if IdentifyingLEDs

void Indicator::ActivateLED(int LED)
{
	Neopixel.clear();
	//	Neopixel.begin();
	Neopixel.setPixelColor(LED, Neopixel.Color(0, 255, 0));
	Neopixel.show();
}

int Indicator::NeopixelLEDcount()
{
	return 40;
}

#endif