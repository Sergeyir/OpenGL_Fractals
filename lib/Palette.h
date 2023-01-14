#include <cmath>

struct OceanPalette
{
	float R(float col_val)
	{
		return 0;
	}
	float G(float col_val)
	{
		float val = 0.8*sqrt(col_val);
		return val;
	}
	float B(float col_val)
	{
		float val = 0.9*pow(col_val, 1./4.);
		return val;
	}
};

struct CrimsonPalette
{
	float R(float col_val)
	{
		float val = 0.8*pow(col_val, 1./4.);
		return val;
	}
	float G(float col_val)
	{
		return 0;
	}
	float B(float col_val)
	{
		return 0;
	}
};

struct Neon
{
	float R(float col_val)
	{
		float val = 0.5*pow(col_val, 1./4.);
		return val;
	}
	float G(float col_val)
	{
		float val = 0.4*col_val;
		return val;
	}
	float B(float col_val)
	{
		float val = 0.7*pow(col_val, 1./4.);
		return val;
	}
};
