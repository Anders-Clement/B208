#include "map.h"

float map(float x, float in_min, float in_max, float out_min, float out_max)
{
    double in_normal = (x - in_min) / (in_max - in_min);
    return in_normal*(out_max - out_min) + out_min;
}
