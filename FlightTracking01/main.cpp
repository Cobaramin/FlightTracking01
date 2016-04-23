#define _CRT_SECURE_NO_DEPRECATE
#define MAXFLIGHT 50
#define NUM 4
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
struct flight {
	location *locate;
	char code[10];
	double speed;
};
struct location {
	int numHoop;
	double distance[20];
	double distancec[20];
	char startnode[20][50];
	char endnode[20][50];
};

// Function prototypes
void getLogo();
int firstInterface();
void getTime(tm *timeInfo);
location* getRoutine(int numfile);
flight* getFlight(int numfile, location *l);
void settingMenu(flight *allf[]);
double getAllDistance(flight *f);
void loadingBar(double time, double maxTime);
void loadingLocation(double time, double maxTime, flight *f);
void selectFlight(flight **allf, int status[]);
void printSelector(flight **allf, int status[]);
int getHitTime(int status[]);
void clearHitTime(int status[]);

int main(void) {
	/// Initialize Variable & Pointer
	tm *timeInfo = (tm*)malloc(sizeof(tm));
	time_t now;
	int selectChoice;
	int exitStatus = 0;
	double seconds;
	double maxTime[NUM];
	double timer[NUM];
	int status[NUM] = { 0 };
	int percent;
	int temp;
	double totalDistance;
	char c;


	//------------ Routine Part

	flight *allFlight[MAXFLIGHT];
	location *allLocation[MAXFLIGHT];

	// Get All Locations form File
	for (int i = 0; i < NUM; i++) {
		allLocation[i] = getRoutine(i + 1);
	}
	// Get All Flights form file
	for (int i = 0; i < NUM; i++) {
		allFlight[i] = getFlight(i + 1, allLocation[i]);
	}



	//----------------- Interfacing

	while (!exitStatus) {
		system("cls"); // <--- Clear Screen
		getLogo();
		getTime(timeInfo); // <--- Show current time 

		printf("\n-----Fight Tracking ver 1.0-----\n");

		selectChoice = firstInterface(); //  <--- Show select menu interface and return choice
										 //int dataIn;
		switch (selectChoice)
		{
		case '1':
			getTime(timeInfo);
			selectFlight(allFlight, status);
			do {
				system("cls");
				time(&now);
				seconds = difftime(now, mktime(timeInfo));

				printf("\t____Start Fligth tracking____\n");
				printf("(Presss Any key on your keyboard to terminate this process)\n");

				for (int i = 0; i < NUM; i++) {
					if (status[i] == 1) {
						totalDistance = getAllDistance(allFlight[i]);
						maxTime[i] = totalDistance / allFlight[i]->speed * 60;
						timer[i] = (int)seconds % ((int)maxTime[i] + 1);
						for (int j = 0; j < 80; j++) {
							printf("%c", 209);
						}
						printf("\n\t%s ,%.2lfkm/hr ,%dkm\n", allFlight[i]->code, allFlight[i]->speed, (int)totalDistance);
						printf("\t%s - %s\n", allFlight[i]->locate->startnode[0], allFlight[i]->locate->endnode[allFlight[i]->locate->numHoop - 1]);
						loadingBar(timer[i], maxTime[i]);
						loadingLocation(timer[i], maxTime[i], allFlight[i]);
						percent = timer[i] / (int)maxTime[i] * 100;
						printf("Time remaining %.2lfmins\t\t\t\t\t\t[%d%c]\n", maxTime[i] - timer[i], percent, '%');
						for (int j = 0; j < 80; j++) {
							printf("%c", 207);
						}printf("\n");
					}
				}

				//// Delay
				for (int i = 0; i < 20000; i++) {
					for (int j = 0; j < 25000; j++);
				}
			} while (!_kbhit());
			clearHitTime(status);

			break;
		case '2':

			settingMenu(allFlight);
			break;
		case '3':
			exitStatus = 1;
			break;
		default:
			printf("\ntry agian!!\n");
			break;
		}
	}
	system("cls");
	printf("Bye.....\n");
	//// Delay
	for (int i = 0; i < 30000; i++) {
		for (int j = 0; j < 30000; j++);
	}

	return 0;
}

void getLogo() {
	FILE *fp;
	char buff[80];

	fp = fopen("logo.txt", "r");

	while (fgets(buff, 80, fp) != NULL) {
		printf("%s", buff);
	}
	fclose(fp);
}

location* getRoutine(int numfile) {
	location *l = (location*)malloc(sizeof(location));
	FILE *fp;
	char s1[50];
	char s2[50];
	double distance;
	double distancec;
	int num = 0;
	char str[20];

	sprintf(str, "location/l%.2d.csv", numfile);

	fp = fopen(str, "r");

	if (fp == NULL)
	{
		perror(str);
		_getch();
		exit(EXIT_FAILURE);
	}

	while (fscanf(fp, "%s %s %lf %lf", s1, s2, &distance, &distancec) != EOF) {
		num++;

		strcpy(l->startnode[num - 1], s1);
		strcpy(l->endnode[num - 1], s2);
		l->distance[num - 1] = distance;
		l->distancec[num - 1] = distancec;
		l->numHoop = num;
	}
	fclose(fp);
	return l;
}

