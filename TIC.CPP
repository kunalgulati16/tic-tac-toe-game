#include <dos.h>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include <graphics.h>

union REGS in, out;
int gdriver, gmode, errorcode;

int boardCreated = 0;
char matrix[3][3];

char player1[20];
char player2[20];
int playerturn = 1;
int vsComputer = 1;

void initGame();

class point {
	public:
	int x;
	int y;
	point(){
		x=0;
		y=0;
	}
	point(int x1,int y1){
		x=x1;
		y=y1;
	}
};

void initBoard ();
void createBoard ();
void closeBoard ();
point getInput(char turn);
void drawAt(int c, char turn);
void drawO (point p);
void drawX (point p);
int hasWon(char turn, int draw);
int hasWon(char turn);
int hasTied();
void makeWin(char winner);
void makeTie();
void initGame();

class Scoreboard {
	public:
	int X;
	int O;
	Scoreboard() {
		X=0;
		O=0;
	}
	
	int winsO(){
		return O++;
	}
	
	int winsX(){
		return X++;
	}
	
	void drawScoreboard ();
} score;

void Scoreboard::drawScoreboard () {
	int array[]={220, 380, 445, 380, 445, 450, 220, 450};
	setfillstyle(SOLID_FILL,BLACK);
	fillpoly(4,array);
	setcolor(15);
	char winText[100];
	outtextxy(290, 390, "LeaderBoard");
	sprintf(winText, "%10.10s (X):    %d", player1, X);
	outtextxy(245, 408, winText);
	sprintf(winText, "%10.10s (O):    %d", player2, O);
	outtextxy(245, 421, winText);
	if(playerturn == 1){
		outtextxy(235, 408,"=>");
	} else {
		outtextxy(235, 421, "=>"); // prints »
	}
}

class Computer {
	public:
		char compPlayer;
		char guestPlayer;
		int plyturn;
		int startby;
		Computer (int playerStart) {
			startby = playerStart;
		}
		Computer () {
			startby = 0;
		}
		
		void gamePlay();
		int checkWin();
		int checkOppWin ();
		void markPosition ();

} comp;

void Computer::gamePlay() {
			if(startby == 1){
				compPlayer = 'O';
				guestPlayer = 'X';
			} else {
				compPlayer = 'X';
				guestPlayer = 'O';
			}
			createBoard();
			int i = startby;
			while(1){
				if(i){
					guestPlayer == 'X' ? drawX(getInput(guestPlayer)) : drawO(getInput(guestPlayer));
					if(hasWon(guestPlayer)){
						makeWin(guestPlayer);
						break;
					}
						
				} else {
					if(checkWin()){
						break;
					} else if (!checkOppWin()){
						markPosition();
					}
				}
				if(hasTied()){
					makeTie();
					break;
				}
				i++;
				i%=2;
				playerturn = i;
				score.drawScoreboard();
			}
		}

int Computer::checkWin() {
	for(int i=0; i<3;i++){
		for(int j=0; j<3; j++){
			if(matrix[i][j] == '-'){
				matrix[i][j] = compPlayer;
				if(hasWon(compPlayer)){
					drawAt(10-3*(i+1)+j, compPlayer);
					makeWin(compPlayer);
					return 1;
				} else {
					matrix[i][j] = '-';
				}
			}
		}
	}
	return 0;
}	
	
int Computer::checkOppWin () {
	for(int i=0; i<3;i++){
		for(int j=0; j<3; j++){
			if(matrix[i][j] == '-'){
				matrix[i][j] = guestPlayer;
				if(hasWon(guestPlayer, 0)){
					matrix[i][j] = compPlayer;
					drawAt(10-3*(i+1)+j, compPlayer);
					return 1;
				} else {
					matrix[i][j] = '-';
				}
			}
		}
	}
	return 0;
}
	
void Computer::markPosition () {
	
	point available[9];
	int length =0;
	
	for(int i=0; i<3;i++){
		for(int j=0; j<3; j++){
			if(matrix[i][j] == '-'){
				available[length++] = point(i,j);
			}
		}
	}
	
	int r = rand() % length;
	matrix[available[r].x][available[r].y] = compPlayer;
	drawAt(10-3*(available[r].x+1)+available[r].y, compPlayer);
	
}	

