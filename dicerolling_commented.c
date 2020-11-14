//Calling library for the main functions.
#include <stdio.h>
//Calling library for the random function.
#include <stdlib.h>
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
  if (!ftime(&timer_msec)) {
      //ticking start
    timestamp_msec = ((long long int) timer_msec.time) * 1000ll +
                        (long long int) timer_msec.millitm;
  } else {
    timestamp_msec = -1;
  }
  //sorting a random number between 1 and limit (no of faces)
	srand ( timestamp_msec );
	/* result = rand() % limit; */
	result = rand() % limit + 1;
	//sleep for 1 sec
  usleep(98765);

  return result;
}

//Here we create a structure. it will contain the face number we check and the occurence of each of them.
struct Die {
  int face,occurrence;
};

//Calling the main function
int main(void) {
    //Declaring the variables we are going to use for the rolls and for setting the simulation rules.
  int faces, throws, total = 0;
  
    //Prompt the User the how many faces question.
  printf("Enter number of faces: ");
    //Looking after his answer. must be an Integer.
  scanf("%d", &faces);

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
    printf("%d throws are expected!\n",throws);
    
  //Struct in Die a new variable 'dash' .malloc for creating a dynamic array returning a pointer of the allocated value. 
  struct Die *dash = malloc(sizeof(struct Die) + throws);
  
  //For loop that will create an empty array the size of the number of faces the dice is.
  for (int i=1; i<=faces; i++) dash[i].occurrence = 0;
  
  //Informing the user the throws are generated.
  printf("\nGenerating throws: \n");
  
  //For that will loop for each unique throws.
  for (int i=1; i<=throws; i++) {
    //First the sort a random number . To make sure the random number is between 1 and the number of faces chosen,
    //the function take 1 argument , here faces . which will be assign to 'limit' in the function.
    total = randNumber(faces);
    //sorting the number for each time it loop.
    printf("%d\n", total);

    //Check if this position of the array(corresponding to a face)not null.
    if (dash[total].face) {
        //Occurence + 1
      dash[total].occurrence += 1;
    } else {
        //If face at position Total is null . face = total which is the rolled number and occurence + 1.
      dash[total].face = total;
      dash[total].occurrence = 1;
    }
  };

  printf("\n");
  //For loop that will print the occurence of each face . i++ to print each position in the array.
  for (int i=1; i<=faces; i++)
    printf("Occurences of %d: (%d) %.2f%%\n", i, dash[i].occurrence, dash[i].occurrence/(float)throws*100);

  return 0;
}
