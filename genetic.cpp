#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
#define IMAX 4
#define JMAX 8

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
void chooseBest();
void mutation(int (& )[IMAX][JMAX]);

int main (){
    inputPopulation();
    for(int t=0; t<4;t++){
        cout << "\n###################";
        cout << "\n** Generation "<< t+1 <<" **\n";
        cout << "###################\n";
        cout << "\n***  Parents:  ***\n";
        print(x);
        calculateFitnessOf(x, fitness);
        printFitnessOf(fitness);
        cout << "\n*   After sort:  *\n";
        sortByFitnessOf(x, fitness);
        print(x);
        printFitnessOf(fitness);
        crossOver();
        calculateFitnessOf(offSpring, fitnessOffspring);

        cout << "\n*** Offspring: ***\n";
        print(offSpring);
        printFitnessOf(fitnessOffspring);

        cout << "\n*    Mutation:   *\n";
        mutation(offSpring);
        calculateFitnessOf(offSpring, fitnessOffspring);
        print(offSpring);
        printFitnessOf(fitnessOffspring);


        sortByFitnessOf(offSpring, fitnessOffspring);
        cout << "\n*   After sort:  *\n";
        print(offSpring);
        printFitnessOf(fitnessOffspring);

        chooseBest();
        cout << "###################\n";
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

void inline print(int (&arr)[IMAX][JMAX]){
    cout << "   a b c d e f g h\n";
    for (int i=0; i<IMAX; i++){
        cout  << i+1 << ": ";
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
    cout<<"Fitness: f(x) = (a+b)-(c+d)+(e+f)-(g+h)\n";
    for (int i=0; i<IMAX; i++){
        cout <<i+1<<": "<<arr[i]<<endl;
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

