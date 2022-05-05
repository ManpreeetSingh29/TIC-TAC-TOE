#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<string.h>

using namespace std;

#define N 3

void createNewBoard(char[N][N]);									//All
void userMove(int *, int *, int *);									//Shreya
void printBoard(char[N][N]);										//Shreya
void compPlaysRandom(char[N][N], int * , int *);					//Manpreet
int compPlaysToWin(char [N][N], int * , int * );					//Manpreet
int generateComputerMove(char board[N][N], int *, int *, char);		//Nripesh
bool isGameWon(char [N][N], char);									//Manpreet
bool isInputValid(int, int, int);									//Nripesh
bool isBoardFull(char board[N][N]);									//Manpreet
int compPlaysToBlock(char [N][N], int * , int * );					//Manpreet
void computerIsThinking();											//Nripesh
void intro(string, string);											//Shreya
char gameDifficulty();												//Nripesh
int opponent();														//Nripesh
bool wantRematch();													//Nripesh
void frontPage(); 													//Shreya
bool wishToQuit();													//Shreya											

using namespace std;

int main(){
	frontPage();
	int spotTaken=0, compRow, compCol, userRow, userCol, firstMove=1, stepsWon=0;
	char board[N][N], winner = 'N', difficulty;
	string name = "You", name2 = "Computer";
	
	while(true){	//For returning to main menu or quiting
		cout<<"\t\tTIC TAC TOE\n";
		srand((int) time (0));
		int scoreP1 = 0, scoreP2 = 0, opp = opponent();
		if(opp){
			cout<<"\n--> Please Enter your name : ";
			cin.ignore();
			getline(cin,name);
			//cin>>name;
			cout<<endl;
			difficulty = gameDifficulty();
		}
		else{
			cout<<"\n--> Please Enter Player 1 name : ";
			cin.ignore();
			getline(cin,name);
//			cin>>name;
			cout<<endl;
			cout<<"\n--> Please Enter Player 2 name : ";
			getline(cin,name2);
//			cin>>name2;
			cout<<endl;
		}
		while(true){	//For continuing the game if player wants a rematch
			intro(name, name2);
			createNewBoard(board);
			winner ='N';
			while(!isBoardFull(board) && winner == 'N'){
				cout<<"\n\t\t    Score\n\n\t  "<<name<<" : "<<scoreP1<<"\t\t"<<name2<<" : "<<scoreP2<<endl;
				if(firstMove){
					spotTaken = 0;
					while(!spotTaken){	//check if that spot is already occupied or not	
						cout<<endl<<name<<" your turn:\n\n";
						userMove(&userRow, &userCol, &stepsWon); //read input from user
						while(!isInputValid(userRow, 1, 3) || !isInputValid(userCol, 1, 3)){	//check if user input is between 1 and 3
							cout<<"That's an invalid Spot!!! Please select a row and column between 1 and 3\n";
							userMove(&userRow, &userCol, &stepsWon);
						}
						if(board[userRow-1][userCol-1] == ' '){
							board[userRow-1][userCol-1] = 'X';	//update the specified row and column with user's symbol
							spotTaken = 1;
						}
						else{
							cout<<"That spot is taken. Please select another one.\n";
							spotTaken = 0;
						}
					}
					intro(name, name2);
					cout<<"\n";
					printBoard(board);
					
					if(isGameWon(board, 'X')){
						winner = 'X';
					}
				}
				else{
					if (!isBoardFull(board)){
					spotTaken = 0;
					while(!spotTaken){
						if(opp){
							spotTaken = generateComputerMove(board, &compRow, &compCol, difficulty);
							if(spotTaken){
								break;
							}
							if (board[compRow][compCol] == ' '){ 
									board[compRow][compCol] = 'O'; 
									spotTaken = 1; 
								}
							else{ 
								spotTaken = 0;
							}	
						}
						else{
							cout<<endl<<name2<<" your turn:\n\n";
							userMove(&userRow, &userCol, &stepsWon); //read input from user
							while(!isInputValid(userRow, 1, 3) || !isInputValid(userCol, 1, 3)){	//check if user input is between 1 and 3
								cout<<"That's an invalid Spot!!! Please select a row and column between 1 and 3\n"<<endl;
								userMove(&userRow, &userCol, &stepsWon);
							}
							if(board[userRow-1][userCol-1] == ' '){
								board[userRow-1][userCol-1] = 'O';	//update the specified row and column with user's symbol
								spotTaken = 1;
							}
							else{
								cout<<"That spot is taken. Please select another one.\n";
								spotTaken = 0;
							}
						}
					}
					if(opp){
						computerIsThinking();
						cout<<"\nComputer choose row "<<compRow+1<<" and column "<<compCol+1<<endl;
						Sleep(3000);
					}
					
					if(isGameWon(board, 'O')){
						winner = 'O';
					}
				}
				
				intro(name, name2);
				cout<<"\n";
				printBoard(board);
				}
				
				
				if(opp){
					if(winner == 'X'){
						cout<<"\nCongrats "<<name<<" !!! You won against Computer.\n";
						++scoreP1;
					}
					else if(winner == 'O'){
						cout<<"\nAlas ! "<<name<<" you were defeated by computer.\n";
						++scoreP2;
					}
					else if(isBoardFull(board) && winner == 'N'){
						cout<<"\nTHE MATCH WAS DRAWN";
					}
				}
				
				else{
					if(winner == 'X'){
						cout<<"\nCongrats "<<name<<" !!! You won against "<<name2<<".\n";
						++scoreP1;
					}
					else if(winner == 'O'){
						cout<<"\nCongrats "<<name2<<" !!! You won against "<<name<<".\n";
						++scoreP2;
						}
					else if(isBoardFull(board) && winner == 'N'){
						cout<<"\nTHE MATCH WAS DRAWN";
					}
				}
				firstMove = !firstMove;
			}
			if(!wantRematch()){
				break;
			}
		}
		if(wishToQuit()){
			break;
		}
		system("cls");
	}
	return 0;
}

