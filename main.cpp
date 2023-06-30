#include<iostream>
#include<cstdlib>
#include<unordered_set>
using namespace std;

void debugy(unordered_set<int> y[][3]){
    for(int i=0;i<9;i++){
        for(int j=0;j<3;j++){
            for(unordered_set<int>::iterator el=y[i][j].begin();el!=y[i][j].end();++el){
                    cout<<*el;
            }
            cout<<" ";
        }
        cout<<endl;
    }
}

void clone(unordered_set<int> source[][3],unordered_set<int> dest[][3]){//copying set
    for(int i=0;i<9;i++){
        for(int j=0;j<3;j++){
            for(unordered_set<int>::iterator element=source[i][j].begin();element !=source[i][j].end();++element){
                dest[i][j].insert(*element);
            }
        }
    }
}
int Rnd(unordered_set<int> set1){//Generating Random
    if(set1.empty()){
        cout<<"nullptr\n";
        return 1;
    }
    int r=rand() % (set1.size()-1);
    int re,cnt=0;
    for(unordered_set<int>::iterator el=set1.begin();el!=set1.end();el++){
        if(cnt==r){
            re=*el;
            break;
        }
        cnt++;
    }
    
    return re;
}
int fill_sudoku(){
    int sudoku[9][9] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0}
  };
    int i,j,k,l,m,n;
    int xpos,ypos;
    unordered_set<int> x[3];
    unordered_set<int> y[9][3];
    unordered_set<int> temp[9][3];

    //sets for choosing random values
    for(n=0;n<9;n++){
        for(l=0;l<3;l++){
            for(m=0;m<3;m++){
                y[n][l].insert((m+1)+(3*l));
            }
        }
    }
    //filling
    for(i=1;i<=9;i++){
        //initializing values
        for(l=0;l<3;l++){
            for(m=0;m<3;m++){
                x[l].insert((m+1)+(3*l));
            }
        }
        clone(y,temp);
        for(j=0;j<3;j++){
            for(k=0;k<3;k++){
                xpos=Rnd(x[j]);
                ypos=Rnd(temp[xpos-1][k]);

                //erasing
                x[j].erase(xpos);
                y[xpos-1][k].erase(ypos);
                debugy(y);
                for(int it=0;it<9;it++){
                    temp[it][k].erase(ypos);
                }
                //sudoku[xpos-1][ypos-1]=i;
                if (xpos-1 <= 8 && ypos-1<=8) {
                    //cout<<xpos-1<<" "<<ypos-1<<endl;
                    sudoku[xpos - 1][ypos - 1] = i;
                }
                /*else{
                    cout<<"error"<<xpos-1<<" "<<ypos<<endl;
                }*/
            }
        }
    }
    for(i=0;i<9;i++){
        for(j=0;j<9;j++){
            cout<<sudoku[i][j]<<" ";
        }
        cout<<endl;
    }
    return 0;
}
int main(){
    int ans=fill_sudoku();
    return 0;
}