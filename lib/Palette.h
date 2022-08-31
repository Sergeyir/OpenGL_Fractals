#include <cmath>

struct
{
	float R(float col_val)
	{
		return 0;
	}
	float G(float col_val)
	{
		float val = sqrt(col_val);
		return val;
	}
	float B(float col_val)
	{
		float val = pow(col_val, 1./4.);
		return val;
	}
} OceanPalette;
