#include <cassert>
#include <iostream>

float advance_towards(float current, float target, float max_delta)
{
    assert(max_delta >= 0.0f);
    if (current > target)
    {
        if (current - max_delta <= target)
        {
            return target;
        }
        return current - max_delta;
    }
    if (target <= current + max_delta)
    {
        return target;
    }
    return current + max_delta;
}
