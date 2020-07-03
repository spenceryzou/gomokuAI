#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include <vector>
#include <utility>
using namespace std;

int MAX_DEPTH = 1;
string columnToLetter(int column){
    switch(column){
        case 0:
            return "a";
        case 1:
            return "b";
        case 2:
            return "c";
        case 3:
            return "d";
        case 4:
            return "e";
        case 5:
            return "f";
        case 6:
            return "g";
        case 7:
            return "h";
        case 8:
            return "i";
        case 9:
            return "j";
        case 10:
            return "k";
        case 11:
            return "l";
        case 12:
            return "m";
        case 13:
            return "n";
        case 14:
            return "o";
        case 15:
            return "p";
        case 16:
            return "q";
        case 17:
            return "r";
        case 18:
            return "s";
        case 19:
            return "t";
        case 20:
            return "u";
        case 21:
            return "v";
        case 22:
            return "w";
        case 23:
            return "x";
        case 24:
            return "y";
        case 25:
            return "z";
    }
}
int letterToColumn(char letter){
    switch(letter){
        case 'a':
            return 0;
        case 'b':
            return 1;
        case 'c':
            return 2;
        case 'd':
            return 3;
        case 'e':
            return 4;
        case 'f':
            return 5;
        case 'g':
            return 6;
        case 'h':
            return 7;
        case 'i':
            return 8;
        case 'j':
            return 9;
        case 'k':
            return 10;
        case 'l':
            return 11;
        case 'm':
            return 12;
        case 'n':
            return 13;
        case 'o':
            return 14;
        case 'p':
            return 15;
        case 'q':
            return 16;
        case 'r':
            return 17;
        case 's':
            return 18;
        case 't':
            return 19;
        case 'u':
            return 20;
        case 'v':
            return 21;
        case 'w':
            return 22;
        case 'x':
            return 23;
        case 'y':
            return 24;
        case 'z':
            return 25;
    }
}
int scoringFunction(int connected, int openEnds, bool AIturn){
    if(openEnds == 0 && connected < 5) //case where no spaces around it available, no possible win from here
        return 0;
    switch(connected){        
        case 4:
            switch(openEnds){
                case 1:
                    if(AIturn)//if there is 4 in a row with one open end on AI turn, AI wins
                    //     return 15000;
                        return 1000;
                    else
                        return 10000;
                case 2:
                    if(AIturn)
                    //     return 15000;
                        return 15000;
                    else
                        return 25000;
            }
        case 3:
            switch(openEnds){
                case 1:
                    if(AIturn)
                    //     return 10000;
                        return 100;
                    else
                        return 1000;
                case 2:
                    if(AIturn)
                    //     return 15000;
                        return 1000;
                    else
                        return 15000;
            }
        case 2:
            switch(openEnds){
                case 1:
                    return 25;
                case 2: 
                    return 100;
            }
        case 1:
            switch(openEnds){
                case 1:
                    return 1;
                case 2:
                    return 1;
            }
        default: //leads to win
            if(AIturn)//if there is 4 in a row with one open end on AI turn, AI wins
                return 1000000;
            else
                return 1500000;
    }
}
int heuristicAI(vector<vector<int>> &board, int board_size){
    int score = 0;
    int connected = 0;
    int openEnds = 0;
    //check horizontal sets
    for(int column = 0; column < board_size; column++){
        for(int row = 0; row < board_size; row++){ //iterate through horizontally
            if(board[column][row] == 1){ //if current mover's piece is already here
                connected++;
                //cout << "there is a piece at " << column << " " << row << " "; 
            }
            else if(board[column][row] == -1 && connected > 0){ //if space is empty and there are pieces before it
                //cout << "there is a space before " << column << " " << row << " "; 
                openEnds++;
                score += scoringFunction(connected, openEnds, true);
                connected = 0; //reset connected count
                openEnds = 1;
            }else if(board[column][row] == -1){ //if space is empty and there is nothing before it
                openEnds=1;
            }else if(connected > 0){//if space is filled with adversary piece
                score += scoringFunction(connected, openEnds, true);
                connected = 0; //reset connected count
                openEnds = 0; //reset openEnds
            }else{
                openEnds = 0;
            }
        }//hit right wall, check if the remaining chain has potential to win, weakness: does not account for gaps
        if(connected > 0)
            score += scoringFunction(connected, openEnds, true);
        connected = 0;
        openEnds = 0;
    }
    //check vertical sets
    for(int row = 0; row < board_size; row++){
        for(int column = 0; column < board_size; column++){ //iterate through vertically
            if(board[column][row] == 1){ //if current mover's piece is already here
                connected++;
            }
            else if(board[column][row] == -1 && connected > 0){ //if space is empty and there are pieces before it
                openEnds++;
                score += scoringFunction(connected, openEnds, true);
                connected = 0; //reset connected count
                openEnds = 1;
            }else if(board[column][row] == -1){ //if space is empty and there is nothing before it
                openEnds=1;
            }else if(connected > 0){//if space is filled with adversary piece
                score += scoringFunction(connected, openEnds, true);
                connected = 0; //reset connected count
                openEnds = 0; //reset openEnds
            }else{
                openEnds = 0;
            } 
        }//hit bottom wall, check if the remaining chain has potential to win, weakness: does not account for gaps
        if(connected > 0)
            score += scoringFunction(connected, openEnds, true);
        connected = 0;
        openEnds = 0;
    }
    //check diagonal right to left sets
    int diagonals = (board_size + board_size) - 1;
    for (int i = 0; i < diagonals; ++i) {
        int z = (i < board_size) ? 0 : i - board_size + 1;
        for (int j = z; j <= i - z; ++j) {
            if(board[j][i-j] == 1){ //if current mover's piece is already here
                connected++;
            }
            else if(board[j][i-j] == -1 && connected > 0){ //if space is empty and there are pieces before it
                openEnds++;
                score += scoringFunction(connected, openEnds, true);
                connected = 0; //reset connected count
                openEnds = 1;
            }else if(board[j][i-j] == -1){ //if space is empty and there is nothing before it
                openEnds=1;
            }else if(connected > 0){//if space is filled with adversary piece
                score += scoringFunction(connected, openEnds, true);
                connected = 0; //reset connected count
                openEnds = 0; //reset openEnds
            }else{
                openEnds = 0;
            }
        }
        if(connected > 0)
            score += scoringFunction(connected, openEnds, true);
        connected = 0;
        openEnds = 0;
    }
    //check diagonals left to right set
    diagonals = (board_size + board_size) - 1;
    for (int i = 0; i < diagonals; ++i) {
        int z = (i < board_size) ? 0 : i - board_size + 1;
        for (int j = z; j <= i - z; ++j) {
            if(board[j][(board_size-1)-(i-j)] == 1){ //if current mover's piece is already here
                connected++;
            }
            else if(board[j][(board_size-1)-(i-j)] == -1 && connected > 0){ //if space is empty and there are pieces before it
                openEnds++;
                score += scoringFunction(connected, openEnds, true);
                connected = 0; //reset connected count
                openEnds = 1;
            }else if(board[j][(board_size-1)-(i-j)] == -1){ //if space is empty and there is nothing before it
                openEnds=1;
            }else if(connected > 0){//if space is filled with adversary piece
                score += scoringFunction(connected, openEnds, true);
                connected = 0; //reset connected count
                openEnds = 0; //reset openEnds
            }else{
                openEnds = 0;
            }
        }
        if(connected > 0)
            score += scoringFunction(connected, openEnds, true);
        connected = 0;
        openEnds = 0;
    }
    return score;
}
int heuristicPlayer(vector<vector<int>> &board, int board_size){
    int score = 0;
    int connected = 0;
    int openEnds = 0;
    
    //check horizontal sets
    for(int column = 0; column < board_size; column++){
        for(int row = 0; row < board_size; row++){ //iterate through horizontally
            if(board[column][row] == 2){ //if current mover's piece is already here
                connected++;
                //cout << "there is a piece at " << column << " " << row << " "; 
            }
            else if(board[column][row] == -1 && connected > 0){ //if space is empty and there are pieces before it
                //cout << "there is a space before " << column << " " << row << " "; 
                openEnds++;
                score += scoringFunction(connected, openEnds, false);
                connected = 0; //reset connected count
                openEnds = 1;
            }else if(board[column][row] == -1){ //if space is empty and there is nothing before it
                openEnds=1;
            }else if(connected > 0){//if space is filled with adversary piece
                score += scoringFunction(connected, openEnds, false);
                connected = 0; //reset connected count
                openEnds = 0; //reset openEnds
            }else{
                openEnds = 0;
            }
        }//hit right wall, check if the remaining chain has potential to win, weakness: does not account for gaps
        if(connected > 0)
            score += scoringFunction(connected, openEnds, false);
        connected = 0;
        openEnds = 0;
    }
    //check vertical sets
    for(int row = 0; row < board_size; row++){
        for(int column = 0; column < board_size; column++){ //iterate through vertically
            if(board[column][row] == 2){ //if current mover's piece is already here
                connected++;
            }
            else if(board[column][row] == -1 && connected > 0){ //if space is empty and there are pieces before it
                openEnds++;
                score += scoringFunction(connected, openEnds, false);
                connected = 0; //reset connected count
                openEnds = 1;
            }else if(board[column][row] == -1){ //if space is empty and there is nothing before it
                openEnds=1;
            }else if(connected > 0){//if space is filled with adversary piece
                score += scoringFunction(connected, openEnds, false);
                connected = 0; //reset connected count
                openEnds = 0; //reset openEnds
            }else{
                openEnds = 0;
            } 
        }//hit bottom wall, check if the remaining chain has potential to win, weakness: does not account for gaps
        if(connected > 0)
            score += scoringFunction(connected, openEnds, false);
        connected = 0;
        openEnds = 0;
    }
    //check diagonal right to left sets
    int diagonals = (board_size + board_size) - 1;
    for (int i = 0; i < diagonals; ++i) {
        int z = (i < board_size) ? 0 : i - board_size + 1;
        for (int j = z; j <= i - z; ++j) {
            if(board[j][i-j] == 2){ //if current mover's piece is already here
                connected++;
            }
            else if(board[j][i-j] == -1 && connected > 0){ //if space is empty and there are pieces before it
                openEnds++;
                score += scoringFunction(connected, openEnds, false);
                connected = 0; //reset connected count
                openEnds = 1;
            }else if(board[j][i-j] == -1){ //if space is empty and there is nothing before it
                openEnds=1;
            }else if(connected > 0){//if space is filled with adversary piece
                score += scoringFunction(connected, openEnds, false);
                connected = 0; //reset connected count
                openEnds = 0; //reset openEnds
            }else{
                openEnds = 0;
            }
        }
        if(connected > 0)
            score += scoringFunction(connected, openEnds, false);
        connected = 0;
        openEnds = 0;
    }
    //check diagonals left to right set
    diagonals = (board_size + board_size) - 1;
    for (int i = 0; i < diagonals; ++i) {
        int z = (i < board_size) ? 0 : i - board_size + 1;
        for (int j = z; j <= i - z; ++j) {
            if(board[j][(board_size-1)-(i-j)] == 2){ //if current mover's piece is already here
                connected++;
            }
            else if(board[j][(board_size-1)-(i-j)] == -1 && connected > 0){ //if space is empty and there are pieces before it
                openEnds++;
                score += scoringFunction(connected, openEnds, false);
                connected = 0; //reset connected count
                openEnds = 1;
            }else if(board[j][(board_size-1)-(i-j)] == -1){ //if space is empty and there is nothing before it
                openEnds=1;
            }else if(connected > 0){//if space is filled with adversary piece
                score += scoringFunction(connected, openEnds, false);
                connected = 0; //reset connected count
                openEnds = 0; //reset openEnds
            }else{
                openEnds = 0;
            }
        }
        if(connected > 0)
            score += scoringFunction(connected, openEnds, false);
        connected = 0;
        openEnds = 0;
    }
    return score;
}
int minimax(vector<vector<int>> &board, int currentDepth, bool AIturn, int board_size, int alpha, int beta){
    //evaluate board with latest added move
    int remainingSpace=0;
    for(int column = 0; column < board_size; column++){
        for(int row = 0; row < board_size; row++){
                if(board[column][row] == -1){
                    remainingSpace++;
                }
        }
    }
    int score;
    int bestScore;
    if(currentDepth == MAX_DEPTH || remainingSpace==0){
        return heuristicAI(board, board_size)-heuristicPlayer(board, board_size);
    }
    if(AIturn){
        bestScore = -INFINITY;
        for(int column = 0; column < board_size; column++){
            for(int row = 0; row < board_size; row++){
                if(board[column][row] == -1){
                    board[column][row] = 1;
                    //call minmax to recursively return score for current move after simulating min for next move, and max for move after
                    score = minimax(board, currentDepth + 1, false, board_size, alpha, beta);
                    board[column][row] = -1;
                    bestScore = max(bestScore, score);
                    alpha = max(alpha, score);
                    if(beta <= alpha)
                        return bestScore;
                }
            }
        }
        return bestScore;
    }else{//minimize, simulate players turn
        bestScore = +INFINITY;
        for(int column = 0; column < board_size; column++){
            for(int row = 0; row < board_size; row++){
                if(board[column][row] == -1){
                    board[column][row] = 2;
                    //call minmax to recursively return score for current move after simulating min for next move, and max for move after
                    score = minimax(board, currentDepth + 1, true, board_size, alpha, beta);
                    board[column][row] = -1;
                    bestScore = min(bestScore, score);
                    beta = min(beta, score);
                    if(beta <= alpha)
                        return bestScore;
                    // cout << column << " " << row << " ";
                    // cout << score << endl;
                    
                }
            }
        }
        return bestScore;
    }
}

