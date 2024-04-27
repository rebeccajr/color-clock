#include <stdio.h>
#include "flux-clock.hpp"

int main(void)
{
  FluxClock clock;
  int count = 0;
  int prev_sec = 0;
  int sec = 0;

  while (count < 30)
  {
    sec = (&clock)->get_sec();
    if (prev_sec != sec)
    {
      printf("_____________\n");
      printf("year:  %4d\n", (&clock)->get_yr() + 1900);
      printf("month: %4d\n", (&clock)->get_month() + 1);
      printf("day:   %4d\n", (&clock)->get_day());
      printf("hour:  %4d\n", (&clock)->get_hr());
      printf("min:   %4d\n", (&clock)->get_min());
      printf("sec:   %4d\n", (&clock)->get_sec());
      count++;
    }
    prev_sec = sec;
  }
}