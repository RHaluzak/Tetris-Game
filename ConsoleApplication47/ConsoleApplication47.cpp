
#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>		
#include <time.h>		
#include <Windows.h>
using namespace std;





const int WIDTH = 12; // Board will always be 12 units wide.
const int HEIGHT = 25;// Board will always be 25 units tall.
enum { UP_ARROW = 38, DOWN_ARROW = 40, LEFT_ARROW = 37, RIGHT_ARROW = 39 };// Setting directional keys
int speed = 100;// Default speed
int score = 0;

class TetrisShape
{
public:
	int shapeTopLeftX;
	int shapeTopLeftY;
	char shapeArray[4][4];
	void populateShapeArray(int shapeType){// Coordinates of the tetris piece.
		shapeTopLeftX = 6,			
		shapeTopLeftY = 0;			
		
		
		switch (shapeType){// The different shapes in Tetris
		case 0:					
			shapeArray[0][0] = ' '; shapeArray[1][0] = ' '; shapeArray[2][0] = ' '; shapeArray[3][0] = ' ';
			shapeArray[0][1] = ' '; shapeArray[1][1] = 'X'; shapeArray[2][1] = 'X'; shapeArray[3][1] = ' ';
			shapeArray[0][2] = ' '; shapeArray[1][2] = 'X'; shapeArray[2][2] = 'X'; shapeArray[3][2] = ' ';
			shapeArray[0][3] = ' '; shapeArray[1][3] = ' '; shapeArray[2][3] = ' '; shapeArray[3][3] = ' ';
			break;
		case 1:					
			shapeArray[0][0] = ' '; shapeArray[1][0] = ' '; shapeArray[2][0] = ' '; shapeArray[3][0] = ' ';
			shapeArray[0][1] = 'X'; shapeArray[1][1] = 'X'; shapeArray[2][1] = 'X'; shapeArray[3][1] = 'X';
			shapeArray[0][2] = ' '; shapeArray[1][2] = ' '; shapeArray[2][2] = ' '; shapeArray[3][2] = ' ';
			shapeArray[0][3] = ' '; shapeArray[1][3] = ' '; shapeArray[2][3] = ' '; shapeArray[3][3] = ' ';
			break;
		case 2:					
			shapeArray[0][0] = ' '; shapeArray[1][0] = ' '; shapeArray[2][0] = ' '; shapeArray[3][0] = ' ';
			shapeArray[0][1] = ' '; shapeArray[1][1] = ' '; shapeArray[2][1] = 'X'; shapeArray[3][1] = 'X';
			shapeArray[0][2] = ' '; shapeArray[1][2] = 'X'; shapeArray[2][2] = 'X'; shapeArray[3][2] = ' ';
			shapeArray[0][3] = ' '; shapeArray[1][3] = ' '; shapeArray[2][3] = ' '; shapeArray[3][3] = ' ';
			break;
		case 3:					
			shapeArray[0][0] = ' '; shapeArray[1][0] = ' '; shapeArray[2][0] = ' '; shapeArray[3][0] = ' ';
			shapeArray[0][1] = ' '; shapeArray[1][1] = 'X'; shapeArray[2][1] = 'X'; shapeArray[3][1] = ' ';
			shapeArray[0][2] = ' '; shapeArray[1][2] = ' '; shapeArray[2][2] = 'X'; shapeArray[3][2] = 'X';
			shapeArray[0][3] = ' '; shapeArray[1][3] = ' '; shapeArray[2][3] = ' '; shapeArray[3][3] = ' ';
			break;
		case 4:					
			shapeArray[0][0] = ' '; shapeArray[1][0] = ' '; shapeArray[2][0] = ' '; shapeArray[3][0] = ' ';
			shapeArray[0][1] = ' '; shapeArray[1][1] = 'X'; shapeArray[2][1] = 'X'; shapeArray[3][1] = 'X';
			shapeArray[0][2] = ' '; shapeArray[1][2] = 'X'; shapeArray[2][2] = ' '; shapeArray[3][2] = ' ';
			shapeArray[0][3] = ' '; shapeArray[1][3] = ' '; shapeArray[2][3] = ' '; shapeArray[3][3] = ' ';
			break;
		case 5:					
			shapeArray[0][0] = ' '; shapeArray[1][0] = ' '; shapeArray[2][0] = ' '; shapeArray[3][0] = ' ';
			shapeArray[0][1] = ' '; shapeArray[1][1] = 'X'; shapeArray[2][1] = 'X'; shapeArray[3][1] = 'X';
			shapeArray[0][2] = ' '; shapeArray[1][2] = ' '; shapeArray[2][2] = ' '; shapeArray[3][2] = 'X';
			shapeArray[0][3] = ' '; shapeArray[1][3] = ' '; shapeArray[2][3] = ' '; shapeArray[3][3] = ' ';
			break;
		case 6:					
			shapeArray[0][0] = ' '; shapeArray[1][0] = ' '; shapeArray[2][0] = ' '; shapeArray[3][0] = ' ';
			shapeArray[0][1] = ' '; shapeArray[1][1] = 'X'; shapeArray[2][1] = 'X'; shapeArray[3][1] = 'X';
			shapeArray[0][2] = ' '; shapeArray[1][2] = ' '; shapeArray[2][2] = 'X'; shapeArray[3][2] = ' ';
			shapeArray[0][3] = ' '; shapeArray[1][3] = ' '; shapeArray[2][3] = ' '; shapeArray[3][3] = ' ';
			break;
		}	
	}

};

