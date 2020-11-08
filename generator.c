#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <utime.h>
#include <sys/timeb.h>
#include <sys/time.h>

char *readFile(char path[49], int wordLength, int rLine) {
  static char lineTrimmed[500];
  char str[50];
  sprintf(str, "%s/%d", path, wordLength);
  FILE *file = fopen(str, "r");

  if ( file != NULL ) {
    char line[500]; /* or other suitable maximum line size */
    int x = 0;
    while (fgets(line, sizeof(line), file)) {
      x++;
      if(x == rLine ) {
        memset(&lineTrimmed[0], 0, sizeof(lineTrimmed));
        strncpy(lineTrimmed, line, strlen(line)-1);
        return lineTrimmed;
      }
    }

    fclose(file);
  } else {
    printf("File does not exist \n");
  }

  return lineTrimmed;
}

int randNumber(int lower, int upper) {
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
	result = (rand() % (upper - lower + 1)) + lower;
  usleep(98765);

  return result;
}

int main(void) {
  int wordCount = 0;
  int size = 0;
  char words[wordCount][500];
  printf("Number of words: ");
  scanf("%d", &wordCount);

  while (wordCount < 2 || wordCount > 5) {
    printf("Invalid option. option should be between 2 and 5\n");
    printf("Re-enter number of words: ");
    scanf("%d", &wordCount);
  };

  for (int i=1; i<=wordCount; i++) {
    char word[500];
    int line = randNumber(0, 500);
    strcpy(word, readFile("./", randNumber(4, 7), line));
    strcpy(words[i], word);
    printf("%d %s\n", i, word);
  };

  printf("\nYour e-t-r password is: ");
  for (int i=1; i<=wordCount; i++)
    (i != wordCount) ? printf("%s-", words[i]) : printf("%s\n", words[i]);

  return 0;
}
