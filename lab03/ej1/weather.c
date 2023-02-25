/*
  @file weather.c
  @brief Implements weather mesuarement structure and methods
*/
#include <stdlib.h>
#include "weather.h"

//static const int AMOUNT_OF_WEATHER_VARS = 6 ;------------COMENTADA PORQUE NO SABÍA QUE HACÍA xd

Weather weather_from_file(FILE* file)
{
    Weather weather;
   // <avg_temp> <max_temp> <min_temp> <pressure> <moisture> <rainfall>
    fscanf(file, " %d %d %d %u %u %u ", &weather._average_temp, &weather._max_temp, &weather._min_temp, &weather._pressure, &weather._moisture,&weather._rainfall);
    return weather;
}

void weather_to_file(FILE* file, Weather weather)
{
    fprintf(file, EXPECTED_WEATHER_FILE_FORMAT, weather._average_temp, 
            weather._max_temp, weather._min_temp, weather._pressure, weather._moisture, weather._rainfall);
}
