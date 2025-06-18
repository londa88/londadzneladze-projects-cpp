#include <iostream>
#include "gboggle.h"
#include "grid.h"
#include "gwindow.h"
#include "lexicon.h"
#include "random.h"
#include "simpio.h"
#include "Set.h"
using namespace std;

/* Constants */
Lexicon lex;
const int BOGGLE_WINDOW_WIDTH = 650;
const int BOGGLE_WINDOW_HEIGHT = 350;


void welcome();
void giveInstructions();
void fillTheBoard(Grid<char> &board);
void humanTurn(Grid<char> &board, Lexicon lex);
bool wordIsValid(Lexicon lex, string word, Grid<char> &board, Set<string> words);
bool isPossibleToMade(Grid<char> &board, string word);
bool helper(Grid<char> &board, int row, int col, int index, string word, Grid<bool> &usedCharIndex);
void computerFound( Grid<char> &board,int row, int col, string curr,Lexicon lex, Set<string> &compAlreadyFound, Grid<bool> &compUsedCharIndex);
void computerTurn(Grid<char> &board, Lexicon lex);
void playTheBoggle();
void swapPlaces(Vector<string> &allTheOptions);
void formateBoard(Grid<char> &board, Vector<string> allTheOptions);
bool wantsToContinue();
const string STANDARD_CUBES[16]  = {
    "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
    "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
    "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
    "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};
 
const string BIG_BOGGLE_CUBES[25]  = {
    "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
    "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
    "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
    "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
    "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

/* Function prototypes */


/* Main program */

int main() {
    GWindow gw(BOGGLE_WINDOW_WIDTH, BOGGLE_WINDOW_HEIGHT);
    initGBoggle(gw);
	lex.addWordsFromFile("EnglishWords.dat");
    welcome();
    giveInstructions();
	playTheBoggle();	
    return 0;
}

void playTheBoggle(){
	while(true){
     int  size=getInteger("Choose 5x5 or 4x4, enter 4 or 5 ");
     drawBoard(size,size);
     Grid<char> board(size,size);
	 Lexicon lex;
	 lex.addWordsFromFile("EnglishWords.dat");
	 fillTheBoard(board);
	 humanTurn(board,lex);
	 computerTurn(board,lex);
	 if(!wantsToContinue()){
		 break;
	 }
	 playTheBoggle();
	}

}
bool wantsToContinue(){
	string s=getLine("want to play again? enter yes or now: ");
	if(s=="yes"){
		return true;
	}
	return false;
}
void fillTheBoard(Grid<char> &board){
     Vector<string> allTheOptions;
	 if(board.numRows()==4){
	 for(int i=0 ;i<16;i++){
		 allTheOptions.add(STANDARD_CUBES[i]);
	 }
	 }
	 if(board.numRows()==5){
	 for(int i=0 ;i<25;i++){
		 allTheOptions.add(BIG_BOGGLE_CUBES[i]);
	 }
	 }
	 swapPlaces(allTheOptions);
	 formateBoard(board, allTheOptions);

}
void swapPlaces(Vector<string> &allTheOptions){
 for(int i=0; i<allTheOptions.size(); i++){
		 int index=randomInteger(0, allTheOptions.size()-1);
         Vector<string> temp=allTheOptions;
		 allTheOptions[i]=temp[index];
		 allTheOptions[index]=temp[i];
	 }
}
void formateBoard(Grid<char> &board, Vector<string> allTheOptions){
 for(int i=0 ;i<board.numRows(); i++){
		 for(int j=0; j<board.numCols();j++){
		     int index=randomInteger(0, allTheOptions[i].size()-1);
			 board[i][j]=allTheOptions[i][index];
			 labelCube(i,j,allTheOptions[i][index]);
		 }
	 }
}


void humanTurn(Grid<char> &board, Lexicon lex){
	Set<string> words;
	while(true){
		string word=getLine("enter the word");
		word=toUpperCase(word);
	if(word==""){
		return; 
	}
	if(wordIsValid(lex, word, board, words)){
		words.add(word);
		recordWordForPlayer(word, HUMAN);
	}
	}
}
bool wordIsValid(Lexicon lex, string word, Grid<char> &board, Set<string> words){
	if(lex.contains(word)&&word.size()>=4&&!words.contains(word)&&isPossibleToMade(board, word)){
		for(int i=0; i<board.numRows();i++)
			for(int j=0;j<board.numCols();j++)
				highlightCube(i, j, false);
		return true;
	}
	return false;
}
bool isPossibleToMade(Grid<char> &board, string word){
	Grid<bool> usedCharIndex(board.numRows(), board.numCols());
	for(int i=0; i<board.numRows();i++)
		for(int j=0;j<board.numCols();j++)
			usedCharIndex[i][j] = false;
	for(int i=0; i<board.numRows();i++){
		for(int j=0; j<board.numCols(); j++){
			if(helper(board, i, j, 0, word, usedCharIndex)){
				return true;
			}
		}
	}
	return false;
		
}
bool helper(Grid<char> &board, int row, int col, int index, string word, Grid<bool> &usedCharIndex) {
	if(!board.inBounds(row, col)|| usedCharIndex[row][col]){
		return false;
	}
    if (index == word.size()) {
        return true;
    }
    if (board[row][col] != word[index]) {
        return false;
    }
	usedCharIndex[row][col] = true;
	bool ans = false;
	ans = helper(board, row, col - 1, index + 1, word,usedCharIndex) ||
           helper(board, row, col + 1, index + 1, word,usedCharIndex) ||
           helper(board, row + 1, col - 1, index + 1, word,usedCharIndex) ||
           helper(board, row + 1, col + 1, index + 1, word,usedCharIndex) ||
           helper(board, row - 1, col, index + 1, word,usedCharIndex) ||
           helper(board, row - 1, col - 1, index + 1, word,usedCharIndex) ||
           helper(board, row - 1, col + 1, index + 1, word,usedCharIndex) ||
           helper(board, row + 1, col, index + 1, word,usedCharIndex);
	if(ans)
		highlightCube(row, col, true);
	return ans;
}
void computerTurn(Grid<char> &board, Lexicon lex){
	for(int i=0; i<board.numRows();i++)
		for(int j=0;j<board.numCols();j++)
			highlightCube(i, j, false);
	Set<string> compAlreadyFound;
	Grid<bool> compUsedCharIndex(board.numRows(), board.numCols());
	for(int i=0; i<board.numRows();i++)
		for(int j=0;j<board.numCols();j++)
			compUsedCharIndex[i][j] = false;
	for(int i=0; i<board.numRows();i++){
		for(int j=0;j<board.numCols();j++){
			computerFound(board, i,j, "", lex, compAlreadyFound, compUsedCharIndex);
		}
	}
	foreach(string word in compAlreadyFound){
		recordWordForPlayer(word, COMPUTER);
	}
}
void computerFound( Grid<char> &board,int row, int col, string curr,Lexicon lex, Set<string> &compAlreadyFound, Grid<bool> &compUsedCharIndex){
	if(lex.contains(curr)&&curr.size()>=4&&!compAlreadyFound.contains(curr)){
		compAlreadyFound.add(curr);
		return;
	}
	if(!lex.containsPrefix(toLowerCase(curr)) || !board.inBounds(row, col)|| compUsedCharIndex[row][col]){
		return;
	}
	curr+=board.get(row, col);
	compUsedCharIndex[row][col] = true;
	computerFound(board, row, col - 1, curr, lex, compAlreadyFound, compUsedCharIndex);
	computerFound(board, row, col + 1, curr, lex, compAlreadyFound, compUsedCharIndex);
	computerFound(board, row + 1, col - 1, curr, lex, compAlreadyFound, compUsedCharIndex);
	computerFound(board, row + 1, col + 1, curr, lex, compAlreadyFound, compUsedCharIndex);
	computerFound(board, row - 1, col, curr, lex, compAlreadyFound, compUsedCharIndex);
	computerFound(board, row - 1, col - 1, curr, lex, compAlreadyFound, compUsedCharIndex);
	computerFound(board, row - 1, col + 1, curr, lex, compAlreadyFound, compUsedCharIndex);
	computerFound(board, row + 1, col, curr, lex, compAlreadyFound, compUsedCharIndex);
	compUsedCharIndex[row][col] = false;
}

/*
 * Function: welcome
 * Usage: welcome();
 * -----------------
 * Print out a cheery welcome message.
 */
void welcome() {
    cout << "Welcome!  You're about to play an intense game ";
    cout << "of mind-numbing Boggle.  The good news is that ";
    cout << "you might improve your vocabulary a bit.  The ";
    cout << "bad news is that you're probably going to lose ";
    cout << "miserably to this little dictionary-toting hunk ";
    cout << "of silicon.  If only YOU had a gig of RAM..." << endl << endl;
}
/*
 * Function: giveInstructions
 * Usage: giveInstructions();
 * --------------------------
 * Print out the instructions for the user.
 */
void giveInstructions() {
    cout << endl;
    cout << "The boggle board is a grid onto which I ";
    cout << "I will randomly distribute cubes. These ";
    cout << "6-sided cubes have letters rather than ";
    cout << "numbers on the faces, creating a grid of ";
    cout << "letters on which you try to form words. ";
    cout << "You go first, entering all the words you can ";
    cout << "find that are formed by tracing adjoining ";
    cout << "letters. Two letters adjoin if they are next ";
    cout << "to each other horizontally, vertically, or ";
    cout << "diagonally. A letter can only be used once ";
    cout << "in each word. Words must be at least four ";
    cout << "letters long and can be counted only once. ";
    cout << "You score points based on word length: a ";
    cout << "4-letter word is worth 1 point, 5-letters ";
    cout << "earn 2 points, and so on. After your puny ";
    cout << "brain is exhausted, I, the supercomputer, ";
    cout << "will find all the remaining words and double ";
    cout << "or triple your paltry score." << endl << endl;
    cout << "Hit return when you're ready...";
    getLine();
}