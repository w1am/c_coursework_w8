#include <stdio.h> // fgets
#include <stdlib.h> // Malloc, atoi
#include <unistd.h> // Usleep
#include <sys/timeb.h> // timeb structure, ftime

// declaring a constant variable for size. one addition space for newline character
#define SIZE 4

int randNumber(int limit) {
  struct timeb timer_msec;
  int result;
  long long int timestamp_msec; /* timestamp in millisecond. */
  if (!ftime(&timer_msec)) { // typecasting time (good code practice)
    timestamp_msec = ((long long int) timer_msec.time) * 1000ll +
                        (long long int) timer_msec.millitm;
  } else {
    timestamp_msec = -1;
  }
	srand ( timestamp_msec ); // Initialize random number generator with seed timestamp_msec
	result = rand() % limit + 1;
  usleep(98765); // delay current for 98765 micro seconds

  printf("%d\n", result); // priting the results

  return result;
}

// This structure will use members, face and occurence as properties of a dice
struct Dice {
  int face;
  int occurrence;
};

void validateInteger(char identifier[SIZE]) {
  // Checking if identifier (faces or throws) is a valid integer. Otherwise we keep asking user to input again.
  while (atoi(identifier) == 0) {
    printf("\nInvalid number. Please re enter: ");
    fgets(identifier, SIZE, stdin);
  }
}

int main(void) {
  //Declaring the variables we are going to use for the rolls and for setting the simulation rules.
  int total = 0;
  char faces[SIZE], throws[SIZE];

  // Veryfying that input is respecting the rules. Dice must be between the range and will loop until the conditions are met.
  // Using atoi function to convert character string to integer;
  printf("========== Faces ===========\n");
  printf("Enter number of faces (2-24): ");
  fgets(faces, SIZE, stdin);
  validateInteger(faces); // Passing faces or throws as parameter to check if user input is of type integer

  while (atoi(faces) <= 1 || atoi(faces) >= 25) {
    printf("\nNumber of faces should be between 2 and 24. Please re-enter: ");
    fgets(faces, SIZE, stdin); // Read the line and store it in the buffer pointed by faces or throws and stops the read after newline character
    validateInteger(faces);
  }

  printf("%d faces are expected \n", atoi(faces));

  printf("\n========== Throws ===========\n");
  printf("Enter number of throws (2-499): ");
  fgets(throws, SIZE, stdin);
  validateInteger(throws);
  
  while (atoi(throws) <= 1 || atoi(throws) >= 500) {
    getchar(); // read trailing character from the buffer 
    printf("\nNumber of throws should be between 2 and 499. Please re-enter: ");
    fgets(throws, SIZE, stdin);
    validateInteger(throws);
  }

  printf("%d throws are expected\n", atoi(throws));

  // Initializing structure of type Dice and dynamically allocating the array with size throws;
  struct Dice *dice = malloc(atoi(throws) * sizeof(struct Dice));

  // Setting all occurence members to 0 for each face in our structure
  for (int i=1; i<=atoi(faces); i++) dice[i].occurrence = 0;

  printf("\nGenerating throws: \n");
  for (int i=1; i<=atoi(throws); i++) {
    // Generating a face number and assigning it to a variable called total
    total = (int)randNumber(atoi(faces));

    // using inline if statement to check if face at position total has a value already assigned.
    // If true increment occurence otherwise set it to 1
    dice[total].face ? dice[total].occurrence += 1 : (dice[total].occurrence = 1);
    dice[total].face = total; // update face at current position to total 
  };

  printf("\nFace \t Count \t Occurence \n"); // printing the results 
  for (int i=1; i<=atoi(faces); i++)
    // Calculating the occurrence and typecasting throws to avoid errors.
    printf("%d \t %d \t %.2f%%\n", i, dice[i].occurrence, dice[i].occurrence/(float)atoi(throws)*100);

  free(dice); // To prevent memory leak. not useful for this program but it is a good code practice.

  return 0;
}