void initBoard () {
	boardCreated = 1;
	gdriver = DETECT;
	initgraph(&gdriver, &gmode, "C:\\TURBOC3\\BGI");
}
void createBoard () {
	
	if(!boardCreated)
		initBoard();
	else
		cleardevice();
	
	line(100, 0, 100, 300);
	line(200, 0, 200, 300);
	
	line(0, 100, 300, 100);
	line(0, 200, 300, 200);
	
	playerturn = 1;
	score.drawScoreboard();
	
	for(int i=0; i<3;i++){
		for(int j=0; j<3; j++){
			matrix[i][j] = '-';
		}
	}
}
void closeBoard () {
	cleardevice();
	boardCreated = 0;
	closegraph();
}

point getInput(char turn) {
	char c = getch();
	switch(c){
		case '1':
			if (matrix[2][0] == '-'){
				matrix[2][0] = turn;
				return point(50,250);
			} else {
				return getInput(turn);
			}
		case '2':
			if (matrix[2][1] == '-'){
				matrix[2][1] = turn;
				return point(150,250);
			} else {
				return getInput(turn);
			}
		case '3':
			if (matrix[2][2] == '-'){
				matrix[2][2] = turn;
				return point(250,250);
			} else {
				return getInput(turn);
			}
		case '4':
			if (matrix[1][0] == '-'){
				matrix[1][0] = turn;
				return point(50,150);
			} else {
				return getInput(turn);
			}
		case '5':
			if (matrix[1][1] == '-'){
				matrix[1][1] = turn;
				return point(150,150);
			} else {
				return getInput(turn);
			}
		case '6':
			if (matrix[1][2] == '-'){
				matrix[1][2] = turn;
				return point(250,150);
			} else {
				return getInput(turn);
			}
		case '7':
			if (matrix[0][0] == '-'){
				matrix[0][0] = turn;
				return point(50,50);
			} else {
				return getInput(turn);
			}
		case '8':
			if (matrix[0][1] == '-'){
				matrix[0][1] = turn;
				return point(150,50);
			} else {
				return getInput(turn);
			}
		case '9':
			if (matrix[0][2] == '-'){
				matrix[0][2] = turn;
				return point(250,50);
			} else {
				return getInput(turn);
			}
		case 27:
			closeBoard();
			printf("\nThe Game has Ended.\nHope you liked playing it.\nPress any key to exit..");
			getch();
			exit(1);
			return getInput(turn);
		default:
			return getInput(turn);
	}
}

void drawAt(int c, char turn){
	switch(c){
		case 1:
			matrix[2][0] = turn;
			turn == 'X' ? drawX(point(50,250)) : drawO(point(50,250));
			break;
		case 2:
			matrix[2][1] = turn;
			turn == 'X' ? drawX(point(150,250)) : drawO(point(150,250));
			break;
		case 3:
			matrix[2][2] = turn;
			turn == 'X' ? drawX(point(250,250)) : drawO(point(250,250));
			break;
		case 4:
			matrix[1][0] = turn;
			turn == 'X' ? drawX(point(50,150)) : drawO(point(50,150));
			break;
		case 5:
			matrix[1][1] = turn;
			turn == 'X' ? drawX(point(150,150)) : drawO(point(150,150));
			break;
		case 6:
			matrix[1][2] = turn;
			turn == 'X' ? drawX(point(250,150)) : drawO(point(250,150));
			break;
		case 7:
			matrix[0][0] = turn;
			turn == 'X' ? drawX(point(50,50)) : drawO(point(50,50));
			break;
		case 8:
			matrix[0][1] = turn;
			turn == 'X' ? drawX(point(150,50)) : drawO(point(150,50));
			break;
		case 9:
			matrix[0][2] = turn;
			turn == 'X' ? drawX(point(250,50)) : drawO(point(250,50));
			break;
	}
}

void drawO (point p){
	circle(p.x, p.y, 30);
}
void drawX (point p){
	line(p.x-30, p.y-30, p.x+30, p.y+30);
	line(p.x+30, p.y-30, p.x-30, p.y+30);
}

