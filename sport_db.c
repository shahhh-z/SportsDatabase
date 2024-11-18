/*
 Name: sport_db.c
 Purpose: Main function that allows the user to perform
          operations on the event and athlete databases.
 Author: Shahob Zekria
*/


// Import header file.
#include "sport_db.h"


// Declare relationships database equal to null.
struct Relationship *rlships = NULL;


/************************************************************
* main: Performs operations on database based on the user's *
*       input. These operations are done through calls to   *
*       the other functions.                                *
*************************************************************/
int main() {
  // Initalize operation variables.
  char operation1, operation2;

  // Display the program header.
  printf("*************************\n" \
         "* 2024 Summer Olympics! *\n" \
         "*************************\n");

  while (true) {
    // Prompt the user for the operation.
    printf("\nEnter operation code (h for help): ");
    scanf(" %c", &operation1);

    switch (operation1) {
      case 'h':
        // Display all valid operations.
        printf("Main Operations:\n" \
               "\te - Perform an event operation.\n" \
               "\ta - Perform an athlete operation.\n" \
               "\tr - Perform a relationship operation.\n" \
               "\tq - Quit the program.\n" \
               "Event/Athlete Operations:\n" \
               "\ti - Insert a new event/athlete into the" \
               "database.\n" \
               "\ts - Search the event/athlete database.\n" \
               "\tu - Update the information of an" \
               "event/athlete.\n" \
               "\tp - Print out all events/athletes in the" \
               "database.\n" \
               "\te - Erase an event/athlete from the" \
               "database.\n" \
               "\td - Dump the event/athlete database into" \
               "a file.\n" \
               "\tr - Restore the event/athlete database " \
               "using a file.\n" \
               "Relationship Operations:\n" \
               "\ti - Insert a new event-athlete " \
               "relationship.\n" \
               "\ts - Search the relationship database.\n" \
               "\tp - Print out all relationships in the " \
               "database.\n" \
               "\te - Print out all events of an " \
               "athlete.\n" \
               "\ta - Print out all athletes of an " \
               "event.\n" \
               "\tx - Remove a relationship from the " \
               "database.\n"
               "\td - Dump the relationship database into " \
               "a file.\n" \
               "\tr - Restore the relationship database " \
               "using a file.\n");
        break;

      case 'e':
        // Prompt the user for the next operation.
        printf("Enter event operation code: ");
        scanf(" %c", &operation2);

        // Perform the second operation.
        switch (operation2) {
          case 'i':
            insertEvent();
            break;
          case 's':
            searchEvents();
            break;
          case 'u':
            updateEvent();
            break;
          case 'p':
            printEvents();
            break;
          case 'e':
            // Prompt the user for the event code.
            int delCode;
            printf("\tEnter event code: ");
            scanf("%d", &delCode);

            /*
            Call the erase event function if the event
            is not in the relationships database.
            */
            if (!eventInRlships(delCode)) {
              eraseEvent(delCode);
            }
            else {
              printf("\tEvent-athlete relationship " \
              "present, cannot erase event.\n");
            }
            break;
          case 'd':
            dumpEvents();
            break;
          case 'r':
            restoreEvents();
            break;
          default:
            printf("\tInvalid event operation.\n");
            // Prompt the user again.
            break;
        }
        break;
      
      case 'a':
        // Prompt the user for the next operation.
        printf("Enter athlete operation code: ");
        scanf(" %c", &operation2);

        // Perform the second operation.
        switch (operation2) {
          case 'i':
            insertAthlete();
            break;
          case 's':
            searchAthletes();
            break;
          case 'u':
            updateAthlete();
            break;
          case 'p':
            printAthletes();
            break;
          case 'e':
            // Prompt the user for the athlete code.
            int delCode;
            printf("\tEnter athlete code: ");
            scanf("%d", &delCode);

            /*
            Call the erase athlete function if the athlete
            is not in the relationships database.
            */
            if (!athleteInRlships(delCode)) {
              eraseAthlete(delCode);
            }
            else {
              printf("\tEvent-athlete relationship " \
              "present, cannot erase athlete.\n");
            }
            break;
          case 'd':
            dumpAthletes();
            break;
          case 'r':
            restoreAthletes();
            break;
          default:
            printf("\tInvalid athlete operation.\n");
            // Prompt the user again.
            break;
        }
        break;

      case 'r':
        // Prompt the user for the next operation.
        printf("Enter relationship operation code: ");
        scanf(" %c", &operation2);

        // Perform the second operation.
        switch (operation2) {
          case 'i':
            insertRlship();
            break;
          case 's':
            searchRlships();
            break;
          case 'p':
            printRlships();
            break;
          case 'e':
            printRlshipsE();
            break;
          case 'a':
            printRlshipsA();
            break;
          case 'x':
            eraseRlship();
            break;
          case 'd':
            dumpRlships();
            break;
          case 'r':
            restoreRlships();
            break;
          default:
            printf("\tInvalid relationship operation.\n");
            // Prompt the user again.
            break;
        }
        break;

      case 'q':
        // End the program.
        return 0;

      default:
        printf("\tInvalid operation.\n");
        // Prompt the user again.
        break;
    }
  }
}


