#pragma once
static class GPSMath
{
public:
	GPSMath();
	~GPSMath();
static float GetDistanceInFeet(float Lat1, float Lon1, float Lat2, float Lon2);
static float GetHeading(float Lat1, float Lon1, float Lat2, float Lon2);
};

