#define _CRT_SECURE_NO_DEPRECATE
#define MAXFLIGHT 5
#define NUM 2
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
	double distance[20];
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

int main(void) {
	/// Initialize Variable & Pointer
	tm *timeInfo = (tm*)malloc(sizeof(tm));
	time_t now;
	int selectChoice;
	int exitStatus = 0;
	double seconds;
	double maxTime[NUM];
	double timer[NUM];
	int percent;

	//------------ Routine Part

	flight *allFlight[MAXFLIGHT];
	location *allLocation[MAXFLIGHT];

	// Get All Locations form File
	for (int i = 0; i < NUM; i++) {
		allLocation[i] = getRoutine(i+1);
	}
	// Get All Flights form file
	for (int i = 0; i < NUM; i++) {
		allFlight[i] = getFlight(i+1, allLocation[i]);
	}

	//printf("\nStart location is :%s", allFlight[0]->locate->startnode[0]);
	//printf("\nDesination is : %s", allFlight[0]->locate->endnode[allFlight[0]->locate->numHoop-1]);
	//printf("\nThe number of passenger is %d peopoles", allFlight[0]->num_people);


	//----------------- Interfacing

	while (!exitStatus) {
		system("cls"); // <--- Clear Screen
		//getTime(timeInfo); // <--- Show current time 
		getLogo();

		printf("\n-----Fight Tracking ver 1.0-----\n");

		selectChoice = firstInterface(); //  <--- Show select menu interface and return choice
		//int dataIn;
		switch (selectChoice)
		{
		case '1':
			getTime(timeInfo);
			//printf("Press 'q' to end process\n");
			do {
				system("cls");
				time(&now);
				seconds = difftime(now, mktime(timeInfo));

				printf("Start Fligth tracking\n");
				
				for (int i = 0; i < NUM; i++) {
					maxTime[i] = getAllDistance(allFlight[i]) / allFlight[i]->speed * 60;
					timer[i] = (int)seconds % (int)maxTime[i];
					printf("--------------------------------------------------------------------------------\n");
					printf("\t%s ,%.2lfkm/hr\n",allFlight[i]->code,allFlight[i]->speed);
					printf("\t%s - %s\n",allFlight[i]->locate->startnode[0], allFlight[i]->locate->startnode[allFlight[i]->locate->numHoop-1]);
					loadingBar(timer[i], maxTime[i]);
					percent = timer[i] / (int)maxTime[i] * 100;
					printf("\t\t\t\t\t\t\t\t\t[%d%c]\n",percent,'%');
					printf("--------------------------------------------------------------------------------\n");
				}
				
				// Delay
				for (int i = 0; i < 10000; i++) {
					for (int j = 0; j < 10000; j++);
				}
				while ((int)seconds % 2) {
					time(&now);
					seconds = difftime(now, mktime(timeInfo));
				}
			} while ((int)seconds < 10000);

			/*printf("\n%.2lf \n", getAllDistance(allFlight[1]) / allFlight[1]->speed * 60);*/
			exitStatus = 1;
			break;
		case '2':
			settingMenu(allFlight);
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

location* getRoutine(int numfile) {
	location *l = (location*)malloc(sizeof(location));
	FILE *fp;
	char s1[50];
	char s2[50];
	double distance;
	int num = 0;
	char str[20];

	sprintf(str,"location/l%.2d.csv",numfile);

	fp = fopen(str, "r");

	if (fp == NULL)
	{
		perror(str);
		_getch();
		exit(EXIT_FAILURE);
	}

	while (fscanf(fp, "%s %s %lf", s1, s2, &distance) != EOF) {
		num++;
		//printf("\n[%s-%s]-%d->%d", s1, s2, distance,num);
		
		strcpy(l->startnode[num-1],s1);
		strcpy(l->endnode[num-1],s2);
		l->distance[num-1] = distance;
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
	int numPeople;
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

	while (fscanf(fp, "%s %lf %d", code, &speed, &numPeople) != EOF) {
		num++;
		//printf("\n[%s]-%.2lf->%d", code, speed, numPeople);

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

	//timeInfo->tm_hour = info->tm_hour;
	//timeInfo->tm_isdst = info->tm_isdst;
	//timeInfo->tm_mday = info->tm_mday;
	//timeInfo->tm_min = info->tm_min;
	//timeInfo->tm_mon = info->tm_mon;
	//timeInfo->tm_sec = info->tm_sec;
	//timeInfo->tm_wday = info->tm_wday;
	//timeInfo->tm_yday = info->tm_yday;
	//timeInfo->tm_year = info->tm_year;

	*timeInfo = *info;
}

void settingMenu(flight *allf[]) {
	int input;
	char code[50];
	double speed;
	int num;
	system("cls");
	printf("Select the Flight that you want to setting\n");
	for (int i = 0; i < NUM; i++) {
		printf("\t%d : %s %s-%s\n",i+1,allf[i]->code,allf[i]->locate->startnode[0], allf[i]->locate->startnode[allf[i]->locate->numHoop-1]);
	}
	do {
		input = _getch();
	} while (input <= '0' || input > 48+NUM);

	printf("Flight's Code [%s] : ",allf[input-49]->code);
	scanf("%s",code);
	printf("Flight's speed [%.2lf] : ", allf[input - 49]->speed);
	scanf("%lf", &speed);
	printf("Number of people [%d] : ", allf[input - 49]->num_people);
	scanf("%d", &num);

	// Update Structure Data
	strcpy(allf[input - 49]->code, code);
	allf[input - 49]->speed = speed;
	allf[input - 49]->num_people = num;

	// Write Changed Data to Files
	FILE *fp;
	char str[20];
	sprintf(str,"flight/f%.2d.csv",input-48);

	fp = fopen(str, "w+");

	if (fp == NULL)
	{
		perror(str);
		_getch();
		exit(EXIT_FAILURE);
	}
	fprintf(fp, "%s %.2lf %d",code,speed,num);
	fclose(fp);

}

double getAllDistance(flight *f) {
	double totalDistance = 0;
	for (int i = 0; i < f->locate->numHoop; i++) {
		totalDistance += f->locate->distance[i];
	}
	return totalDistance;
}

void loadingBar(double time,double maxTime) {
	int percent = (int)(time * 80 / maxTime);
	for (int i = 0; i < percent; i++) {
			printf("%c",176);
	}
	printf("\n");
}