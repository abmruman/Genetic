/**
 *
 *  @author A B M RUMAN
 *
 **/
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <ctime>
using namespace std;
#define IMAX 4
#define JMAX 8
#define GENERATION 5

enum {a,b,c,d,e,f,g,h};
int x[IMAX][JMAX];
int offSpring[IMAX][JMAX];
int fitnessParent[IMAX];
int fitnessOffspring[IMAX];
int mutatedPop=-1, mutatedPos=-1;
void inputPopulation();
void calculateFitnessOf(int (& )[IMAX][JMAX], int (& )[IMAX]);
void printTable(int (& )[IMAX][JMAX], int (&)[IMAX]);
void sortByFitnessOf(int (& )[IMAX][JMAX], int (& )[IMAX]);
void crossOverOnePoint(int, int, int);
void crossOver();
void chooseBest();
void mutation(int (& )[IMAX][JMAX]);
string format(int);
string format(float);

int main (){
    inputPopulation();
    cout<<"\nFitness function : f(x) = (a+b)-(c+d)+(e+f)-(g+h)\n";
    cout<<"\nMutation Marker  : *\n\n";

    for(int t=0; t<GENERATION;t++){
        //cout << "##################################\n";
        cout << "           Generation "<< t+1 <<"           ";
        //cout << "\n##################################\n\n";
        cout << "\n__________________________________\n\n\n";

        cout << "----------------------------------------------------------\n";
        cout << "|                      P A R E N T                       |\n";
        calculateFitnessOf(x, fitnessParent);
        printTable(x, fitnessParent);
        sortByFitnessOf(x, fitnessParent);

        crossOver();


        cout << "----------------------------------------------------------\n";
        cout << "|                   O F F S P R I N G                    |\n";
        mutation(offSpring);
        calculateFitnessOf(offSpring, fitnessOffspring);
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
    int total=0, minVal = 0, extraFit, extraTotal;
    float totalProb = 0.0f, prob=0.0f, avg;
    for (int i=0; i<IMAX; i++){
        minVal = min(minVal, fit[i]);
        total += fit[i];
    }

    /** To prevent a negative probability **/
    extraTotal = (minVal<0) ? abs(minVal*IMAX) : 0;

    avg = 1.0f*total/IMAX;
    cout << "----------------------------------------------------------\n";
    cout << "|  x  | a  b  c  d  e  f  g  h  |  Fitness | Probability |\n";
    cout << "----------------------------------------------------------\n";

    for (int i=0; i<IMAX; i++){
        string mark = (mutatedPop==i)?"*":" ";

        cout  << "|  " << i+1 << mark << " | ";
        for (int j=0; j<JMAX; j++){
            mark = (mutatedPop==i && mutatedPos==j)?"*":" ";
            cout << ""<<arr[i][j] << mark << " ";
        }

        cout << "|";
        totalProb += prob = (1.0f*fit[i]+abs(minVal))/abs(total+extraTotal);

        cout << "     "<<format(fit[i])<< fit[i]<< "  |    "
            << format(prob) << fixed <<setprecision(4) << prob <<"  |" ;
        cout << "\n----------------------------------------------------------\n";
    }
    mutatedPop=-1;
    mutatedPos=-1;

    cout << "|           T O T A L           |     "<< format(total) << total <<"  |      "
        << format(totalProb) << fixed <<setprecision(2) << totalProb <<"  |";
    cout << "\n----------------------------------------------------------\n";
    cout << "|         A V E R A G E         |   "<< format(avg) << fixed <<setprecision(2)<< avg <<"  |             |";
    cout << "\n----------------------------------------------------------\n";
    cout << endl << endl;
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
    mutatedPop = randNum(0,IMAX);
    mutatedPos = randNum(0,JMAX);
   arr[mutatedPop][mutatedPos] = randNum(0,9);
}

string format(int val){
    string formated = "";
    if(val<-9)
        formated = "";
    else if(val<0)
        formated = " ";
    else if(val<10)
        formated = "  ";
    else if(val<100)
        formated = " ";
    return formated;
}

string format(float val){
    string formated = "";

    if(val<0)
        formated = "";
    else
        if(val<10)
        formated = " ";
    return formated;
}
