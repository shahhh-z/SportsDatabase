/*
 Name: sport_db.c
 Purpose: Hosts a database of event information and
          contains functions that alter and display
          event information.
 Author: Shahob Zekria
*/


// Import header file.
#include "sport_db_event.h"


// Declare events database equal to null.
struct Event *events = NULL;


/************************************************************
* insertEvent: Prompts the user for the information of a    *
*              new event and inserts it into the database.  *
*************************************************************/
void insertEvent() {
  // Initalize new event.
  struct Event *newEvent;
  newEvent = malloc(sizeof(struct Event));
  if (newEvent == NULL) {
    printf("\tEvents database is full.\n");
    // Return to main.
    return;
  }

  // Prompt the user for the event code.
  printf("\tEnter event code: ");
  scanf("%d", &newEvent->eventCode);
  // Check to see if the code is valid.
  if (eventInEvents(newEvent->eventCode) != NULL) {
    printf("\tEvent already exists.\n");
    // Free up memory and return to main.
    free(newEvent);
    return;
  }

  // Prompt the user for the event name.
  printf("\tEnter event name: ");
  scanf(" %49[^\n]", &newEvent->name);
  clearEventInput();

  // Prompt the user for the number of competitors.
  printf("\tEnter number of competitors: ");
  scanf("%d", &newEvent->competitors);
  // Check to see if the number is valid.
  if (newEvent->competitors < 10 ||
  newEvent->competitors > 99) {
    printf("\tInvalid number.\n");
    // Free up memory and return to main.
    free(newEvent);
    return;
  }

  // Prompt the user for the gender of the event.
  printf("\tEnter gender: ");
  scanf(" %c", &newEvent->gender);
  // Check to see if the character is valid.
  if (newEvent->gender != 'M' && newEvent->gender != 'W' &&
  newEvent->gender != 'X') {
    printf("\tInvalid character.\n");
    // Free up memory and return to main.
    free(newEvent);
    return;
  }

  // Add the new event to the database.
  newEvent->nextEvent = events;
  events = newEvent;
}


/************************************************************
* searchEvents: Searches the database for the given event   *
*               using it's code and displays the rest of    *
*               the event's information.                    *
*************************************************************/
void searchEvents() {
  // Initialize code variable and loop pointer.
  int searchCode;
  struct Event *curr;

  // Prompt the user for the event code.
  printf("\tEnter event code: ");
  scanf("%d", &searchCode);

  // Search the database for the event.
  curr = eventInEvents(searchCode);
  // If the event does not exist, let the user know.
  if (curr == NULL) {
    printf("\tEvent does not exist.\n");
    // Return to main.
    return;
  }

  // Display the table header.
  printf("%s    %-49s    %s    %s\n", "Event Code",
  "Event Name", "Competitors", "Gender");
  // Display the event information.
  printf("%-10d    %-49s    %-11d    %-6c\n",
  curr->eventCode, curr->name, curr->competitors,
  curr->gender);
}


/************************************************************
* updateEvent: Updates the information of an existing event *
*              that is specified by the user.               *
*************************************************************/
void updateEvent() {
  // Create the replacement event and loop pointers.
  struct Event *updEvent, *curr, *prev;
  updEvent = malloc(sizeof(struct Event));
  if (updEvent == NULL) {
    printf("\tEvents database is full.\n");
    // Return to main.
    return;
  }

  // Prompt the user for the event code.
  printf("\tEnter event code: ");
  scanf("%d", &updEvent->eventCode);
  // Check to see if the code is valid.
  for (curr = events, prev = NULL;
  curr != NULL && updEvent->eventCode != curr->eventCode;
  prev = curr, curr = curr->nextEvent) {
    ;
  }
  if (curr == NULL) {
    printf("\tEvent does not exist.\n");
    // Free up memory and return to main.
    free(updEvent);
    return;
  }

  // Prompt the user for the event name.
  printf("\tEnter event name: ");
  scanf(" %49[^\n]", &updEvent->name);
  clearEventInput();

  // Prompt the user for the number of competitors.
  printf("\tEnter number of competitors: ");
  scanf("%d", &updEvent->competitors);
  // Check to see if the number is valid.
  if (updEvent->competitors < 10 ||
  updEvent->competitors > 99) {
    printf("\tInvalid number.\n");
    // Free up memory and return to main.
    free(updEvent);
    return;
  }

  // Prompt the user for the gender of the event.
  printf("\tEnter gender: ");
  scanf(" %c", &updEvent->gender);
  // Check to see if the character is valid.
  if (updEvent->gender != 'M' && updEvent->gender != 'W' &&
  updEvent->gender != 'X') {
    printf("\tInvalid character.\n");
    // Free up memory and return to main.
    free(updEvent);
    return;
  }

  // Update the database.
  // Event is at the start of the database.
  if (prev == NULL) {
    updEvent->nextEvent = curr->nextEvent;
    events = updEvent;
  }
  // Event is at the end of the database.
  else if (curr->nextEvent == NULL) {
    prev->nextEvent = updEvent;
  }
  // Event is in the middle of the database.
  else {
    updEvent->nextEvent = curr->nextEvent;
    prev->nextEvent = updEvent;
  }
  // Free up memory.
  free(curr);
}


