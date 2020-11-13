//Calling library for the main functions.
#include <stdio.h>
//Calling library for the random function.
#include <stdlib.h>
//
#include <unistd.h>
//
#include <sys/timeb.h>

int randNumber(int limit) 
{
    struct timeb timer_msec;
    int result;
    long long int timestamp_msec; /* timestamp in millisecond. */
  
    if (!ftime(&timer_msec)) 
    {
        timestamp_msec = ((long long int) timer_msec.time) * 1000ll +
                            (long long int) timer_msec.millitm;
    } 
    else 
    {
        timestamp_msec = -1;
    }
    
	srand ( timestamp_msec );
	/* result = rand() % limit; */
	result = rand() % limit + 1;
    usleep(98765);

  return result;
}
//Here we create a structure. it will contain the face number we check and the occurence of each of them.
struct summary
{
  int arrayface, occurence;
};

//Calling the main function
int main(void) 
{
    //Declaring the variables we are going to use for the rolls and for setting the simulation rules.
    int faces = 0,throws = 0,random_number,i;
    
    //Prompt the User the how many faces question.
    printf("How many faces the dice is? ");
    //Looking after his answer. must be an Integer.
    scanf("%i", &faces);

    //Here , we are veryfying that the user input is respecting the rules. the dice must be more than 1 and less than 25 faces.
    //the loop will go on until the 2 conditions mentioned before are met.
    while (faces <= 1 || faces >= 25) 
    {
        //Tell the user that his answer is not good . Re-ask him another value.
        printf("\nNumber of faces should be between 1 and 25. Please re-enter: ");
        scanf("%i", &faces);
    };
  
    //This Statement show the user that his input have been correctly understood and will be used.
    printf("A %d faces dice will be used.\n", faces);

    //Prompt the User the how many throws question.
    printf("How many throw would you like to be performed? ");
    scanf("%i", &throws);
    
    //Here , we are veryfying that the user input is respecting the rules. the dice must be throw more than 1 and less than 500 faces.
    //the loop will go on until the 2 conditions mentioned before are met.
    while (throws <= 1 || throws >= 500)
    {
        //Tell the user that his answer is not good . Re-ask him another value.
        printf("\nNumber of throws should be between 1 and 500. Please re-enter: ");
        scanf("%i", &throws);
    };
  
    //This Statement show the user that his input have been correctly understood and will be used.
    printf("%d throws are expected!\n",throws);

    //Struct in summary a new variable 'dash' .
    struct summary dash[throws];

    //For loop that will create an empty array the size of the number of faces the dice is.
    for (i=1; i<=faces; i++) 
    {
        dash[i].occurrence = 0;
    }
    
    //Informing the user the throws are generated.
    printf("Generating throws: \n");
    
    //For that will loop for each unique throws .
    for (i=1; i<=throws; i++) 
    {
        //First the sort a random number . To make sure the random number is between 1 and the number of faces chosen,
        //the function take 1 argument , here faces . which will be assign to 'limit' in the function.
        random_number = randNumber(faces);
        //sorting the number for each time it loop.
        printf("%d\n", random_number);
        
        
        if (dash[random_number].arrayface > 0) 
        {
            dash[random_number].occurrence += 1;
        } 
        else 
        {
            dash[random_number].arrayface = random_number;
            dash[random_number].occurrence = 1;
        }
    };
    //For loop that will print the occurence of each face . i++ to print each position in the array.
    for (i=1; i<=faces; i++) 
    {
        printf("Occurences of %d: (%d) %.2f%%\n", i, dash[i].occurrence, dash[i].occurrence/(float)throws*100);
    };
    //ending the program.
    return 0;
}