void generateBucket(char bucket[WIDTH][HEIGHT]){// Creates the bucket.
	

	for (int i = 0; i < HEIGHT; i++){	//Borders are 0s		
		bucket[0][i] = '0';					
		for (int j = 1; j < 11; j++){
			bucket[j][i] = ' ';
		}
		bucket[11][i] = '0';
	}
	for (int j = 0; j < WIDTH; j++){			
		bucket[j][24] = '0';
	}
	Sleep(200); // Pause for a moment
}


void setCursorTo(int x, int y) // Tells where to display grid.
{
	HANDLE handle;
	COORD position;
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	position.X = x;
	position.Y = y;
	SetConsoleCursorPosition(handle, position);
}

void displayBucket(char bucket[WIDTH][HEIGHT]){ // Displays the bucket

	for (int i = 0; i < HEIGHT; i++){
		setCursorTo(30, i);
		for (int j = 0; j < WIDTH; j++){
			cout << bucket[j][i];
		}
		cout << endl;
	}
	cout << endl;
}




int generateNewPiece(){ //Genreates a new piece.
	int number = rand() % 7;
	return number;
}

bool lowerPiece(TetrisShape& shape, char bucket[WIDTH][HEIGHT]){ //Makes the Piece descend.
	int x = shape.shapeTopLeftX,
		y = shape.shapeTopLeftY;
	
	for (int i = 0; i < 4; i++){			
		for (int j = 3; j >= 0; j--){		
			if (shape.shapeArray[i][j] == 'X'){
				if (bucket[i + x][j + y + 1] != ' ') return 0;
				else break;
			}
		}
	}

	return 1;
}


void clearShape(TetrisShape localTetrisShape, char bucket[WIDTH][HEIGHT]){ 
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			if (localTetrisShape.shapeArray[i][j] == 'X'){
				bucket[i + localTetrisShape.shapeTopLeftX][j + localTetrisShape.shapeTopLeftY] = ' ';
			}
		}
	}
}


void updateBucket(TetrisShape localTetrisShape, char bucket[WIDTH][HEIGHT]){ // Redraws the bucket.
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			if (localTetrisShape.shapeArray[i][j] == 'X'){
				bucket[i + localTetrisShape.shapeTopLeftX][j + localTetrisShape.shapeTopLeftY] = localTetrisShape.shapeArray[i][j];
			}
		}
	}
}



int getInput(){ // Recieves key input.
	if (GetAsyncKeyState(LEFT_ARROW)) return LEFT_ARROW;
	else if (GetAsyncKeyState(RIGHT_ARROW)) return RIGHT_ARROW;
	else if (GetAsyncKeyState(UP_ARROW)) return UP_ARROW;
	else if (GetAsyncKeyState(DOWN_ARROW)) return DOWN_ARROW;
	else return 0;
}

