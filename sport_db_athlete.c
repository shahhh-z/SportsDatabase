/*
 Name: sport_db.c
 Purpose: Hosts a database of athlete information and
          contains functions that alter and display
          athlete information.
 Author: Shahob Zekria (251372860)
*/


// Import header file.
#include "sport_db_athlete.h"


// Declare athletes database equal to null.
struct Athlete *athletes = NULL;


/************************************************************
* insertAthlete: Prompts the user for the information of a  *
*                new athlete and inserts it into the        *
*                database.                                  *
*************************************************************/
void insertAthlete() {
  // Initalize new athlete.
  struct Athlete *newAthlete;

  // Allocate size to new athlete.
  newAthlete = malloc(sizeof(struct Athlete));
  if (newAthlete == NULL) {
    printf("\tAthletes database is full.\n");
    // Return to main.
    return;
  }

  // Prompt the user for the athlete code.
  printf("\tEnter athlete code: ");
  scanf("%d", &newAthlete->athleteCode);
  // Check to see if the code is valid.
  if (athleteInAthletes(newAthlete->athleteCode) != NULL) {
    printf("\tAthlete already exists.\n");
    // Free up memory and return to main.
    free(newAthlete);
    return;
  }

  // Prompt the user for the athlete name.
  printf("\tEnter athlete name: ");
  scanf(" %49[^\n]", &newAthlete->name);
  clearAthleteInput();

  // Prompt the user for the athlete's age.
  printf("\tEnter age: ");
  scanf("%d", &newAthlete->age);
  // Check to see if the age is valid.
  if (newAthlete->age < 14 ||
  newAthlete->age > 120) {
    printf("\tInvalid age.\n");
    // Free up memory and return to main.
    free(newAthlete);
    return;
  }

  // Prompt the user for the athlete's nationality.
  printf("\tEnter nationality: ");
  scanf(" %3[^\n]", &newAthlete->nationality);
  clearAthleteInput();
  // Check to see if the nationlity is valid.
  for (char *currChar = newAthlete->nationality;
  currChar < newAthlete->nationality +
  MAX_NATIONALITY_LENGTH - 1; currChar++) {
    // Check to see that the current character is valid.
    if (!isupper(*currChar) || (*currChar) == '\n') {
      printf("\tInvalid nationality.\n");
      // Free up memory and return to main.
      free(newAthlete);
      return;
    }
  }

  // Add the new athlete to the database.
  newAthlete->nextAthlete = athletes;
  athletes = newAthlete;
}


/************************************************************
* searchAthletes: Searches the database for the given       *
*                 athlete using it's code and displays the  * 
*                 rest of the athlete's information.        *
*************************************************************/
void searchAthletes() {
  // Initialize code variable and loop pointer.
  int searchCode;
  struct Athlete *curr;

  // Prompt the user for the athlete code.
  printf("\tEnter athlete code: ");
  scanf("%d", &searchCode);

  // Search the database for the athlete.
  curr = athleteInAthletes(searchCode);
  // If the athlete does not exist, let the user know.
  if (curr == NULL) {
    printf("\tAthlete does not exist.\n");
    // Return to main.
    return;
  }

  // Display the table header.
  printf("%s    %-49s    %s    %s\n", "Athlete Code",
  "Athlete Name", "Age", "Nationality");
  // Display the athlete information.
  printf("%-12d    %-49s    %-3d    %-11s\n",
  curr->athleteCode, curr->name, curr->age,
  curr->nationality);
}


/************************************************************
* updateAthlete: Updates the information of an existing     *
*                athlete that is specified by the user.     *
*************************************************************/
void updateAthlete() {
  // Create the replacement athlete and loop pointers.
  struct Athlete *updAthlete, *curr, *prev;
  
  // Allocate size to replacement athlete.
  updAthlete = malloc(sizeof(struct Athlete));
  if (updAthlete == NULL) {
    printf("\tAthletes database is full.\n");
    // Return to main.
    return;
  }

  // Prompt the user for the athlete code.
  printf("\tEnter athlete code: ");
  scanf("%d", &updAthlete->athleteCode);
  // Check to see if the code is valid.
  for (curr = athletes, prev = NULL;
  curr != NULL &&
  updAthlete->athleteCode != curr->athleteCode;
  prev = curr, curr = curr->nextAthlete) {
    ;
  }
  if (curr == NULL) {
    printf("\tAthlete does not exist.\n");
    // Free up memory and return to main.
    free(updAthlete);
    return;
  }

  // Prompt the user for the athlete name.
  printf("\tEnter athlete name: ");
  scanf(" %49[^\n]", &updAthlete->name);
  clearAthleteInput();

  // Prompt the user for the athlete's age.
  printf("\tEnter age: ");
  scanf("%d", &updAthlete->age);
  // Check to see if the age is valid.
  if (updAthlete->age < 14 ||
  updAthlete->age > 120) {
    printf("\tInvalid age.\n");
    // Free up memory and return to main.
    free(updAthlete);
    return;
  }

  // Prompt the user for the athlete's nationality.
  printf("\tEnter nationality: ");
  scanf(" %3[^\n]", &updAthlete->nationality);
  clearAthleteInput();
  // Check to see if the nationlity is valid.
  for (char *currChar = updAthlete->nationality;
  currChar < updAthlete->nationality +
  MAX_NATIONALITY_LENGTH - 1; currChar++) {
    // Check to see that the current character is valid.
    if (!isupper(*currChar) || (*currChar) == '\n') {
      printf("\tInvalid nationality.\n");
      // Free up memory and return to main.
      free(updAthlete);
      return;
    }
  }

  // Update the database.
  // Athlete is at the start of the database.
  if (prev == NULL) {
    updAthlete->nextAthlete = curr->nextAthlete;
    athletes = updAthlete;
  }
  // Athlete is at the end of the database.
  else if (curr->nextAthlete == NULL) {
    prev->nextAthlete = updAthlete;
  }
  // Athlete is in the middle of the database.
  else {
    updAthlete->nextAthlete = curr->nextAthlete;
    prev->nextAthlete = updAthlete;
  }
  // Free up memory.
  free(curr);
}