/************************************************************
* insertRlship: Prompts the user for the information of a   *
*               new relationship and inserts it into the    *
*               database.                                   *
*************************************************************/
void insertRlship() {
  // Initalize new relationship.
  struct Relationship *newRlship;
  newRlship = malloc(sizeof(struct Relationship));
  if (newRlship == NULL) {
    printf("\tRelationships database is full.\n");
    // Return to main.
    return;
  }

  // Prompt the user for the relationship code.
  printf("\tEnter relationship code: ");
  scanf("%d", &newRlship->rlshipCode);
  // Check to see if the code is valid.
  if (rlshipInRlships(newRlship->rlshipCode) != NULL) {
    printf("\tRelationship already exists.\n");
    // Free up memory and return to main.
    free(newRlship);
    return;
  }

  // Prompt the user for the event code.
  printf("\tEnter event code: ");
  scanf("%d", &newRlship->eventCode);
  // Check to see if the code is valid.
  if (eventInEvents(newRlship->eventCode) == NULL) {
    printf("\tEvent does not exist.\n");
    // Free up memory and return to main.
    free(newRlship);
    return;
  }

  // Prompt the user for the athlete code.
  printf("\tEnter athlete code: ");
  scanf("%d", &newRlship->athleteCode);
  // Check to see if the code is valid.
  if (athleteInAthletes(newRlship->athleteCode) == NULL) {
    printf("\tAthlete does not exist.\n");
    // Free up memory and return to main.
    free(newRlship);
    return;
  }

  // Add the new relationship to the database.
  newRlship->nextRlship = rlships;
  rlships = newRlship;
}


/************************************************************
* searchRlships: Searches the database for the given        *
*               relationship using it's code and displays   *
*               the rest of the relationship's information. *
*************************************************************/
void searchRlships() {
  // Initialize code variable and loop pointer.
  int searchCode;
  struct Relationship *curr;

  // Prompt the user for the relationship code.
  printf("\tEnter relationship code: ");
  scanf("%d", &searchCode);

  // Search the database for the relationship.
  curr = rlshipInRlships(searchCode);
  // If the relationship does not exist, let the user know.
  if (curr == NULL) {
    printf("\tRelationship does not exist.\n");
    // Return to main.
    return;
  }

  // Display the table header.
  printf("%s    %s    %s\n", "Relationship Code",
  "Event Code", "Athlete Code");
  // Display the relationship information.
  printf("%-17d    %-10d    %-12d\n",
  curr->rlshipCode, curr->eventCode, curr->athleteCode);
}


/************************************************************
* printRlships: Goes through the database and prints out    *
*               the information of each relationship in a   *
*               table.                                      *
*************************************************************/
void printRlships(){
  // Display the table header.
  printf("%s    %s    %s\n", "Relationship Code",
  "Event Code", "Athlete Code");
  // Go through the relationships within the database.
  for (struct Relationship *curr = rlships;
  curr != NULL; curr = curr->nextRlship) {
    // Display the relationship information.
    printf("%-17d    %-10d    %-12d\n",
    curr->rlshipCode, curr->eventCode, curr->athleteCode);
  }
}


/************************************************************
* printRlshipsE: Goes through the database and prints out   *
*                all events associated with an athlete.     *
*************************************************************/
void printRlshipsE() {
  // Initalize code variable.
  int athleteCode;

  // Prompt the user for the athlete code.
  printf("\tEnter athlete code: ");
  scanf("%d", &athleteCode);

  // Check to see if the athlete exists.
  if (athleteInAthletes(athleteCode) == NULL) {
    printf("\tAthlete does not exist.\n");
    // Return to main.
    return;
  }

  // Display the table header.
  printf("%s    %s    %s\n", "Relationship Code",
  "Event Code", "Athlete Code");
  // Go through the relationships within the database.
  for (struct Relationship *curr = rlships;
  curr != NULL; curr = curr->nextRlship) {
    // If the athlete is in a relationship, display it.
    if (athleteCode == curr->athleteCode) {
      // Display the relationship information.
      printf("%-17d    %-10d    %-12d\n",
      curr->rlshipCode, curr->eventCode, curr->athleteCode);
    }
  }
}


/************************************************************
* printRlshipsA: Goes through the database and prints out   *
*                all athletes associated with an event.     *
*************************************************************/
void printRlshipsA() {
  // Initalize code variable.
  int eventCode;

  // Prompt the user for the athlete code.
  printf("\tEnter event code: ");
  scanf("%d", &eventCode);

  // Check to see if the event exists.
  if (eventInEvents(eventCode) == NULL) {
    printf("\tEvent does not exist.\n");
    // Return to main.
    return;
  }

  // Display the table header.
  printf("%s    %s    %s\n", "Relationship Code",
  "Event Code", "Athlete Code");
  // Go through the relationships within the database.
  for (struct Relationship *curr = rlships;
  curr != NULL; curr = curr->nextRlship) {
    // If the event is in a relationship, display it.
    if (eventCode == curr->eventCode) {
      // Display the relationship information.
      printf("%-17d    %-10d    %-12d\n",
      curr->rlshipCode, curr->eventCode, curr->athleteCode);
    }
  }
}