int hasWon(char turn, int draw){
	
	for(int i = 0; i<3; i++){
		//horizontal rows
		if(matrix[i][0]==turn && matrix[i][1]==turn && matrix[i][2]==turn){
			if(draw) line(10, 50+i*100, 290, 50+i*100);
			return 1;
		}
		//vertical columns
		if(matrix[0][i]==turn && matrix[1][i]==turn && matrix[2][i]==turn){
			if(draw) line(50+i*100, 10, 50+i*100, 290);
			return 1;
		}
	}
	
	//diagonals
	if(matrix[0][0]==turn && matrix[1][1]==turn && matrix[2][2]==turn){
		if(draw) line(10,10, 290,290);
		return 1;
	}
	if(matrix[0][2]==turn && matrix[1][1]==turn && matrix[2][0]==turn){
		if(draw) line(290,10, 10, 290);
		return 1;
	}
	
	//else
	return 0;
}
int hasWon(char turn) {
	return hasWon(turn, 1);
}

int hasTied(){
	int hasTiedint = 1;
	
	for(int i=0; i<3;i++){
		for(int j=0; j<3; j++){
			if(matrix[i][j] == '-')
				hasTiedint=0;
		}
	}
	
	return hasTiedint;
}

void makeWin(char winner) {
	char winText[100];
	
	if(winner == 'X')
		score.winsX();
	else
		score.winsO();
	
	score.drawScoreboard();
	
	sprintf(winText, "The Game is Won by \"%c\"", winner);
	outtextxy(400, 100, winText);
	outtextxy(400, 200, "Press Enter to Restart");
	outtextxy(400, 212, "or");
	outtextxy(400, 225, "Esc to Exit...");
	while(1){
		char c =getch();
		if(c == '\n' || c=='\r'  || c == EOF){
			if(vsComputer)
				comp.gamePlay();
			else
				initGame();
			break;
		} else if(c == 27) {
			closeBoard();
			
			printf("\nThe Game has Ended.\nHope you liked playing it.\nPress any key to exit..");
			getch();
			break;
		}
	}
}

void makeTie() {
	outtextxy(400, 100, "It's a Tie ! Try Again ?");
	outtextxy(400, 200, "Press Enter to Restart");
	outtextxy(400, 212, "or");
	outtextxy(400, 225, "Esc to Exit...");
	while(1){
		char c =getch();
		if(c == '\n' || c=='\r'  || c == EOF){
			if(vsComputer)
				comp.gamePlay();
			else
				initGame();
			break;
		} else if(c == 27) {
			closeBoard();
			
			printf("\nThe Game has Ended.\nHope you liked playing it.\nPress any key to exit..");
			getch();
			break;
		}
	}
}

void initGame(){
	createBoard();
	
	int i = 1;
	while(1){
		if(i){
			drawX(getInput('X'));
			if(hasWon('X')){
				makeWin('X');
				break;
			}
				
		} else {
			drawO(getInput('O'));
			if(hasWon('O')){
				makeWin('O');
				break;
			}
		}
		if(hasTied()){
			makeTie();
			break;
		}
		i++;
		i%=2;
		playerturn = i;
		score.drawScoreboard();
	}
}

int main () {
	
	int ch;
	clrscr();
	printf("\nWelcome to the Game of Tic Tac Toe.\n\n");
	
	printf("Game Created By \n");
	printf("525\tKunal Gulati\n");
	printf("531\tAkshay Naik\n");
	printf("555\tShrey Javia\n");
	printf("565\tVaibhav Mishra\n");
	printf("569\tZainulabuddin Mohammad\n");
	
	printf("\n\n");
	
	printf("1 - Player vs Player \n2 - Player vs Computer\n");
	printf("Enter your Choice:");
	scanf("%d", &ch);
	
	if(ch == 1){
		
		printf("Enter player 1 name: ");
		scanf("%s", &player1);
		
		printf("Enter player 2 name: ");
		scanf("%s", &player2);
		
		printf("Press any key to begin ...");
		getch();
		initGame();
		
	} else {
		
		printf("You want to start ? (1-Yes or 2-No): ");
		scanf("%d", &ch);
		
		if(ch == 1){
			
			printf("Enter your name: ");
			scanf("%s", &player1);
			
			strcpy(player2, "Computer");
			comp = Computer(1);
			
			printf("Press any key to begin ...");
			getch();
			comp.gamePlay();
			
		} else {
			
			printf("Enter your name: ");
			scanf("%s", &player2);
			
			strcpy(player1, "Computer");
			comp = Computer(0);
			
			printf("Press any key to begin ...");
			getch();
			comp.gamePlay();
			
		}
	}
	
	return 0;
}