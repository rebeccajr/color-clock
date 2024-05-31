#include <stdio.h>
#define BAR

struct foo
{
  int a = 43;
};

int main()
{

  int a = 7;
#ifdef BAR
  foo aw;
#endif

  printf("\n\n number: %d\n\n",
#ifdef BAR
  aw.
#endif
  a);

  return 0;
}
