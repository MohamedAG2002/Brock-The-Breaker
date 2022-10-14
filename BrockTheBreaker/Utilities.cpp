#include "Utilities.h"

float utl::Clamp(float value, const float min, const float max)
{
	if (value > max) return value = max;
	else if (value < min) return value = min;
	else return value;
}