/************************************************************
* eraseRlship: Goes through the database and removes the    *
*              relationship with the given code.            *
*************************************************************/
void eraseRlship() {
  // Initalize loop pointers.
  int delCode;
  struct Relationship *curr, *prev;

  // Prompt the user for the relationship code.
  printf("\tEnter relationship code: ");
  scanf("%d", &delCode);
  
  // Check to see if a relationship exists for the code.
  for (curr = rlships, prev = NULL;
  curr != NULL && delCode != curr->rlshipCode;
  prev = curr, curr = curr->nextRlship) {
    ;
  }
  if (curr == NULL) {
    printf("\tRelationship does not exist.\n");
    return;
  }

  // Update the database.
  // Relationship is at the start of the database.
  if (prev == NULL) {
    rlships = curr->nextRlship;
  }
  // Relationship is at the end of the database.
  else if (curr->nextRlship == NULL) {
    prev->nextRlship = NULL;
  }
  // Relationship is in the middle of the database.
  else {
    prev->nextRlship = curr->nextRlship;
  }
  // Free up memory.
  free(curr);
}


/************************************************************
* dumpRlships: Empty out the database into the given file.  *
*************************************************************/
void dumpRlships() {
  // Initalize file name array and pointer for while loop.
  char filename[100];
  struct Relationship *curr = rlships;

  // Prompt the user for the name of the file.
  printf("\tEnter filename to dump events: ");
  scanf(" %99[^\n]", filename);
  /*
  Can call this function instead of creating new one to
  clear excess input.
  */ 
  clearEventInput();

  // Open the file in writing mode.
  FILE *fp = fopen(filename, "w");
  if (fp == NULL) {
    printf("\tError opening file.\n");
    return;
  }

  // Write each relationship one at a time to the file.
  while (curr != NULL) {
    fwrite(curr, sizeof(struct Relationship), 1, fp);
    curr = curr->nextRlship;
  }

  // Close the file.
  fclose(fp);
  printf("\tRelationships database fully dumped.\n");
}


/************************************************************
* restoreRlships: Restore the database using the given file.*
*************************************************************/
void restoreRlships() {
  // Initalize file name array and pointer for while loop.
  char filename[100];
  struct Relationship *curr;

  // Prompt the user for the name of the file.
  printf("\tEnter filename to restore relationships: ");
  scanf(" %99[^\n]", filename);
  /*
  Can call this function instead of creating new one to
  clear excess input.
  */ 
  clearEventInput();

  // Open the file in reading mode.
  FILE *fp = fopen(filename, "r");
  if (fp == NULL) {
    printf("\tError opening file.\n");
    return;
  }

  // Read the relationships one at a time.
  while (fread(curr, sizeof(struct Relationship),
  1, fp) == 1) {
    struct Relationship *newRlship;
    newRlship = malloc(sizeof(struct Relationship));
    if (newRlship == NULL) {
      printf("\tRelationships database is full.\n");
      fclose(fp);
      return;
    }
    // Copy the information.
    newRlship->rlshipCode = curr->rlshipCode;
    newRlship->eventCode = curr->eventCode;
    newRlship->athleteCode = curr->athleteCode;
    // Update pointers.
    newRlship->nextRlship = rlships;
    rlships = newRlship;
  }

  // Close the file.
  fclose(fp);
  printf("\tRelationships database fully restored.\n");
}


/************************************************************
* eventInRlships: Recieves an event code then searches the  *
*                 relationships database for the event with *
*                 the code. Returns true if event is found, *
*                 false if not.                             *
*************************************************************/
_Bool eventInRlships(int code) {
  // Search through the database for the code.
  for (struct Relationship *curr = rlships;
  curr != NULL; curr = curr->nextRlship) {
    // If the code is in the database, return the pointer.
    if (code == curr->eventCode) {
      return true;
    }
  }
  // If the code is not in the database, return null.
  return false;
}


/************************************************************
* athleteInRlships: Recieves an athlete code then searches  *
*                   the relationships database for the      *
*                   athlete with the code. Returns true if  *
*                   athlete is found, false if not.         *
*************************************************************/
_Bool athleteInRlships(int code) {
  // Search through the database for the code.
  for (struct Relationship *curr = rlships;
  curr != NULL; curr = curr->nextRlship) {
    // If the code is in the database, return the pointer.
    if (code == curr->athleteCode) {
      return true;
    }
  }
  // If the code is not in the database, return null.
  return false;
}


/************************************************************
* rlshipInRlships: Recieves a relationship code then        *
*                  searches the database for the            *
*                  relationship with the code. Returns      *
*                  pointer to relationship if found, null   *
*                  if not.                                  *
*************************************************************/
struct Relationship *rlshipInRlships(int code) {
  // Search through the database for the code.
  for (struct Relationship *curr = rlships;
  curr != NULL; curr = curr->nextRlship) {
    // If the code is in the database, return the pointer.
    if (code == curr->rlshipCode) {
      return curr;
    }
  }
  // If the code is not in the database, return null.
  return NULL;
}