/************************************************************
* printEvents: Goes through the database and prints out the *
*             information of each event in a table.         *
*************************************************************/
void printEvents() {
  // Display the table header.
  printf("%s    %-49s    %s    %s\n", "Event Code",
  "Event Name", "Competitors", "Gender");
  // Go through the events within the database.
  for (struct Event *curr = events; curr != NULL;
  curr = curr->nextEvent) {
    // Display the event information.
    printf("%-10d    %-49s    %-11d    %-6c\n",
    curr->eventCode, curr->name, curr->competitors,
    curr->gender);
  }
}


/************************************************************
* eraseEvent: Recieves an event code then goes through the  *
*             database and removes the event with the given *
*             code.                                         *
*************************************************************/
void eraseEvent(int delCode) {
  // Initalize loop pointers.
  struct Event *curr, *prev;

  // Check to see if an event exists for the code.
  for (curr = events, prev = NULL;
  curr != NULL && delCode != curr->eventCode;
  prev = curr, curr = curr->nextEvent) {
    ;
  }
  if (curr == NULL) {
    printf("\tEvent does not exist.\n");
    return;
  }

  // Update the database.
  // Event is at the start of the database.
  if (prev == NULL) {
    events = curr->nextEvent;
  }
  // Event is at the end of the database.
  else if (curr->nextEvent == NULL) {
    prev->nextEvent = NULL;
  }
  // Event is in the middle of the database.
  else {
    prev->nextEvent = curr->nextEvent;
  }
  // Free up memory.
  free(curr);
}


/************************************************************
* dumpEvents: Empty out the database into the given file.   *
*************************************************************/
void dumpEvents() {
  // Initalize file name array and pointer for while loop.
  char filename[100];
  struct Event *curr = events;

  // Prompt the user for the name of the file.
  printf("\tEnter filename to dump events: ");
  scanf(" %99[^\n]", filename);
  clearEventInput();

  // Open the file in writing mode.
  FILE *fp = fopen(filename, "w");
  if (fp == NULL) {
    printf("\tError opening file.\n");
    return;
  }

  // Write each event one at a time to the file.
  while (curr != NULL) {
    fwrite(curr, sizeof(struct Event), 1, fp);
    curr = curr->nextEvent;
  }

  // Close the file.
  fclose(fp);
  printf("\tEvents database fully dumped.\n");
}


/************************************************************
* restoreEvents: Restore the database using the given file. *
*************************************************************/
void restoreEvents() {
  // Initalize file name array and pointer for while loop.
  char filename[100];
  struct Event *curr;

  // Prompt the user for the name of the file.
  printf("\tEnter filename to restore events: ");
  scanf(" %99[^\n]", filename);
  clearEventInput();

  // Open the file in reading mode.
  FILE *fp = fopen(filename, "r");
  if (fp == NULL) {
    printf("\tError opening file.\n");
    return;
  }

  // Read the events one at a time.
  while (fread(curr, sizeof(struct Event),
  1, fp) == 1) {
    struct Event *newEvent;
    newEvent = malloc(sizeof(struct Event));
    if (newEvent == NULL) {
      printf("\tEvents database is full.\n");
      fclose(fp);
      return;
    }
    // Copy the information.
    newEvent->eventCode = curr->eventCode;
    strcpy(newEvent->name, curr->name);
    newEvent->competitors = curr->competitors;
    newEvent->gender = curr->gender;
    // Update pointers.
    newEvent->nextEvent = events;
    events = newEvent;
  }

  // Close the file.
  fclose(fp);
  printf("\tEvents database fully restored.\n");
}


/************************************************************
* clearEventInput: Clears excess input for next scanf call. *
*************************************************************/
// Initalize character variable.
void clearEventInput(void) {
  int character;
  // Use a while loop to read the remaining input characters.
  while ((character = getchar()) != '\n') {
    ;
  }
}


/************************************************************
* eventInEvents: Recieves an event code then searches the   *
*                database for the event with the code.      *
*                Returns pointer to event if found, null if *
*                not.                                       *
*************************************************************/
struct Event *eventInEvents(int code) {
  // Search through the database for the code.
  for (struct Event *curr = events; curr != NULL;
  curr = curr->nextEvent) {
    // If the code is in the database, return the pointer.
    if (code == curr->eventCode) {
      return curr;
    }
  }
  // If the code is not in the database, return null.
  return NULL;
}
