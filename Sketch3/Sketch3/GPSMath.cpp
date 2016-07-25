#include "GPSMath.h"
#include <Arduino.h>

#define Pi 3.1415926535


float LinearDistance(float Latdist, float Londist, float PosLat, float TarLat)
{
	float flatdist1 = (sin(Latdist*0.5f)*sin(Latdist * 0.5f));
	float flatdist2 = cos(PosLat);
	flatdist2 *= cos(TarLat);
	flatdist2 *= sin(Londist * 0.5f);
	flatdist2 *= sin(Londist * 0.5f);
	flatdist1 += flatdist2;
	flatdist1 = (2 * atan2(sqrt(flatdist1), sqrt(1 - flatdist2)));
	flatdist1 *= 6371000.0;
	flatdist1 *= 3;
	return flatdist1;
}

float GPSMath::GetDistanceInFeet(float PosLat, float PosLon, float TarLat, float TarLon)
{
	float Latdist = radians(TarLat - PosLat);
	float PosLatRads = radians(PosLat);
	float TarLatRads = radians(TarLat);
	float Londist = radians(TarLon - PosLon);

	return LinearDistance(Latdist,Londist,PosLatRads,TarLatRads);
}

float GetDegreestoPoint(float PosLatRads, float PosLonRads, float TarLatRads, float TarLonRads)
{
	float deg = atan2(sin(TarLonRads - PosLonRads) * cos(TarLatRads), cos(PosLatRads) * sin(TarLatRads) - sin(PosLatRads) * cos(TarLatRads) * cos(TarLonRads - PosLonRads));// *2 * Pi;
	deg = deg * 180 / Pi;
	return deg;
}

float GPSMath::GetHeading(float PosLat, float PosLon, float TarLat, float TarLon, float CurrentHeadinginDegrees, bool HemisphereModifier)
{
	float PosLatRads = radians(PosLat);
	float TarLatRads = radians(TarLat);
	float PosLonRads = radians(PosLon);
	float TarLonRads = radians(TarLon);

	float Degreestopoint = GetDegreestoPoint(PosLatRads, PosLonRads, TarLatRads, TarLonRads);

	if (Degreestopoint < 0)
	{
		Degreestopoint += 360;
	}

	Degreestopoint -= CurrentHeadinginDegrees;

	if (Degreestopoint < 0)
	{
		Degreestopoint += 360;
	}

	return Degreestopoint;
}