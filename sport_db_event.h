/*
 Name: sport_db.c
 Purpose: Header file for the event program.
 Author: Shahob Zekria
*/

#ifndef SPORT_DB_EVENT
#define SPORT_DB_EVENT

// Import libraries.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Maximum length for event name.
#define MAX_EVENT_NAME_LENGTH (49+1)

// Event structure.
struct Event {
  int eventCode;
  char name[MAX_EVENT_NAME_LENGTH];
  int competitors;
  char gender;
  struct Event *nextEvent;
};

// Initalize database pointer.
extern struct Event *events;

// Function prototypes.
void insertEvent(void);
void searchEvents(void);
void updateEvent(void);
void printEvents(void);
void eraseEvent(int delCode);
void dumpEvents(void);
void restoreEvents(void);
void clearEventInput(void);
struct Event *eventInEvents(int code);

#endif
