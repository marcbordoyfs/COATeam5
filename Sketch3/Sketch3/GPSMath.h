#pragma once
class GPSMath
{
public:
static float GetDistanceInFeet(float PosLat, float PosLon, float TarLat, float TarLon);
static float GetHeading(float PosLat, float PosLon, float TarLat, float TarLon, float CurrentHeadinginDegrees);
static void DegreesMinutesToDecimalDegreesConversion(float &Latitude, float &Longitude, bool SouthernHemisphere, bool WesternHemisphere);
};

