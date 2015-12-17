/**
 *
 *  @author A B M RUMAN
 *
 **/
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
#define IMAX 4
#define JMAX 8

enum {a,b,c,d,e,f,g,h};
int x[IMAX][JMAX];
int offSpring[IMAX][JMAX];
int fitnessParent[IMAX];
int fitnessOffspring[IMAX];

void inputPopulation();
void calculateFitnessOf(int (& )[IMAX][JMAX], int (& )[IMAX]);
void printTable(int (& )[IMAX][JMAX], int (&)[IMAX]);
void sortByFitnessOf(int (& )[IMAX][JMAX], int (& )[IMAX]);
void crossOverOnePoint(int, int, int);
void crossOver();
void chooseBest();
void mutation(int (& )[IMAX][JMAX]);
string format(int);
int main (){
    inputPopulation();
    cout<<"\nFitness function : f(x) = (a+b)-(c+d)+(e+f)-(g+h)\n\n";

    for(int t=0; t<4;t++){
        cout << "##################################\n";
        cout << "           Generation "<< t+1 <<"           ";
        cout << "\n##################################\n\n";
        cout << "***          Parent:          ***\n";
        calculateFitnessOf(x, fitnessParent);
        printTable(x, fitnessParent);

        sortByFitnessOf(x, fitnessParent);

        crossOver();
        calculateFitnessOf(offSpring, fitnessOffspring);

        cout << "***         Offspring:         ***\n";
        printTable(offSpring, fitnessOffspring);

        sortByFitnessOf(offSpring, fitnessOffspring);
        chooseBest();
    }
    return 0;
}

inline int randNum(int min, int max){
	double d = rand()/static_cast<double>(RAND_MAX);
    int i = min + static_cast<int>( d * (max - min) );
    return i;
}

inline void inputPopulation(){
    for (int i=0; i<IMAX; i++){
        for (int j=0; j<JMAX; j++){
            cin >> x[i][j];
        }
    }
}

void inline printTable(int (&arr)[IMAX][JMAX], int (&fit)[IMAX]){
    cout << "----------------------------------\n";
    cout << "| x | a b c d e f g h |  Fitness |\n";
    cout << "----------------------------------\n";
    for (int i=0; i<IMAX; i++){
        cout  << "| "<< i+1 << " | ";
        for (int j=0; j<JMAX; j++){
            cout << ""<<arr[i][j] << " ";
        }
        cout << "|";
        cout <<"   "<<format(fit[i])<< fit[i]<< "    |" ;
        cout << "\n----------------------------------\n";
    }
    cout << endl;
}

void calculateFitnessOf(int (&arr)[IMAX][JMAX], int (& fit)[IMAX]){
    for (int i=0; i<IMAX; i++){
        fit[i] =((arr[i][a] + arr[i][b])
                 -(arr[i][c] + arr[i][d])
                 +(arr[i][e] + arr[i][f])
                 -(arr[i][g] + arr[i][h]));
    }
}

void sortByFitnessOf(int (&arr)[IMAX][JMAX], int (&fit)[IMAX]){
    int temp, tempArr[JMAX];
    for(int i=0; i<IMAX; i++){
        for(int j=0; j<IMAX; j++){
            if(fit[i]>fit[j]){
                temp = fit[i];
                fit[i] = fit[j];
                fit[j] = temp;
                for(int t=0; t<JMAX; t++){
                    tempArr[t]=arr[i][t];
                }
                for(int t=0; t<JMAX; t++){
                    arr[i][t] = arr[j][t];
                }
                for(int t=0; t<JMAX; t++){
                    arr[j][t] = tempArr[t];
                }
            }
        }
    }
}

void crossOverOnePoint(int a, int b, int pointer){
    for (int i= 0; i<pointer; i++){
        offSpring[a][i] = x[a][i];
        offSpring[b][i] = x[b][i];
    }
    for (int i= pointer; i<JMAX; i++){
        offSpring[b][i] = x[a][i];
        offSpring[a][i] = x[b][i];
    }
}

void crossOver(){
    crossOverOnePoint(0, 1, 4);
    crossOverOnePoint(2, 3, 4);
}

void chooseBest(){
    for (int j=0; j<JMAX; j++){
        x[2][j] = offSpring[0][j];
        x[3][j] = offSpring[1][j];
    }
}

void inline mutation(int (&arr)[IMAX][JMAX]){
    for (int i=0; i<IMAX; i++){
        arr[i][randNum(0,JMAX)] = randNum(0,9);

    }
}

string format(int val){
    string formated = "";
    if(val<0)
        formated = "";
    else if(val<10)
        formated = "  ";
    else if(val<100)
        formated = " ";
    return formated;
}