void decideMove(vector<vector<int>> &board, int board_size){
    int xcoord = -1;
    int ycoord = -1;
    int maxScore = -100000; //initialize with minimum possible score
    //try possible moves
    for(int column = 0; column < board_size; column++){
        for(int row = 0; row < board_size; row++){
            if(board[column][row] == -1){
                board[column][row] = 1;
                //call minmax to recursively return score for current move after simulating min for next move, and max for move after
                int score = minimax(board, 0, false, board_size, -INFINITY, +INFINITY);
                board[column][row] = -1;
                if(score > maxScore){
                    xcoord = column;
                    ycoord = row;
                    maxScore = score;
                }
            }
        }
    }
    board[xcoord][ycoord] = 1;
    cout << "Move played: " + columnToLetter(xcoord) + to_string(ycoord + 1) << endl;
    return;
}

int main(int argc, char* argv[]){
    int moveCount=0;
    int board_size = 11;
    bool black = false;
    bool inGame = true;
    for (int i=1; i<argc; i++) {
   	    if (argv[i] == string("-n"))
            board_size = atoi(argv[i+1]);
        if (argv[i] == string("-l"))
            black = true;
    }
    //initialize board, let ai be equal to 1, player be equal to 2.
    vector<int> y(board_size, -1);
    vector<vector<int>> board(board_size, y);
    int diagonals = (board_size + board_size) - 1;
    //first ai move
    if(black){
        board[(board_size-1)/2][(board_size-1)/2] = 1;
        cout << "Move played: " + columnToLetter((board_size-1)/2) + to_string(((board_size-1)/2)+1) << endl;
        // decideMove(board, board_size);
        moveCount++;
    }
    while(inGame){
        if(moveCount > 5){
            MAX_DEPTH = 2;
        }
        //take player move
        bool playerMove = true;
        while(playerMove){
            string move;
            int row;
            int column;
            cin >> move;
            column = letterToColumn(move[0]);
            move.erase(move.begin());
            row = stoi(move) - 1;
            if(row < 0 || row > board_size - 1 || column < 0 || column > board_size - 1){
                cout << "invalid move, redo input" << endl;
                continue;
            }
            if(board[column][row] != -1){
                cout << "spot taken, redo input" << endl;
                continue;
            }
            board[column][row] = 2;
            moveCount++;
            cout << "Move played: " + columnToLetter(column) + to_string(row + 1) << endl;
            playerMove=false;
        }
        //ai decide move
        decideMove(board, board_size);
        moveCount++;
        playerMove=true;
    }
}