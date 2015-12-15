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
int sortedIndex[IMAX];

void inputPopulation();
void calculateFitnessOf(int (& )[IMAX][JMAX]);
void printFitness();
void printPopulation();
void sortByFitness();
void printOffspring();
void crossOverOnePoint(int, int, int);

int main (){
    cout << "###################\n";
    inputPopulation();
    printPopulation();
    calculateFitnessOf(x);
    printFitness();
    cout << "###################\n";
    cout << "\n*** After sort: ***\n";
    sortByFitness();
    cout << "###################\n";
    printPopulation();
    printFitness();
    cout << "###################\n";

    crossOverOnePoint(0, 1, 4);
    crossOverOnePoint(2, 3, 4);
    printOffspring();
    return 0;
}

void inline inputPopulation(){
    for (int i=0; i<IMAX; i++){
        sortedIndex[i]=i;
        for (int j=0; j<JMAX; j++){
            cin >> x[i][j];
        }
    }
}

void inline printPopulation(){
    cout << "Population: \n";
    for (int i=0; i<IMAX; i++){
        cout  << "x"<< i+1 << ": ";
        for (int j=0; j<JMAX; j++){
            cout << x[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void calculateFitnessOf(int (&arr)[IMAX][JMAX]){
    //int &X[][] = (name == PARENT) ? x : offSpring;
    for (int i=0; i<IMAX; i++){
        fitness[i] =((arr[i][a] + arr[i][b])
                     -(arr[i][c] + arr[i][d])
                     +(arr[i][e] + arr[i][f])
                     -(arr[i][g] + arr[i][h]));
    }
}

void printFitness(){
    cout << "Fitness :\n";
    for (int i=0; i<IMAX; i++){
        cout << "X"<<i+1<<": "<<fitness[i]<<endl;
    }
}

void sortByFitness(){
    int temp, arr[JMAX];
    for(int i=0; i<IMAX; i++){

        for(int j=0; j<IMAX; j++){
            if(fitness[i]>fitness[j]){
                temp = fitness[i];
                fitness[i] = fitness[j];
                fitness[j] = temp;
                for(int t=0; t<JMAX; t++){
                    arr[t]=x[i][t];
                }
                for(int t=0; t<JMAX; t++){
                    x[i][t] = x[j][t];
                }
                for(int t=0; t<JMAX; t++){
                    x[j][t] = arr[t];
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


void inline printOffspring(){
    cout << "\nOffspting: \n";
    for (int i=0; i<IMAX; i++){
        cout  << "x"<< i+1 << ": ";
        for (int j=0; j<JMAX; j++){
            cout << offSpring[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl << endl;
}

