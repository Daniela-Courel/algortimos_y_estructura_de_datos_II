#include <weather_utils.h>

int min_tem_hist(WeatherTable array){
    int minim = array[0][0][0]._min_temp;
    for (unsigned int year = 0u; year < YEARS; ++year) {
        for (month_t month = january; month <= december; ++month) {
            for (unsigned int day = 0u; day < DAYS; ++day) {
                minim = min(array[year][month][day],minim);
            }
        }
    }
    return minim;
}