void frontPage(){
	cout<<"\n*******************************************************************************\n";
	cout<<"\n\n¦¦¦¦¦¦¦¦ ¦¦ ¦¦¦¦¦¦¦     ¦¦¦¦¦¦¦¦  ¦¦¦¦¦  ¦¦¦¦¦¦¦     ¦¦¦¦¦¦¦¦  ¦¦¦¦¦¦  ¦¦¦¦¦¦¦ \n   ¦¦    ¦¦ ¦¦             ¦¦    ¦¦   ¦¦ ¦¦             ¦¦    ¦¦    ¦¦ ¦¦      \n   ¦¦    ¦¦ ¦¦             ¦¦    ¦¦¦¦¦¦¦ ¦¦             ¦¦    ¦¦    ¦¦ ¦¦¦¦¦   \n   ¦¦    ¦¦ ¦¦             ¦¦    ¦¦   ¦¦ ¦¦             ¦¦    ¦¦    ¦¦ ¦¦      \n   ¦¦    ¦¦ ¦¦¦¦¦¦¦        ¦¦    ¦¦   ¦¦ ¦¦¦¦¦¦¦        ¦¦     ¦¦¦¦¦¦  ¦¦¦¦¦¦¦ \n                                                                           \n";
	cout<<"\n*******************************************************************************\n";
	cout<<"\n++++++++++++++++++++++++++++\tTEAM MEMBERS\t++++++++++++++++++++++++++++++++\n";
	cout<<"\n\n\t\t--> MANPREET SINGH : 20BCS6444"<<endl;
	cout<<"\n\t\t--> NRIPESH KUMAR  : 20BCS6465"<<endl;
	cout<<"\n\t\t--> SHREYA KOHLI   : 20BCS6451\n\n"<<endl;
	cout<<"Press any key to continue";
	getchar();
	system("cls");
}

void createNewBoard(char arr[N][N]){
	cout<<endl;
	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			arr[i][j]=' ';
		}
	}
	for(int i =0 ; i<3 ; i++){
		cout<<"\t\t";
		for(int j=0 ; j<3 ; j++){
			if(j<2)
			cout<<" "<<arr[i][j]<<" | ";
			else
			cout<<" "<<arr[i][j]<<endl;
		}
		if(i<2)
		cout<<"\t\t-----------\n";
	}
}

