#include <iostream>
using namespace std;
#define IMAX 4
#define JMAX 8
#define PARENT 0
#define OFFSPRING 1

enum {a,b,c,d,e,f,g,h};
int x[IMAX][JMAX];
int offSpring[IMAX][JMAX];
int fitness[IMAX];
int fitnessOffspring[IMAX];

void inputPopulation();
void calculateFitnessOf(int (& )[IMAX][JMAX], int (& )[IMAX]);
void printFitnessOf(int (& )[IMAX]);
void print(int (& )[IMAX][JMAX]);
void sortByFitnessOf(int (& )[IMAX][JMAX], int (& )[IMAX]);
void crossOverOnePoint(int, int, int);
void crossOver();

int main (){
    cout << "###################\n";
    inputPopulation();
    print(x);
    calculateFitnessOf(x, fitness);
    printFitnessOf(fitness);
    cout << "###################\n";
    cout << "\n*** After sort: ***\n";
    sortByFitnessOf(x, fitness);
    cout << "###################\n";
    print(x);
    printFitnessOf(fitness);
    cout << "###################\n";

    cout << "\n** 1st generation **\n";
    crossOver();
    print(offSpring);
    calculateFitnessOf(offSpring, fitnessOffspring);
    printFitnessOf(fitnessOffspring);

    return 0;
}

void inline inputPopulation(){
    for (int i=0; i<IMAX; i++){
        for (int j=0; j<JMAX; j++){
            cin >> x[i][j];
        }
    }
}

void inline print(int (&arr)[IMAX][JMAX]){
    for (int i=0; i<IMAX; i++){
        cout  << "x"<< i+1 << ": ";
        for (int j=0; j<JMAX; j++){
            cout << arr[i][j] << " ";
        }
        cout << endl;
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

void printFitnessOf(int (&arr)[IMAX]){
    for (int i=0; i<IMAX; i++){
        cout << "X"<<i+1<<": "<<arr[i]<<endl;
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


