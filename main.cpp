#include <ncurses.h>
#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

vector<vector<int> > sudoku(9,vector<int>(9,0));
vector<vector<int> > puzzle(9,vector<int>(9,0));
void display(){
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            cout<<sudoku[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}
void puzz(int k){
    int r,c;
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            puzzle[i][j]=sudoku[i][j];
        }
    }
    while(k!=0){
        r=(rand()%9);
        c=rand()%9;
        puzzle[r][c]=0;
        puzzle[c][r]=0;
        k--;
    }
}

//Randomly fills diagonal 3x3 values
void fill_diagonal(int row,int col){
    int num,it,temp;
    vector<int> remaining_random;
    for(it=1;it<=9;it++){
        remaining_random.push_back(it);
    }
    for(int i=row;i<row+3;i++){
        for(int j=col;j<col+3;j++){

            it=rand()%remaining_random.size();

            num=remaining_random[it];
            temp=remaining_random[it];
            remaining_random[it]=remaining_random[(remaining_random.size()-1)];
            remaining_random.pop_back();


            sudoku[i][j]=num;
        }
    }
}
void next(int &row,int &col){
    if(col!=8){
        col++;
    }
    else{
        row++;
        col=0;
    }
    if(((row>=0&&row<=2)&&(col>=0&&col<=2))||((row>=3&&row<=5)&&(col>=3&&col<=5))||((row>=6&&row<=8)&&(col>=6&&col<=8))){
        next(row,col);
    }
    return;
}
void prev(int &row,int &col){
    if(col!=0){
        col--;
    }
    else{
        col=8;
        row--;
    }
    if(((row>=0&&row<=2)&&(col>=0&&col<=2))||((row>=3&&row<=5)&&(col>=3&&col<=5))||((row>=6&&row<=8)&&(col>=6&&col<=8))){
        prev(row,col);
    }

}
bool isvalid(int i,int row,int col){
    int count=0;
    int r,c,it,j;
    for(it=0;it<9;it++){
        if(sudoku[row][it]==i){
            count++;
        }
        if(sudoku[it][col]==i){
            count++;
        }
    }
    if(count>0){
        return false;
    }
    r=row-(row%3);
    c=col-(col%3);
    count=0;
    for(it=r;it<r+3;it++){
        for(j=c;j<c+3;j++){
            if(sudoku[it][j]==i){
                count++;
            }
        }
    }
    if(count>0){
        return false;
    }
    else{
        return true;
    }
}
bool fill_remaining(int row,int col){
    int i;
    if(row==9 && col==0){
        return false;
    }
    for(i=1;i<=9;i++){
        if(!isvalid(i,row,col)){
            continue;
        }
        sudoku[row][col]=i;
        //display();
        next(row,col);
        if(!fill_remaining(row,col)){
            return false;
        }
        prev(row,col);
    }
    //display();
    sudoku[row][col]=0;
    return true;
}

void fill_sudoku(){
    fill_diagonal(0,0);
    fill_diagonal(3,3);
    fill_diagonal(6,6);
    fill_remaining(0,3);
}
int main(){
    int i,j,n;
    fill_sudoku();
    puzz(6);
    initscr();
    noecho();
    for(i=0;i<9;i++){
        for(int j=0;j<9;j++){
            mvprintw(i*2,j*3,"%d",puzzle[i][j]);
        }
    }
    move(0,0);
    i=0;j=0;
    while(1){
        char ch=getch();
        switch(ch){
            case 'd':
                j++;
                move(i*2,j*3);
                refresh();
                break;
            case 'a':
                j--;
                move(i*2,j*3);
                refresh();
                break;
            case 's':
                i++;
                move(i*2,j*3);
                refresh();
                break;
            case 'w':
                i--;
                move(i*2,j*3);
                refresh();
                break;
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                n=int(ch-'0');
                if(sudoku[i][j]==n){
                    printw("%d",n);
                    mvprintw(27,0,"correct!!   ");
                    move(i*2,j*3);
                    refresh();}
                else{
                    mvprintw(27,0,"wrong answer");
                    move(i*2,j*3);
                    refresh();}
                break;
            case 'P':
                clear();
                for(i=0;i<9;i++){
                for(int j=0;j<9;j++){
                     mvprintw(i*2,j*3,"%d",sudoku[i][j]);
                    }
                }
                mvprintw(20,0,"Guess you could`nt solve it!!!!!!!!!!!");
                getch();
                endwin();
                break;
            default:
                endwin();
                break;
        }
    }
    return 0;
}