void printBoard(char arr[N][N]){
	for(int i =0 ; i<3 ; i++){
		cout<<"\t\t";
		for(int j=0 ; j<3 ; j++){
			if(j<2)
			cout<<" "<<arr[i][j]<<" | ";
			else
			cout<<" "<<arr[i][j]<<endl;
		}
		if(i<2)
		cout<<"\t\t-----------\n";
	}
	
}

void userMove( int *userRow, int *userCol , int *stepsWon){
	cout<<"Enter Row number   : ";
	cin>>*userRow;
	cout<<"Enter Column number: ";
	cin>>*userCol;
	cout<<"\nYou choose row "<<*userRow<<" and column "<<*userCol<<"\n"<<endl;
	*stepsWon+=1;
}

bool isInputValid(int a, int i, int j){
	if(a>=i && a<=j){
		return 1;
	}
	else{
		return 0;
	}
}

bool isBoardFull (char board [N][N]){
	for(int i=0; i<3; i++){
		for(int j=0; j<3; j++){
			if( board[i][j] == ' '){
				return 0;
			}
		}
	}
	return 1;
}

int generateComputerMove (char board[N][N], int * computerRow, int * computerCol, char d){ 
	if(d == 'h'){
		int winningSpot = 0; 
		winningSpot = compPlaysToWin(board, computerRow, computerCol); 
		if (!winningSpot) {
			int blocked = 0; 
			blocked = compPlaysToBlock(board, computerRow, computerCol);
			if (blocked == 0){
				compPlaysRandom(board, computerRow, computerCol); 
			} 
			return blocked; 
		} 
		return winningSpot;	
	}
	else if(d == 'm'){
		int winningSpot = 0; 
		winningSpot = compPlaysToWin(board, computerRow, computerCol); 
		if (!winningSpot) {
			compPlaysRandom(board, computerRow, computerCol); 
		} 
		return winningSpot;
	}
	else if (d == 'e'){
		compPlaysRandom(board, computerRow, computerCol);
		return 0;
	}
}

void compPlaysRandom (char board[N][N], int * cRow, int * cCol){
	*cRow = rand()%3;
	*cCol = rand()%3;
	
	if(board[*cRow][*cCol] == ' ')
		board[*cRow][*cCol] == 'X';
	else
		compPlaysRandom(board, cRow, cCol);
}

