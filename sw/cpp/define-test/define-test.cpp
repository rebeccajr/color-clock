#include <stdio.h>

#define SECONDS_PER_MIN   60.0
#define MINUTES_PER_HOUR  60.0
#define SECONDS_PER_HOUR  SECONDS_PER_MIN * MINUTES_PER_HOUR 

#define CC0_CYCLE_TIME_HOURS (12.0 / SECONDS_PER_HOUR)

int main()
{
  printf("CC0_CYCLE_TIME_HOURS: %f", CC0_CYCLE_TIME_HOURS);
  printf("\nSECONDS_PER_HOUR:     %f", SECONDS_PER_HOUR);

  return 0;
}