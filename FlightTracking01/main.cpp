#define _CRT_SECURE_NO_DEPRECATE
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
int firstInterface();
void getTime(tm *timeInfo);
void getRoutine(location *data);
void initFlight(flight *f, location *l);

int main(void) {
	/// Initialize Variable & Pointer
	tm *timeInfo = (tm*)malloc(sizeof(tm));
	int selectChoice;
	int exitStatus = 0;

	//------------ Routine Part

	//flight **allFlight;
	flight *f1 = (flight*)malloc(sizeof(flight));
	location *l1 = (location*)malloc(sizeof(location));

	getRoutine(l1);
	
	printf("\n%s-%s",l1->startnode[0],l1->endnode[l1->numHoop-1]);
	printf("\n%d",l1->numHoop);
	initFlight(f1, l1);
	printf("\nStart location is :%s", f1->locate->startnode[0]);
	printf("\nDesination is : %s",f1->locate->endnode[f1->locate->numHoop-1]);
	printf("\nThe number of passenger is %d peopoles",f1->num_people);

	//----------------- Interfacing

	while (!exitStatus) {
		system("cls"); // <--- Clear Screen
		getTime(timeInfo); // <--- Show current time 


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
		case '3':
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

void initFlight(flight *f, location *l) {
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
}

int firstInterface() {
	int d;
	printf("Choose below option:\n");
	printf("Press -> '1' get passenger status\n");
	printf("         '2' find flight detail by Start & Desination point\n");
	printf("         '3' find flight detail by using Flight's Code\n");
	d = _getch();
	return d;
}

void passengerStatus() {
	char name[50];
	printf("Enter Passenger's Name : ");
	scanf("%s", name);

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

void startCounter(flight f, tm timer) {

}