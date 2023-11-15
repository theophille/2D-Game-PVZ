#pragma once

#define LIVES 3
#define BOARD_SIZE 3
#define ENEMIES 4
#define ENTITIES 4
#define WAIT_TIME 6
#define HP_GEN_TIME 10
#define HP_GEN_COUNT 3
#define BULLETS_TIME 4
#define MAX_STARS_NUM 7

#define RAD_CONST M_PI / 180.0
#define DEG_TO_RAD(degrees) ((degrees) * RAD_CONST)
#define ROUND(value, decimalPlaces) \
    (std::round((value) * std::pow(10, (decimalPlaces))) / std::pow(10, (decimalPlaces)))