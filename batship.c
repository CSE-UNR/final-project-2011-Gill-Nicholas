//Final Project
//Nicholas Gill
//7/26/2024
#include<stdio.h>
#include<stdbool.h>
#define SIZE 10
#define FILE_TYPE "easy.txt"
//prototypes
void display(char board[][SIZE]);
int playGame(char guess[][SIZE], char ships[][SIZE]);
void clear(char board[][SIZE]);
bool miss(int colMove, char rowMove);
bool won(char guess[][SIZE], char ships[][SIZE]);
int loadSea(FILE* fin, char board[][SIZE]);
//Body
int main(){
	char guess[SIZE][SIZE], ships[SIZE][SIZE]; 
	FILE* fin;
	char playAgain;
	int playerTurns, numSpots;
	
	fin = fopen(FILE_TYPE, "r");
	if(fin == NULL){
		printf("Cant't open file");
		return 0;
	}
	numSpots = loadSea(fin, ships);
	fclose(fin);
	
	do{
		clear(guess);
		playerTurns = playGame(guess, ships);
		display(guess);
		printf("AWESOME JOB!\n");
		printf("It took %d turns for you to hit %d spots and destroy all thr ships\n", playerTurns, numSpots);
		printf("Your score is %d!\n", 100 - playerTurns + numSpots);
		printf("Play again? (Y/N) ");
		scanf(" %c", &playAgain);
	}while(playAgain == 'Y');
	

	return 0;
}
//definitions
void display(char board[][SIZE]){
	printf("   A B C D E F G H I J\n");
	for(int row1 = 0; row1 < SIZE; row1++){
		if(row1 == SIZE -1){
			printf("%d ", row1 + 1);
		}
		else{
			printf("%d ", row1 + 1);
		}
		
		for(int col1 = 0; col1 < SIZE; col1++){
			printf("%c ", board[row1][col1]);
		}
		printf("\n");
	}
}
int playGame(char guess[][SIZE], char ships[][SIZE]){
	int moveRow, moveCol;
	int numFires = 0;
	char userCol;
	
	do{
		display(guess);
		
		printf("Fire away!\n(enter a square in the grid like A1) ");
		scanf(" %c%d", &userCol, &moveRow);
		
		while(!miss(userCol, moveRow)){
			printf("Try again!\n(enter a square in the grid like A1) ");
			scanf(" %c%d", &userCol, &moveRow);
		}
		
		moveRow--;
		moveCol = userCol - 'A';
		
		if(ships[moveRow][moveCol] == 'S'){
			guess[moveRow][moveCol] = 'X';
		}
		else{
			guess[moveRow][moveCol] = 'O';
		}
		
		numFires++;
	}while(!won(guess, ships));
	
	return numFires;
}
void clear(char board[][SIZE]){
	for(int row1 = 0; row1 < SIZE; row1++){
		for(int col1 = 0; col1 < SIZE; col1++){
			board[row1][col1] = ' ';
		}
	}
}
bool miss(int colMove, char rowMove){
	if(colMove > 'J' || colMove < 'A'){
		printf("Invalid column letter.\n");
		return false;
	}
	else if(rowMove < 1 || rowMove > 10){
		printf("Invalid row number.\n");
		return false;
		
	}
	return true;
}
bool won(char guess[][SIZE], char ships[][SIZE]){
	for(int row1 = 0; row1 < SIZE; row1++){
		for(int col1 = 0; col1 < SIZE; col1++){
			if(ships[row1][col1] == 'S' && guess[row1][col1] != 'X'){
				return false;
			}
		}
	}
	return true;
}

int loadSea(FILE* fin, char board[][SIZE]){
	char cent;
	int shipScore = 0;
	
	for(int row1 = 0; row1 < SIZE; row1++){
		for(int col1 = 0; col1 < SIZE; col1++){
			fscanf(fin, "%c", &board[row1][col1]);
			if(board[row1][col1] == 'S'){
				shipScore++;
			}
		}
		fscanf(fin, "%c", &cent);
	}
	return shipScore;
}
