#define _CRT_SECURE_NO_DEPRECATE
#define MAXFLIGHT 5
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
typedef struct tm tm;
typedef struct flight flight;
typedef struct people people;
typedef struct location location;

// Structure Deffination
struct people {
	char name[50];
	int age;
	int sex; // 0:Male 1:Female
};
struct flight {
	location *locate;
	char code[10];
	double speed;
	int num_people;
	people p;
};
struct location {
	int numHoop;
	char startnode[20][50];
	char endnode[20][50];
};

// Function prototypes
void getLogo();
int firstInterface();
void getTime(tm *timeInfo);
void getRoutine(location *data);
// void initFlight(flight *f, location *l);
flight* getFlight(location *l);

int main(void) {
	/// Initialize Variable & Pointer
	tm *timeInfo = (tm*)malloc(sizeof(tm));
	time_t now;
	int selectChoice;
	int exitStatus = 0;
	double seconds;

	time(&now);
	seconds = difftime(now, mktime(timeInfo));
	//------------ Routine Part

	flight *allFlight[MAXFLIGHT];
	//flight *f1 = (flight*)malloc(sizeof(flight));
	location *l1 = (location*)malloc(sizeof(location));

	getRoutine(l1);
	
	printf("\n%s-%s",l1->startnode[0],l1->endnode[l1->numHoop-1]);
	printf("\n%d",l1->numHoop);
	//initFlight(f1, l1);
	allFlight[0] = getFlight(l1);

	printf("\nStart location is :%s", allFlight[0]->locate->startnode[0]);
	printf("\nDesination is : %s", allFlight[0]->locate->endnode[allFlight[0]->locate->numHoop-1]);
	printf("\nThe number of passenger is %d peopoles", allFlight[0]->num_people);

	_getch();

	//----------------- Interfacing

	while (!exitStatus) {
		system("cls"); // <--- Clear Screen
		getTime(timeInfo); // <--- Show current time 
		getLogo();

		printf("\n-----Fight Tracking ver 1.0-----\n");

		selectChoice = firstInterface(); //  <--- Show select menu interface and return choice

		switch (selectChoice)
		{
		case '1':
			exitStatus = 1;
			break;
		case '2':
			exitStatus = 1;
			break;
		default:
			printf("\ntry agian!!\n");
			break;
		}
	}


	_getch();
	return 0;
}

void getLogo(){
	FILE *fp;
	char buff[80];

	fp = fopen("logo.txt", "r");

	while (fgets(buff,80, fp) != NULL) {
		printf("%s",buff);
	}
	fclose(fp);
}

void getRoutine(location *data) {
	FILE *fp;
	char s1[50];
	char s2[50];
	int distance;
	int num = 0;

	fp = fopen("location/l01.csv", "r");

	while (fscanf(fp, "%s %s %d", s1, s2, &distance) != EOF) {
		num++;
		printf("\n[%s-%s]-%d->%d", s1, s2, distance,num);
		
		strcpy(data->startnode[num-1],s1);
		strcpy(data->endnode[num-1],s2);

		data->numHoop = num;
	}
	fclose(fp);
}

//void initFlight(flight *f, location *l) {
//	FILE *fp;
//	char code[50];
//	double speed;
//	int numPeople;
//	int num = 0;
//
//	fp = fopen("flight/f01.csv", "r");
//
//	while (fscanf(fp, "%s %lf %d", code, &speed, &numPeople) != EOF) {
//		num++;
//		printf("\n[%s]-%.2lf->%d", code, speed, numPeople);
//		
//		strcpy(f->code, code);
//		f->locate = l;
//		f->num_people = numPeople;
//		f->speed = speed;
//	}
//	fclose(fp);
//}

flight* getFlight(location *l) {
	flight *f = (flight*)malloc(sizeof(flight));
	FILE *fp;
	char code[50];
	double speed;
	int numPeople;
	int num = 0;

	fp = fopen("flight/f01.csv", "r");

	while (fscanf(fp, "%s %lf %d", code, &speed, &numPeople) != EOF) {
		num++;
		printf("\n[%s]-%.2lf->%d", code, speed, numPeople);

		strcpy(f->code, code);
		f->locate = l;
		f->num_people = numPeople;
		f->speed = speed;
	}
	fclose(fp);
	return f;
}

int firstInterface() {
	int d;
	printf("\tChoose below option:\n");
	printf("\tPress -> '1' Start Flight Tracking\n");
	printf("\t         '2' Setting\n");
	d = _getch();
	return d;
}

void getTime(tm *timeInfo) {
	tm *info;
	time_t current_time;

	/* Obtain current time. */
	time(&current_time);
	info = localtime(&current_time);

	printf("\nCurrent local time and date: %s", asctime(info));

	timeInfo->tm_hour = info->tm_hour;
	timeInfo->tm_isdst = info->tm_isdst;
	timeInfo->tm_mday = info->tm_mday;
	timeInfo->tm_min = info->tm_min;
	timeInfo->tm_mon = info->tm_mon;
	timeInfo->tm_sec = info->tm_sec;
	timeInfo->tm_wday = info->tm_wday;
	timeInfo->tm_yday = info->tm_yday;
	timeInfo->tm_year = info->tm_year;
}

void settingMenu() {
	printf("Select the Flight that you want to setting");
	
}

void startCounter(flight f, tm timer) {

}