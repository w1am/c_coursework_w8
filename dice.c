#include <stdio.h>
#include <time.h>
#include <stdlib.h> // Malloc
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

  printf("%d\n", result);

  return result;
}

struct Dice {
  int face;
  int occurrence;
};

int main(void) {
  int faces, throws, total = 0;

  printf("Enter number of faces: ");
  scanf("%d", &faces);

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
  
  struct Dice *dice = malloc(throws * sizeof(struct Dice));

  for (int i=1; i<=faces; i++) dice[i].occurrence = 0;

  printf("\nGenerating throws: \n");
  for (int i=1; i<=throws; i++) {
    total = randNumber(faces);
    dice[total].face = total;
    dice[total].face ? dice[total].occurrence += 1 : (dice[total].occurrence = 1);
  };

  printf("\nFace \t Count \t Occurence \n");
  for (int i=1; i<=faces; i++)
    printf("%d \t %d \t %.2f%%\n", i, dice[i].occurrence, dice[i].occurrence/(float)throws*100);

  free(dice);

  return 0;
}
