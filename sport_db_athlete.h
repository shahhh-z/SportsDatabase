/*
 Name: sport_db.c
 Purpose: Header file for the athlete program.
 Author: Shahob Zekria (251372860)
*/

#ifndef SPORT_DB_ATHLETE
#define SPORT_DB_ATHLETE

// Import libraries.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Maximum length for athlete name.
#define MAX_ATHLETE_NAME_LENGTH (49+1)

// Maximum length for nationality code.
#define MAX_NATIONALITY_LENGTH (3+1)

// Athlete structure.
struct Athlete {
  int athleteCode;
  char name[MAX_ATHLETE_NAME_LENGTH];
  int age;
  char nationality[MAX_NATIONALITY_LENGTH];
  struct Athlete *nextAthlete;
};

// Initalize database pointer.
extern struct Athlete *athletes;

// Function prototypes.
void insertAthlete(void);
void searchAthletes(void);
void updateAthlete(void);
void printAthletes(void);
void eraseAthlete(int delCode);
void dumpAthletes(void);
void restoreAthletes(void);
void clearAthleteInput(void);
struct Athlete *athleteInAthletes(int code);

#endif