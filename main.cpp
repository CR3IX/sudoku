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
void disp(vector<int> &d){
    for(int i=0;i<d.size();i++){
        cout<<d[i];
    }
    cout<<endl;
}
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
            disp(remaining_random);


            sudoku[i][j]=num;
        }
    }
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