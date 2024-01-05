#pragma once

#include "Position.h"

class ITankMovementStrategy
{
    virtual Position move() = 0;
};
