#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <utime.h>
#include <sys/timeb.h>
#include <sys/time.h>

int randNumber(int limit) {
  struct timeb timer_msec;
  int result;
  long long int timestamp_msec; /* timestamp in millisecond. */
  if (!ftime(&timer_msec)) {
    timestamp_msec = ((long long int) timer_msec.time) * 1000ll +
                        (long long int) timer_msec.millitm;
  } else {
    timestamp_msec = -1;
  }
	srand ( timestamp_msec );
	/* result = rand() % limit; */
	result = rand() % limit + 1;
  usleep(98765);

  return result;
}

struct dashboard {
  int face;
  int occurrence;
};

int main(void) {
  int faces = 0;
  int throws = 0;

  printf("Enter number of faces: ");
  scanf("%i", &faces);

  while (faces < 1 || faces > 25) {
    printf("\nNumber of faces should be between 1 and 25. Please re-enter: ");
    scanf("%i", &faces);
  };

  printf("Enter number of throws: ");
  scanf("%i", &throws);

  while (throws < 1 || throws > 500) {
    printf("\nNumber of throws should be between 1 and 500. Please re-enter: ");
    scanf("%i", &throws);
  };

  struct dashboard dash[throws];

  for (int i=1; i<=faces; i++) dash[i].occurrence = 0;

  printf("Generating throws: \n");
  for (int i=1; i<=throws; i++) {
    int random_number;
    random_number = randNumber(faces);
    printf("%d\n", random_number);

    if (dash[random_number].face > 0) {
      dash[random_number].occurrence += 1;
    } else {
      dash[random_number].face = random_number;
      dash[random_number].occurrence = 1;
    }
  };

  for (int i=1; i<=faces; i++) {
    printf("Occurences of %d: (%d) %.2f%%\n", i, dash[i].occurrence, dash[i].occurrence/(float)throws*100);
  };

  return 0;
}