int compPlaysToBlock(char arr[N][N], int *cRow, int *cCol){
	//case 1
	if(arr[0][0]==' ' && arr[0][1]=='X' && arr[0][2]=='X'){
		arr[0][0] = 'O';
		*cRow = 0;
		*cCol = 0;
		return 1;		
	}
	else if(arr[0][0]=='X' && arr[0][1]==' ' && arr[0][2]=='X'){
		arr[0][1] = 'O';
		*cRow = 0;
		*cCol = 1;
		return 1;		
	}
	else if(arr[0][0]=='X' && arr[0][1]=='X' && arr[0][2]==' '){
		arr[0][2] = 'O';
		*cRow = 0;
		*cCol = 2;
		return 1;		
	}
	
	//case 2
	else if(arr[1][0]==' ' && arr[1][1]=='X' && arr[1][2]=='X'){
		arr[1][0] = 'O';
		*cRow = 1;
		*cCol = 0;
		return 1;		
	}
	else if(arr[1][0]=='X' && arr[1][1]==' ' && arr[1][2]=='X'){
		arr[1][1] = 'O';
		*cRow = 1;
		*cCol = 1;
		return 1;		
	}
	else if(arr[1][0]=='X' && arr[1][1]=='X' && arr[1][2]==' '){
		arr[1][2] = 'O';
		*cRow = 1;
		*cCol = 2;
		return 1;		
	}
	//case 3
	else if(arr[2][0]==' ' && arr[2][1]=='X' && arr[2][2]=='X'){
		arr[2][0] = 'O';
		*cRow = 2;
		*cCol = 0;
		return 1;		
	}
	else if(arr[2][0]=='X' && arr[2][1]==' ' && arr[2][2]=='X'){
		arr[2][1] = 'O';
		*cRow = 2;
		*cCol = 1;
		return 1;		
	}
	else if(arr[2][0]=='X' && arr[2][1]=='X' && arr[2][2]==' '){
		arr[2][2] = 'O';
		*cRow = 2;
		*cCol = 2;
		return 1;		
	}
	//case 4
	else if(arr[0][0]==' ' && arr[1][0]=='X' && arr[2][0]=='X'){
		arr[0][0] = 'O';
		*cRow = 0;
		*cCol = 0;
		return 1;		
	}
	else if(arr[0][0]=='X' && arr[1][0]==' ' && arr[2][0]=='X'){
		arr[1][0] = 'O';
		*cRow = 1;
		*cCol = 0;
		return 1;		
	}
	else if(arr[0][0]=='X' && arr[1][0]=='X' && arr[2][0]==' '){
		arr[2][0] = 'O';
		*cRow = 2;
		*cCol = 0;
		return 1;		
	}//case 5
	else if(arr[0][1]==' ' && arr[1][1]=='X' && arr[2][1]=='X'){
		arr[0][1] = 'O';
		*cRow = 0;
		*cCol = 1;
		return 1;		
	}
	else if(arr[0][1]=='X' && arr[1][1]==' ' && arr[2][1]=='X'){
		arr[1][1] = 'O';
		*cRow = 1;
		*cCol = 1;
		return 1;		
	}
	else if(arr[0][1]=='X' && arr[1][1]=='X' && arr[2][1]==' '){
		arr[2][1] = 'O';
		*cRow = 2;
		*cCol = 1;
		return 1;		
	}
	//case 6
	else if(arr[0][2]==' ' && arr[1][2]=='X' && arr[2][2]=='X'){
		arr[0][2] = 'O';
		*cRow = 0;
		*cCol = 2;
		return 1;		
	}
	else if(arr[0][2]=='X' && arr[1][2]==' ' && arr[2][2]=='X'){
		arr[1][2] = 'O';
		*cRow = 1;
		*cCol = 2;
		return 1;		
	}
	else if(arr[0][2]=='X' && arr[1][2]=='X' && arr[2][2]==' '){
		arr[2][2] = 'O';
		*cRow = 2;
		*cCol = 2;
		return 1;		
	}
	
	//case 7
	else if(arr[0][0]==' ' && arr[1][1]=='X' && arr[2][2]=='X'){
		arr[0][0] = 'O';
		*cRow = 0;
		*cCol = 0;
		return 1;		
	}
	else if(arr[0][0]=='X' && arr[1][1]==' ' && arr[2][2]=='X'){
		arr[1][1] = 'O';
		*cRow = 1;
		*cCol = 1;
		return 1;		
	}
	else if(arr[0][0]=='X' && arr[1][1]=='X' && arr[2][2]==' '){
		arr[2][2] = 'O';
		*cRow = 2;
		*cCol = 2;
		return 1;		
	}
	//case 8
	else if(arr[0][2]==' ' && arr[1][1]=='X' && arr[2][0]=='X'){
		arr[0][2] = 'O';
		*cRow = 0;
		*cCol = 2;
		return 1;		
	}
	else if(arr[0][2]=='X' && arr[1][1]==' ' && arr[2][0]=='X'){
		arr[1][1] = 'O';
		*cRow = 1;
		*cCol = 1;
		return 1;		
	}
	else if(arr[0][2]=='X' && arr[1][1]=='X' && arr[2][0]==' '){
		arr[2][0] = 'O';
		*cRow = 2;
		*cCol = 0;
		return 1;		
	}
	else{
		return 0;
	}
}