/************************************************************
* printAthletes: Goes through the database and prints out   *
*                the information of each athlete in a       *
*                table.                                     *
*************************************************************/
void printAthletes() {
  // Display the table header.
  printf("%s    %-49s    %s    %s\n", "Athlete Code",
  "Athlete Name", "Age", "Nationality");
  // Go through the athletes within the database.
  for (struct Athlete *curr = athletes; curr != NULL;
  curr = curr->nextAthlete) {
    // Display the athlete information.
    printf("%-12d    %-49s    %-3d    %-11s\n",
    curr->athleteCode, curr->name, curr->age,
    curr->nationality);
  }
}


/************************************************************
* eraseAthlete: Recieves an athlete code then goes through  *
*               the database and removes the athlete with   *
*               the given code.                             *
*************************************************************/
void eraseAthlete(int delCode) {
  // Initalize loop pointers.
  struct Athlete *curr, *prev;

  // Check to see if an athlete exists for the code.
  for (curr = athletes, prev = NULL;
  curr != NULL && delCode != curr->athleteCode;
  prev = curr, curr = curr->nextAthlete) {
    ;
  }
  if (curr == NULL) {
    printf("\tAthlete does not exist.\n");
    return;
  }

  // Update the database.
  // Athlete is at the start of the database.
  if (prev == NULL) {
    athletes = curr->nextAthlete;
  }
  // Athlete is at the end of the database.
  else if (curr->nextAthlete == NULL) {
    prev->nextAthlete = NULL;
  }
  // Athlete is in the middle of the database.
  else {
    prev->nextAthlete = curr->nextAthlete;
  }
  // Free up memory.
  free(curr);
}


/************************************************************
* dumpAthletes: Empty out the database into the given file. *
*************************************************************/
void dumpAthletes() {
  // Initalize file name array and pointer for while loop.
  char filename[100];
  struct Athlete *curr = athletes;

  // Prompt the user for the name of the file.
  printf("\tEnter filename to dump athletes: ");
  scanf("%99s", filename);

  // Open the file in writing mode.
  FILE *fp = fopen(filename, "wb");
  if (fp == NULL) {
    printf("\tError opening file.\n");
    return;
  }

  // Write each athlete one at a time to the file.
  while (curr != NULL) {
    fwrite(curr, sizeof(struct Athlete), 1, fp);
    curr = curr->nextAthlete;
  }

  // Close the file.
  fclose(fp);
  printf("\tAthletes database fully dumped.\n");
}


/************************************************************
* restoreAthletes: Restore the database using the given     *
*                  file.                                    *
*************************************************************/
void restoreAthletes() {
  // Initalize file name array and pointer for while loop.
  char filename[100];
  struct Athlete *curr;

  // Prompt the user for the name of the file.
  printf("\tEnter filename to restore athletes: ");
  scanf("%99s", filename);

  // Open the file in reading mode.
  FILE *fp = fopen(filename, "rb");
  if (fp == NULL) {
    printf("\tError opening file.\n");
    return;
  }

  // Read the athletes one at a time.
  while (fread(curr, sizeof(struct Athlete), 1, fp) == 1) {
    struct Athlete *newAthlete;
    newAthlete = malloc(sizeof(struct Athlete));
    if (newAthlete == NULL) {
      printf("\tAthletes database is full.\n");
      fclose(fp);
      return;
    }
    // Copy the information.
    newAthlete->athleteCode = curr->athleteCode;
    strcpy(newAthlete->name, curr->name);
    newAthlete->age = curr->age;
    strcpy(newAthlete->nationality, curr->nationality);
    // Update pointers.
    newAthlete->nextAthlete = athletes;
    athletes = newAthlete;
  }

  // Close the file.
  fclose(fp);
  printf("\tAthletes database fully restored.\n");
}


/************************************************************
* clearAthleteInput: Clears excess input for next scanf     *
*                    call.                                  *
*************************************************************/
void clearAthleteInput(void) {
  // Initalize character variable.
  int character;
  // Use a while loop to read the remaining input characters.
  while ((character = getchar()) != '\n') {
    ;
  }
}


/************************************************************
* athleteInAthletes: Recieves an athlete code then searches *
*                    for the athlete with the code. Returns *
*                    pointer to athlete if found, null if   *
*                    not.                                   *
*************************************************************/
struct Athlete *athleteInAthletes(int code) {
  // Search through the database for the code.
  for (struct Athlete *curr = athletes; curr != NULL;
  curr = curr->nextAthlete) {
    // If the code is in the database, return the pointer.
    if (code == curr->athleteCode) {
      return curr;
    }
  }
  // If the code is not in the database, return null.
  return NULL;
}