int movePiece(int input, TetrisShape& shape, char bucket[WIDTH][HEIGHT]){ //Allows for Piece movement
	int x = shape.shapeTopLeftX;
	int y = shape.shapeTopLeftY;
	switch (input){
	case DOWN_ARROW: //Just decreases sleep time.
		speed = speed/8;
		break;
	case RIGHT_ARROW: // Checks to se if the piece can be moved to the right, if not nothing happens (returns 0).
		for (int j = 0; j < 4; j++){			
			for (int i = 3; i >= 0; i--){		
				if (shape.shapeArray[i][j] == 'X'){
					if (bucket[i + x + 1][j + y] != ' ') return 0;
					else break;
				}
			}
		}
		shape.shapeTopLeftX++;
		break;
	case LEFT_ARROW: // Checks to see if the piece can be moved to the left, if not, does nothing (returns 0).
		for (int j = 0; j < 4; j++){				
			for (int i = 0; i < 4; i++){			
				if (shape.shapeArray[i][j] == 'X'){
					if (bucket[i + x - 1][j + y] != ' ') return 0;
					else break;
				}
			}
		}
		shape.shapeTopLeftX--;
		break;
	case UP_ARROW: // Checks to see if the piece can be rotated, if not, does nothing (returns 0).
		for (int j = 0; j < 4; j++){				
			for (int i = 0; i < 4; i++){			
				if (shape.shapeArray[i][j] == 'X'){					
					if (bucket[(3-j) + x][i + y] != ' ') return 0;	
	
				}
			}
		}
		\

		char temp = shape.shapeArray[0][1];
		shape.shapeArray[0][1] = shape.shapeArray[1][3];
		shape.shapeArray[1][3] = shape.shapeArray[3][2];
		shape.shapeArray[3][2] = shape.shapeArray[2][0];
		shape.shapeArray[2][0] = temp;

		temp = shape.shapeArray[0][2];
		shape.shapeArray[0][2] = shape.shapeArray[2][3];
		shape.shapeArray[2][3] = shape.shapeArray[3][1];
		shape.shapeArray[3][1] = shape.shapeArray[1][0];
		shape.shapeArray[1][0] = temp;

		temp = shape.shapeArray[1][1];
		shape.shapeArray[1][1] = shape.shapeArray[1][2];
		shape.shapeArray[1][2] = shape.shapeArray[2][2];
		shape.shapeArray[2][2] = shape.shapeArray[2][1];
		shape.shapeArray[2][1] = temp;
		break;
	}

}


int clearLines(char bucket[WIDTH][HEIGHT], int y){	//Clears completed lines and adds points.	
	bool clearedLines[4] = { true, true, true, true };// Checks for completed lines.

	for (int j = 0; j < 4; j++){
		for (int i = 1; i < 11; i++){
			if (bucket[i][y + j] != 'X'){
				clearedLines[j] = false;
				break;
			}
		}
	}
	
	if (clearedLines[0] == true || clearedLines[1] == true ||
		clearedLines[2] == true || clearedLines[3] == true){
		for (int j = 0; j < 4; j++){
			if (clearedLines[j] == true){
				for (int i = 1; i < 11; i++) bucket[i][y + j] = ' ';
				score = score + 100; // Score 100 points per line cleared.
			}
		}
		displayBucket(bucket);
		Sleep(100);

		for (int j = 0; j < 4; j++){
			if (clearedLines[j] == true){
				for (int i = 1; i < 11; i++) bucket[i][y + j] = 'X';
			}
		}
		displayBucket(bucket);
		Sleep(100);

		for (int j = 0; j < 4; j++){
			if (clearedLines[j] == true){
				for (int i = 1; i < 11; i++) bucket[i][y + j] = ' ';
			}
		}
		displayBucket(bucket);
		Sleep(100);
		int n = 0;
		for (int l = 3; l >= 0; l--){
			if (clearedLines[l] == true){
				n++;
				for (int j = y + l + n-1; j > 0; j--){
					for (int i = 1; i < 11; i++) bucket[i][j] = bucket[i][j - 1];
				}
			}
		}
		displayBucket(bucket);
		Sleep(100);

		return n;
	} else return 0;
}

void displayScore(){
	setCursorTo(25,0);
	cout<<score<<endl;
}


int _tmain(int argc, _TCHAR* argv[]) //Executes everyting!
{
	srand(time(NULL));		
	char bucket[WIDTH][HEIGHT];		 
	bool descend = false;		
	int piece = rand()% 6 + 1;	
	int newPiece = rand() % 6 + 1;	
	int input;
	int linesCleared = 0;
	bool endGame = false;

	srand (time(NULL));
	TetrisShape shape;

	generateBucket(bucket);
	shape.populateShapeArray(piece);		
	updateBucket(shape, bucket);
	
	while (!endGame){				
		Sleep(speed);
		speed=100;
		displayBucket(bucket);			
		clearShape(shape, bucket);	
		for(int x = 1; x < WIDTH; x++){//Checks to see if game is over.
			if(bucket[x][1] == 'X'){
				endGame = true;
			}
		}
		
		input = getInput();									
		if (input) movePiece(input, shape, bucket);			

		if (!lowerPiece(shape, bucket)){											
			updateBucket(shape, bucket);											
			linesCleared += clearLines(bucket, shape.shapeTopLeftY);				
			piece = newPiece;													
			newPiece = generateNewPiece();											
			shape.populateShapeArray(piece);												
			updateBucket(shape, bucket);
		}
		else {
			if (descend){										
				shape.shapeTopLeftY = shape.shapeTopLeftY + 1;	
				descend = false;
			} else descend = true;
		}
		updateBucket(shape, bucket);
		Sleep(speed);
		displayScore(); //Score is always displayed.
	}
	cout<<"Game Over, your score is: "<<score<<endl;
	system("pause");
	
	return 0;

}