int compPlaysToWin(char arr[N][N], int *cRow , int *cCol ){
	//case 1
	if(arr[0][0]==' ' && arr[0][1]=='O' && arr[0][2]=='O'){
		arr[0][0] = 'O';
		*cRow = 0;
		*cCol = 0;
		return 1;		
	}
	else if(arr[0][0]=='O' && arr[0][1]==' ' && arr[0][2]=='O'){
		arr[0][1] = 'O';
		*cRow = 0;
		*cCol = 1;
		return 1;		
	}
	else if(arr[0][0]=='O' && arr[0][1]=='O' && arr[0][2]==' '){
		arr[0][2] = 'O';
		*cRow = 0;
		*cCol = 2;
		return 1;		
	}
	
	//case 2
	else if(arr[1][0]==' ' && arr[1][1]=='O' && arr[1][2]=='O'){
		arr[1][0] = 'O';
		*cRow = 1;
		*cCol = 0;
		return 1;		
	}
	else if(arr[1][0]=='O' && arr[1][1]==' ' && arr[1][2]=='O'){
		arr[1][1] = 'O';
		*cRow = 1;
		*cCol = 1;
		return 1;		
	}
	else if(arr[1][0]=='O' && arr[1][1]=='O' && arr[1][2]==' '){
		arr[1][2] = 'O';
		*cRow = 1;
		*cCol = 2;
		return 1;		
	}
	//case 3
	else if(arr[2][0]==' ' && arr[2][1]=='O' && arr[2][2]=='O'){
		arr[2][0] = 'O';
		*cRow = 2;
		*cCol = 0;
		return 1;		
	}
	else if(arr[2][0]=='O' && arr[2][1]==' ' && arr[2][2]=='O'){
		arr[2][1] = 'O';
		*cRow = 2;
		*cCol = 1;
		return 1;		
	}
	else if(arr[2][0]=='O' && arr[2][1]=='O' && arr[2][2]==' '){
		arr[2][2] = 'O';
		*cRow = 2;
		*cCol = 2;
		return 1;		
	}
	//case 4
	else if(arr[0][0]==' ' && arr[1][0]=='O' && arr[2][0]=='O'){
		arr[0][0] = 'O';
		*cRow = 0;
		*cCol = 0;
		return 1;		
	}
	else if(arr[0][0]=='O' && arr[1][0]==' ' && arr[2][0]=='O'){
		arr[1][0] = 'O';
		*cRow = 1;
		*cCol = 0;
		return 1;		
	}
	else if(arr[0][0]=='O' && arr[1][0]=='O' && arr[2][0]==' '){
		arr[2][0] = 'O';
		*cRow = 2;
		*cCol = 0;
		return 1;		
	}//case 5
	else if(arr[0][1]==' ' && arr[1][1]=='O' && arr[2][1]=='O'){
		arr[0][1] = 'O';
		*cRow = 0;
		*cCol = 1;
		return 1;		
	}
	else if(arr[0][1]=='O' && arr[1][1]==' ' && arr[2][1]=='O'){
		arr[1][1] = 'O';
		*cRow = 1;
		*cCol = 1;
		return 1;		
	}
	else if(arr[0][1]=='O' && arr[1][1]=='O' && arr[2][1]==' '){
		arr[2][1] = 'O';
		*cRow = 2;
		*cCol = 1;
		return 1;		
	}
	//case 6
	else if(arr[0][2]==' ' && arr[1][2]=='O' && arr[2][2]=='O'){
		arr[0][2] = 'O';
		*cRow = 0;
		*cCol = 2;
		return 1;		
	}
	else if(arr[0][2]=='O' && arr[1][2]==' ' && arr[2][2]=='O'){
		arr[1][2] = 'O';
		*cRow = 1;
		*cCol = 2;
		return 1;		
	}
	else if(arr[0][2]=='O' && arr[1][2]=='O' && arr[2][2]==' '){
		arr[2][2] = 'O';
		*cRow = 2;
		*cCol = 2;
		return 1;		
	}
	
	//case 7
	else if(arr[0][0]==' ' && arr[1][1]=='O' && arr[2][2]=='O'){
		arr[0][0] = 'O';
		*cRow = 0;
		*cCol = 0;
		return 1;		
	}
	else if(arr[0][0]=='O' && arr[1][1]==' ' && arr[2][2]=='O'){
		arr[1][1] = 'O';
		*cRow = 1;
		*cCol = 1;
		return 1;		
	}
	else if(arr[0][0]=='O' && arr[1][1]=='O' && arr[2][2]==' '){
		arr[2][2] = 'O';
		*cRow = 2;
		*cCol = 2;
		return 1;		
	}
	//case 8
	else if(arr[0][2]==' ' && arr[1][1]=='O' && arr[2][0]=='O'){
		arr[0][2] = 'O';
		*cRow = 0;
		*cCol = 2;
		return 1;		
	}
	else if(arr[0][2]=='O' && arr[1][1]==' ' && arr[2][0]=='O'){
		arr[1][1] = 'O';
		*cRow = 1;
		*cCol = 1;
		return 1;		
	}
	else if(arr[0][2]=='O' && arr[1][1]=='O' && arr[2][0]==' '){
		arr[2][0] = 'O';
		*cRow = 2;
		*cCol = 0;
		return 1;		
	}
	else{
		return 0;
	}
}

