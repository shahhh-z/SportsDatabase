sport_db: sport_db.o sport_db_event.o sport_db_athlete.o
					gcc -o sport_db sport_db.o sport_db_event.o sport_db_athlete.o

sport_db.o: sport_db.c sport_db.h sport_db_event.h sport_db_athlete.h
					gcc -c sport_db.c

sport_db_event.o: sport_db_event.c sport_db_event.h
					gcc -c sport_db_event.c

sport_db_athlete.o: sport_db_athlete.c sport_db_athlete.h
					gcc -c sport_db_athlete.c