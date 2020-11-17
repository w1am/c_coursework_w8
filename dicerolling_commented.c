//Calling library for the main functions.
#include <stdio.h>
//Calling library for the random function.
#include <stdlib.h> // Malloc
//For Usleep function
#include <unistd.h>
//For time functions
#include <sys/timeb.h>

//Function for randomizing a number.
int randNumber(int limit) {
  //Creating a structure.
  struct timeb timer_msec;
  //Declaring variables.
  int result;
  long long int timestamp_msec; /* timestamp in millisecond. */
  //fetching the system time.
  if (!ftime(&timer_msec)) {
    timestamp_msec = ((long long int) timer_msec.time) * 1000ll +
                        (long long int) timer_msec.millitm;
  } else {
    timestamp_msec = -1;
  }
   //srand will sort new number for each program call.We use the system time because it is never the same in miliseconds.
   //so the seed of srand() is always different and the number are never the same.
	srand ( timestamp_msec );
	//sorting a random number between 1 and limit (no of faces) . 
	result = rand() % limit + 1;
	//sleep program for some millisecond just to make it neat.
  usleep(98765);
  //printing the value for each random number
  printf("%d\n", result);

  return result;
}

//Here we create a structure. it will contain the face value  and the occurence of each of them.
struct Dice {
  int face;
  int occurrence;
};

//Calling the main function
int main(void) {
  //Declaring the variables we are going to use for the rolls and for setting the simulation rules.
  int faces, throws, total = 0;
  
  //Prompt the User the how many faces question.
  printf("Enter number of faces: ");
  //Looking after his answer. must be an Integer.
  scanf("%i", &faces);

  //Here , we are veryfying that the user input is respecting the rules. the dice must be more than 1 and less than 25 faces.
  //the loop will go on until the 2 conditions mentioned before are met.
  while (faces <= 1 || faces >= 25) {
    //Tell the user that his answer is not good . Re-ask him another value.
    printf("\nNumber of faces should be between 1 and 25. Please re-enter: ");
    scanf("%i", &faces);
  };
  //This Statement show the user that his input have been correctly understood and will be used.
    printf("A %d faces dice will be used.\n", faces);

  //Same
  printf("Enter number of throws: ");
  scanf("%i", &throws);

  while (throws <= 1 || throws >= 500) {
    //Same
    printf("\nNumber of throws should be between 1 and 500. Please re-enter: ");
    scanf("%i", &throws);
  };
  //This Statement show the user that his input have been correctly understood and will be used.
  printf("%d throws are expected!",throws);
  
  //in Dice Structure , we allocate memory for dice , size of the throws * structures. 
  //it is use for a dynamic array size which will contain our occurences per face .
  struct Dice *dice = malloc(throws * sizeof(struct Dice));

  //For loop that will create an empty array the size of the number of faces the dice is.
  for (int i=1; i<=faces; i++) dice[i].occurrence = 0;
  
  //Informing the user the throws are generated.
  printf("\nGenerating throws: \n");
  
  //For that will loop for each unique throws.
  for (int i=1; i<=throws; i++) {
    //First the sort a random number . To make sure the random number is between 1 and the number of faces chosen,
    //the function take 1 argument , here faces . which will be assign to 'limit' in the function.
    total = randNumber(faces);
    
    //set face to rolled number at corresponding index.
    dice[total].face = total;
    //one-line if. Condition ? expression1(todo_if) : expression2(todo_else).
    //if dice[total].face is not null => dice[total].occurence += 1 . else => dice[total].occurrence = 1.
    dice[total].face ? dice[total].occurrence += 1 : (dice[total].occurrence = 1);
  };
  
   //For loop that will print the face, occurence, and percentage of each face . i++ to print each position in the array.
  printf("\nFace \t Count \t Occurence \n");
  for (int i=1; i<=faces; i++)
    printf("%d \t %d \t %.2f%%\n", i, dice[i].occurrence, dice[i].occurrence/(float)throws*100);
	
  //Declaring variable for mean median and mode.
  int mean=0,median=0;
 //looping what multiply each count with the face value and sum everything together.
  for (int i=1; i<=faces; i++)
    mean += dice[i].occurrence*i;
	
  int i=0;
  //check for the position of the median value in the array.
  while (median < (throws/2+1)) {
    median += dice[i].occurrence;
    ++i;
  };
 
  int higher = 0;
 //loop to find the higher count which is the mode.
  for(int i=1;i<faces;i++) {
    if(dice[i].occurrence > dice[higher].occurrence) {
      higher = dice[i].face;
    }
  }
  //printing the results.
  printf("--Statistics--\nMean: %.2f\nMedian: %d\nMode: %d", mean/(float)throws, dice[i-1].face,higher);
  
    
  //Once we finished with the allocated memory (malloc), we have to free it back.
  free(dice);
  

  return 0;
}