flight* getFlight(int numfile, location *l) {
	flight *f = (flight*)malloc(sizeof(flight));
	FILE *fp;
	char code[50];
	double speed;
	int num = 0;
	char str[20];

	sprintf(str, "flight/f%.2d.csv", numfile);

	fp = fopen(str, "r");

	if (fp == NULL)
	{
		perror(str);
		_getch();
		exit(EXIT_FAILURE);
	}

	while (fscanf(fp, "%s %lf %d", code, &speed) != EOF) {
		num++;

		strcpy(f->code, code);
		f->locate = l;
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
	printf("\t         '3' Exit\n");
	d = _getch();
	return d;
}

void getTime(tm *timeInfo) {
	tm *info;
	time_t current_time;

	/* Obtain current time. */
	time(&current_time);
	info = localtime(&current_time);

	printf("\nCurrent local time and date: %s\n", asctime(info));

	*timeInfo = *info;
}

void settingMenu(flight *allf[]) {
	int input;
	char code[50];
	double speed;
	system("cls");
	printf("Select the Flight that you want to setting\n");
	for (int i = 0; i < NUM; i++) {
		printf("\t%d : %s %s-%s\n", i + 1, allf[i]->code, allf[i]->locate->startnode[0], allf[i]->locate->endnode[allf[i]->locate->numHoop - 1]);
	}
	do {
		input = _getch();
	} while (input <= '0' || input > 48 + NUM);

	printf("Flight's Code [%s] : ", allf[input - 49]->code);
	scanf("%s", code);
	printf("Flight's speed [%.2lf] : ", allf[input - 49]->speed);
	scanf("%lf", &speed);

	// Update Structure Data
	strcpy(allf[input - 49]->code, code);
	allf[input - 49]->speed = speed;

	// Write Changed Data to Files
	FILE *fp;
	char str[20];
	sprintf(str, "flight/f%.2d.csv", input - 48);

	fp = fopen(str, "w+");

	if (fp == NULL)
	{
		perror(str);
		_getch();
		exit(EXIT_FAILURE);
	}
	fprintf(fp, "%s %.2lf %d", code, speed);
	fclose(fp);

	printf("Update Completed.....\n");
	//// Delay
	for (int i = 0; i < 30000; i++) {
		for (int j = 0; j < 30000; j++);
	}
}

double getAllDistance(flight *f) {
	double totalDistance = 0;
	for (int i = 0; i < f->locate->numHoop; i++) {
		totalDistance += f->locate->distance[i];
	}
	return totalDistance;
}

void loadingBar(double time, double maxTime) {
	int percent = (int)(time * 80 / maxTime);
	for (int i = 0; i < percent - 1; i++) {
		printf(".");
	}
	printf("%c",254);
	printf("\n");
}

void loadingLocation(double time, double maxTime, flight *f) {
	int percent = (int)(time * 80 / maxTime);
	char str[50];
	double distance = time * f->speed / 60;
	for (int i = 0; i < percent - 5; i++) {
		printf(" ");
	}
	sprintf(str, "%s", f->locate->startnode[0]);
	for (int i = 0; i < f->locate->numHoop; i++) {
		if (distance>=f->locate->distancec[i]) {
			sprintf(str, "%s", f->locate->endnode[i]);
		}
	}
	printf("%s", str);
	printf("\n");
}

void selectFlight(flight **allf, int status[]) {
	char input;
	int hitTime = 0;
	do {
		system("cls");
		printf("Select three Flights that you want to tracking\n");

		printSelector(allf, status);
		do {
			input = _getch();
		} while (input <= '0' || input > 48 + NUM);
		status[input - 49] = 1;
		hitTime = getHitTime(status);
	} while (hitTime != 3);
}

void printSelector(flight **allf ,int status[]) {
	char c;
	int num = 0;
	for (int i = 0; i < NUM; i++) {
		if (status[i] == 1) {
			c = 254;
		} else {
			c = ' ';
		}
		
		if (i <= 9) {
			printf("   [%c] ", c);
			printf("%c : %s %s-%s\n", i + 49, allf[i]->code, allf[i]->locate->startnode[0], allf[i]->locate->endnode[allf[i]->locate->numHoop - 1]);
		} else {
			printf("   [%c] ", c);
			printf("%c : %s %s-%s\n", i + 49 + 39 , allf[i]->code, allf[i]->locate->startnode[0], allf[i]->locate->endnode[allf[i]->locate->numHoop - 1]);
		}
	}
}

int getHitTime(int status[]) {
	int num = 0;
	for (int i = 0; i < NUM; i++) {
		if (status[i] == 1)
			num++;
	}
	return num;
}

void clearHitTime(int status[]) {
	for (int i = 0; i < NUM; i++) {
		status[i] = 0;
	}
}