bool isGameWon(char arr[N][N], char b){
	if(arr[0][0]==arr[0][1] && arr[0][1]==arr[0][2] && arr[0][1]==b){
			return 1;		
	}
	else if(arr[1][0]==arr[1][1] && arr[1][1]==arr[1][2] && arr[1][0]==b){
			return 1;
	}
	else if(arr[2][0]==arr[2][1] && arr[2][1]==arr[2][2] && arr[2][0]==b){
			return 1;	
	}
	else if(arr[0][0]==arr[1][0] && arr[1][0]==arr[2][0] && arr[0][0]==b){
			return 1;	
	}
	else if(arr[0][1]==arr[1][1] && arr[1][1]==arr[2][1] && arr[0][1]==b){
			return 1;		
	}
	else if(arr[0][2]==arr[1][2] && arr[1][2]==arr[2][2] && arr[0][2]==b){
			return 1;		
	}
	else if(arr[0][0]==arr[1][1] && arr[1][1]==arr[2][2] && arr[0][0]==b){
			return 1;		
	}
	else if(arr[0][2]==arr[1][1] && arr[1][1]==arr[2][0] && arr[0][2]==b){
			return 1;		
	}
	else{
		return 0;
	}
}

void computerIsThinking(){
	int dot=0;
	dot = rand()%4;
	cout<<"\nComputer is thinking";
	for(int i=0; i<dot; i++){
		Sleep(800);
		cout<<".";
	}
	Sleep(800);
	cout<<".\n";
}

void intro(string n1, string n2){
	system("cls");
	cout<<"\t\tTIC TAC TOE\n\n"<<n1<<" your symbol is 'X' and "<<n2<<" will use 'O'"<<endl;	
}

char gameDifficulty(){	//return e for easy mode and h for difficult mode
	string c;
	cout<<"--> Enter 'E' for easy, 'M' for medium and 'H' for difficult mode : ";
	cin>>c;
	if(c == "E" || c == "e" || c == "Easy" || c == "easy" || c == "EASY"){
		return 'e';
	}
	else if(c == "M" || c == "m" || c == "Medium" || c == "medium" || c == "MEDIUM"){
		return 'm';
	}
	else if(c == "H" || c == "h" || c == "Hard" || c == "hard" || c == "HARD"){
		return 'h';
	}
	else{
		cout<<"Invalid input! Try again\n";
		gameDifficulty();
	}
}

int opponent(){			//return 0 for player and 1 for computer
	string c;
	cout<<"\n--> Select you opponent : \n1.Player\n2.Computer\n"<<endl;
	cin>>c;
	if(c == "1" || c == "P" || c == "p" || c == "Player" || c == "player" || c == "Player" || c=="1."){
		return 0;
	}
	else if(c == "2" || c == "C" || c == "c" || c == "Computer" || c == "computer" || c == "COMPUTER" || c=="2."){
		return 1;
	}
	else{
		cout<<"Invalid Input!!! Try Again\n";
		opponent();
	}
}

bool wantRematch(){
	string rematch;
	cout<<"\nWant a rematch??\nEnter Yes or No : ";
	cin>>rematch;
	if(rematch == "Y" || rematch == "y" || rematch == "yes" || rematch == "YES" || rematch == "Yes"){
		return 1;
	}
	else if(rematch == "N" || rematch == "n" || rematch == "no" || rematch == "NO" || rematch == "No"){
		return 0;
	}
	else{
		cout<<"Invalid Input try again.";
		wantRematch();
	}
}

bool wishToQuit(){
	string quit;
	cout<<"\nDo you wish to quit?\nEnter Yes to quit and No to return to main menu : ";
	cin>>quit;
	if(quit == "Y" || quit == "y" || quit == "yes" || quit == "YES" || quit == "Yes"){
		return 1;
	}
	else if(quit == "N" || quit == "n" || quit == "no" || quit == "NO" || quit == "No"){
		return 0;
	}
	else{
		cout<<"Invalid Input try again.";
		wishToQuit();
	}
}


