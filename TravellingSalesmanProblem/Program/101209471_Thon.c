/*
	101209471_Thon.c
	Thon Pun Liang 101209471
	28/11/2018
*/

/* Include necessary libraries */
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

/* 
   Define some constant 
   - Constant Array Size: Row and Col
   		- User can customize the size of the game board
   - Number of Cities
        - User can customize the number of cities to be visited
		- Recommended limit is 26 as only 26 letters
*/
#define nROW 8  // Number of Row of the array
#define nCOL 8  // Number of Col of the array
#define nCITY 13  // Number of cities of the game

typedef struct {
	int cROW;  // Current ROW coordinate
	int cCOL;  // Current COL coordinate
	int score;  // Cities visited
	int numMove;  // Moves used
	char name[30]; // User's name
} Move;

/* To print the array after evey move*/
void print_array(char array[nROW][nCOL]) {
	int x,y;
	for (x=0; x<nROW; x++) {
		for (y=0; y<nCOL; y++) {
			printf("  %c  ", array[x][y]);
		}
		printf("\n\n");
	}
}

/* To initialize the array */
void init_array(char (*array)[nROW][nCOL], Move *coor) {
	int x,y;
	for (x=0; x<nROW; x++) {
		for (y=0; y<nCOL; y++) {
			(*array)[x][y] = '*';  // Initialize with symbol '*'
		}
	}
	
	/* Codes below randomize starting point */
	srand((unsigned) time(NULL));
	(*coor).cROW = rand() % 8;
	(*coor).cCOL = rand() % 8;	    
	
	(*array)[(*coor).cROW][(*coor).cCOL] = '@';  // This is the head '@'
}

/* To generate cities and assign randomly into array */
void generateCities(char (*array)[nROW][nCOL]) {
	int x,row,col;
	
	srand((unsigned) time(NULL));
	
	/* Codes below assign cities randomly in the array */
	for (x=0; x<nCITY; x++) {
		row = rand() % nROW;
		col = rand() % nCOL;
		
		/* If the coordinates is not '*', go back again */
		/* Only replace '*' with cities (letter) */
		if ((*array)[row][col] != '*') {
			x -= 1;
		}
		else {
			(*array)[row][col] = 'A'+x;  // A,B,C,...
		}
	}
}

/* Get user movement from input */
char getUserMove() {
	char move;
	
	printf("Use:\n");
	printf("[W] to move upward,\n");
	printf("[A] to move toward left,\n");
	printf("[S] to move downward,\n");
	printf("[D] to move toward right.\n");
	printf("[Q] to quit the program.\n");
	printf("Your move: ");
	fflush(stdin);
	scanf("%c", &move);
	
	return move;
}

/* Validate user movement */
char valInput(char move) {
	
	if (move == 'w' || move =='W' ||
	move == 'a' || move == 'A' ||
	move == 's' || move == 'S' ||
	move == 'd' || move == 'D' ||
	move == 'q' || move == 'Q') {
		return 'Y';
	}
	else {
		return 'N';
	}
}

/* Validate Movement */
void valUserMove(char move, char (*array)[nROW][nCOL], Move *movement) {
	char exitx;
	
	/* After each move is done, replace the initial coor with tail '=' */
	(*array)[(*movement).cROW][(*movement).cCOL] = '=';
	
	/* Codes below determine the direction of the head '@' */
	if (move == 'w' || move == 'W') {
		(*movement).cROW = (*movement).cROW - 1;
	}
	else if (move == 'a' || move == 'A') {
		(*movement).cCOL = (*movement).cCOL - 1;
	}
	else if (move == 's' || move == 'S') {
		(*movement).cROW = (*movement).cROW + 1;
	}
	else if (move == 'd' || move == 'D') {
		(*movement).cCOL = (*movement).cCOL + 1;
	}
	
	/* If user decide to quit during game play */
	else if (move == 'q' || move == 'Q') {
		printf("Thanks for playing! See you again!");
		scanf("%c", &exitx);
		exit(0);  // Exit the program
	}
	
	/* Codes below prevent user to break the program
	   by insisting to go over the barrier of the array
	   ie if the max row is 8 the user try to continue move
	   downward.
	   The program will get malfunction if below's code is 
	   absent. */
	if ((*movement).cROW < 0) {
		(*movement).cROW = 0;
		(*movement).numMove--;  // To prevent the moves count even if go over boarder
	}
	else if ((*movement).cROW > nROW-1) {
		(*movement).cROW = nROW-1;
		(*movement).numMove--;  // To prevent the moves count even if go over boarder
	}
	
	if ((*movement).cCOL < 0) {
		(*movement).cCOL = 0;
		(*movement).numMove--;  // To prevent the moves count even if go over boarder
	}
	else if ((*movement).cCOL > nCOL-1) {
		(*movement).cCOL = nCOL-1;
		(*movement).numMove--;  // To prevent the moves count even if go over boarder
	}
}

