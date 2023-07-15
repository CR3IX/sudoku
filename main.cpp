#include<cstdlib>
#include<iostream>
#include<vector>
using namespace std;

vector<vector<int> > sudoku(9,vector<int>(9,0));
void display(){
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            cout<<sudoku[i][j]<<" ";
        }
        cout<<endl;
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
bool isvalid(int i,int row,int col){

}
bool fill_remaining(int row,int col){
    int i;
    if(row==8 && col==8){
        return false;
    }
    for(i=1;i<=9;i++){
        if(!isvalid(i,row,col)){
            continue;
        }
        sudoku[row][col]=i;
        next(row,col);
        if(!fill_remaining(row,col)){
            return false;
        }
    }
    return true;
}

void fill_sudoku(){
    fill_diagonal(0,0);
    fill_diagonal(3,3);
    fill_diagonal(6,6);
}
int main(){
    fill_sudoku();
    display();
    return 0;
}