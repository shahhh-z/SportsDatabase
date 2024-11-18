/*
 Name: sport_db.c
 Purpose: Header file for main program.
 Author: Shahob Zekria
*/

#ifndef SPORT_DB
#define SPORT_DB

// Import libraries and header files.
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "sport_db_event.h"
#include "sport_db_athlete.h"

// Relationship structure.
struct Relationship {
  int rlshipCode;
  int eventCode;
  int athleteCode;
  struct Relationship *nextRlship;
};

// Initalize database pointer.
extern struct Relationship *rlships;

// Function prototypes.
void insertRlship();
void searchRlships();
void printRlships();
void printRlshipsE();
void printRlshipsA();
void eraseRlship();
void dumpRlships();
void restoreRlships();
_Bool eventInRlships(int code);
_Bool athleteInRlships(int code);
struct Relationship *rlshipInRlships(int code);

#endif