/* Do movement by putting head '@' in the array*/
void doUserMove(char move, char (*array)[nROW][nCOL], Move *movement) {
	(*array)[(*movement).cROW][(*movement).cCOL] = '@';
}

/* Count score and movement */
// If not '*' '=' '@' score ++
void calScore(char (*array)[nROW][nCOL], Move *move) {
	if ((*array)[(*move).cROW][(*move).cCOL] != '*' &&
	(*array)[(*move).cROW][(*move).cCOL] != '=' &&
	(*array)[(*move).cROW][(*move).cCOL] != '@') {
		(*move).score += 1;
	}
}	 

/* Display final result */
void finalResult(Move *final) {
	char exit;
	printf("\n---Congratulation---\n");
	printf("Player: %s\n", (*final).name);
	printf("Number of Cities visited: %i\n", (*final).score);
	printf("Number of moves used: %i\n", (*final).numMove);
	printf("---Thanks for playing the game---");
	fflush(stdin);
	scanf("%c", &exit);
}

/* Display welcome page from textfile */
void welcomePage() {
	char c;
	FILE *welcome;

	welcome = fopen("welcomeBanner.txt", "r");
	
	if (welcome == NULL) { 
        printf("Cannot open file \n"); 
        exit(0);  // Exit program if file is null
    } 
  
    // Read contents from file line by line
    c = fgetc(welcome); 
    while (c != EOF) { 
        printf ("%c", c); 
        c = fgetc(welcome); 
    }
	
	fclose(welcome);
}

/* Get user's name and start the program */
void userInfo(Move *info) {
	char xxx;
	printf("\nPlease enter your name: ");
	scanf("%s", (*info).name);
	fflush(stdin);
	printf("Hello %s! Press any key to start your game!", (*info).name);
	scanf("%c", &xxx);
	fflush(stdin);
}

/* Store the game history to textfile */
void storeRecord(Move *rec) {
	FILE *result;
	
	result = fopen("result.txt", "a");
	
	if (result == NULL) { 
        printf("Cannot open file \n"); 
        exit(0);    // Exit program if file is null
    }
	
	fprintf(result, "%s %i %i\n", (*rec).name, (*rec).numMove, (*rec).score);
	
	fclose(result);
}

/* Print previous users' histories */
void printRecord() {
	char namex[30];
	int x, y, bil=0, num=0;

	FILE *reco;
	reco = fopen("result.txt", "r");
	
	if (reco == NULL) { 
        printf("Cannot open file \n"); 
        exit(0);    // Exit program if file is null
    }
	
	printf("\n\n---Previous Players' Records---\n");
	printf("Bil. | Player's Name | Number of Moves | Number of Cities\n");
	
	do {
		bil++;
		num = fscanf(reco, "%s %i %i", namex, &x, &y);
		if(num==3) {
			printf(" %i.\t%s\t\t%i\t\t  %i\n", bil, namex, x, y);
		}
	} while(num==3);
	
	fclose(reco);
}

/* Print real time game status */
void printStatus(Move *status) {
	printf("\nNumber of Move: %i\n", (*status).numMove);
	printf("Number of Cities visited: %i\n\n", (*status).score);
}

/* Main */
int main(void) {
	char game_array[nROW][nCOL];
	char userMove,valMove = 'N';
	
	/* Initialize value in struct Move */
	Move movement = {0, 0, 0, 0};
	
	welcomePage();  // Welcome page
	printRecord();  // Print previous records
	userInfo(&movement);  // Get user name and start game
	init_array(&game_array, &movement);  // Initialize array
	generateCities(&game_array);  // Generate cities into array
	
	/* Loop below codes until all cities has been visited */
	do {
		// Print status
		printStatus(&movement);
		
		/* Loop below codes if user input is wrong */
		do {
			print_array(game_array);  // Print gane array
			userMove = getUserMove();  // Get user's next move
		} while (valInput(userMove) == 'N');  // Validate user's move
	
		// Validate user move
		valUserMove(userMove, &game_array, &movement);
		// Cal Score if cities visited
		calScore(&game_array, &movement);
		// +1 to num of move
		movement.numMove++;
		// Actually move the head '@'
		doUserMove(userMove, &game_array, &movement);
	} while(movement.score<nCITY);
	
	storeRecord(&movement);  // Store record
	finalResult(&movement);  // Print final result
	
	return 0;
}

