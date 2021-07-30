#include <iostream>

using namespace std;


/*
------------------------>>> README <<<------------------------
Desenvolvido por Edsger Dijkstra o algoritmo testa a segurança
ao simular a alocação da quantidade máxima pré-determinada de 
todosos recursos.

1. Variáveis:

N: Número de Processos do Sistema

M: Número de tipos de recursos

2. As estruturas usadas são:

AVAILABLE: Um vetor 1d de tamanho m com o número de recursos 
disponíveis de cada tipo.

MAX: Um vetor 2d de tamanho n*m que define a demanda máxima para
cada processo do sistema.

ALLOCATED: Um vetor 2d de tamanho n*m que define o número de
recursos de cada tipo alocado para cada processo.

NEED: Need[i, j] = Max[i, j] - Allocated[i, j]

Observação: as estruturas serão todas preenchidas com 0 no incio 
do programa.

------------------------>>> README <<<------------------------
*/

//Soma os valores de dois vetores bidimensionais.
int* sum2D(int** arr, int rows, int cols){
    int* sum = new int[cols];
    for(int i = 0; i < cols; i++){
        sum[i] = 0;
    }
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            sum[j] += arr[i][j];
        }
    }
    return sum;
}

void zero2D(int** arr, int rows, int cols){
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            arr[i][j] = 0;
        }
    }
}

void print2D(int** arr, int rows, int cols){
    for(int i = 0; i < rows; i++) {
        cout << "\n";
        for(int j = 0; j < cols; j++) {
            cout << arr[i][j] << "|";
        }
        cout << "\n";
        for(int j = 0; j < cols; j++) {
            cout << "__";
        }
    }
}
/*
Compara dois vetores de tamanhos iguais e retorna false
se existir algum valor de arr1 maior o valor do mesmo indice
no arr2.
*/
bool compareArray(int* arr1, int* arr2, int n1, int n2) {
    if(n1 != n2){
        return false;
    }
    for (int i =0; i < n1; i++){
        if (arr1[i] > arr2[i]) {
            return false;
        }
    }
    return true;
}

int main(){
    int num_of_res;

    cout << "\nNumero de recursos (M): ";
    cin >> num_of_res;

    int num_of_process;
    cout <<  "\nNumero de processos (N): ";
    cin >> num_of_process;


    //Para cada coluna, alocando a quantidade de processos dada.
    int** allocated = new int* [num_of_process];
    for (int i = 0; i < num_of_process; i++){
        allocated[i] = new int[num_of_res];
    }
    zero2D(allocated, num_of_process, num_of_res);
    print2D(allocated, num_of_process, num_of_res);
    cout << "\n";

    //Para cada elemento da matriz ALLOCATED, adicionar o 
    //número de recursos alocados.
    for(int i = 0; i < num_of_process; i++) {
        for(int j = 0; j < num_of_res; j++) {
            cout << "\nQuantidade para R" << j + 1<< " alocado para P" << i + 1 << ": ";
            cin >> allocated[i][j];
        }
    }
    cout << "\n\tALLOCATED";
    print2D(allocated, num_of_process, num_of_res);


    cout << "\n\nNúmero max de recursos";

    int** max = new int* [num_of_process];
    for(int i = 0; i < num_of_process; i++){
        max[i] = new int[num_of_res];
    }
    zero2D(max, num_of_process, num_of_res);
    print2D(max, num_of_process, num_of_res);
    cout << "\n";

    for(int i = 0; i < num_of_process; i++){
        for(int j = 0; j < num_of_res; j++) {
            cout << "\nQuantidade max para R" << j + 1 << "necessaria para P" << i + 1 << ": ";
            cin >> max[i][j];
        }
    }
    cout << "\n\tMAX";
    print2D(max, num_of_process, num_of_res);

    int** need = new int* [num_of_process];
    for(int i = 0; i < num_of_process; i++) {
        need[i] = new int[num_of_res];
    }
    zero2D(need, num_of_process, num_of_res);
    print2D(need, num_of_process, num_of_res);
    cout << "\n";

    for(int i = 0; i < num_of_process; i++) {
        for(int j = 0; j < num_of_res; j++) {
            need[i][j] = max[i][j] - allocated[i][j];
        }
    }
    cout << "\n\tNEED";
    print2D(need, num_of_process, num_of_res);
    cout << "\n";


    //???total_res???
    int * total_res = new int[num_of_res];

    cout << "\nInsira os valores de total resources para calcular AVAILABLE";
    for (int i = 0; i < num_of_res; i++) {
        cout << "\nTotal para R" << i + 1 << ": ";
        cin >> total_res[i]; 
    }

    //recursos disponíveis
    int *totalAllocated = new int[num_of_res];

    totalAllocated = sum2D(allocated, num_of_process, num_of_res);

    int * available = new int[num_of_res];
    for(int i = 0; i < num_of_res; i++) {
        available[i] = total_res[i] - totalAllocated[i];
        cout << available[i] << "|";
    }


    int* safe_state = new int[num_of_process];
    int state_index = 0;
    bool compare = true;
    bool is_terminated;

    while(compare){
        compare = false;
        for (int i = 0; i < num_of_process; i++) {
            is_terminated = false;
            for(int j = 0; j < state_index; j++) {
                if (safe_state[j] == i) {
                    is_terminated = true;
                }
            }
            if(!is_terminated) {
                if(compareArray(need[i], available, num_of_res, num_of_res)){
                    safe_state[state_index] = i;
                    state_index++;
                    for(int j = 0; j < num_of_res; j++){
                        available[j] += allocated[i][j];
                    }
                    compare = true;
                }
            }
        }
    }

    cout << "\nEsta safe: ";
    for (int i = 0; i < state_index; i++) {
        cout << "P" << safe_state[i] + 1 << "\t";
    }

    if (num_of_process == state_index) {
        cout << "\nSem deadlock!\n";
    } else {
        cout << "\nDeadlock\n";
    }
}



