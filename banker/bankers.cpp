#include <iostream>

using namespace std;
                    //num_of_rols and cols
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

    // cout << "\nSoma do vetor é: ";
    // for(int i = 0; i < cols; i++){
    //     cout << sum[i] << "\t";
    // }
    return sum;
}

//Compara dois vetores de tamanhos iguais e retorna false
//se existir algum valor de arr1 maior o valor do mesmo indice
//no arr2.
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
    cout << "\nNumero de recursos: ";
    cin >> num_of_res;

    int * total_res = new int[num_of_res];
    for (int i = 0; i < num_of_res; i++) {
        cout << "\nTotal para R" << i + 1 << ": ";
        cin >> total_res[i]; 
    }

    int num_of_process;
    cout <<  "\nNumero de processos: ";
    cin >> num_of_process;

    int** allocated = new int* [num_of_process];
    for (int i = 0; i < num_of_process; i++){
        allocated[i] = new int[num_of_res];
    }
    
    for(int i = 0; i < num_of_process; i++) {
        for(int j = 0; j < num_of_res; j++) {
            cout << "\nQuantidade para R" << j + 1 << "alocado para P" << i +1 << ": ";
            cin >> allocated[i][j];
        }
    }

    cout << "\nNumero max de recursos";

    int** max = new int* [num_of_process];
    for(int i = 0; i < num_of_process; i++){
        max[i] = new int[num_of_res];
    }

    for(int i = 0; i < num_of_process; i++){
        for(int j = 0; j < num_of_res; j++) {
            cout << "\nQuantidade max para R" << j + 1 << "necessaria para P" << i + 1 << ": ";
            cin >> max[i][j];
        }
    }

    //E  F  G
    //6  7  8
    //recursos disponíveis
    int *totalAllocated = new int[num_of_res];

    totalAllocated = sum2D(allocated, num_of_process, num_of_res);

    int * available = new int[num_of_res];
    for(int i = 0; i < num_of_res; i++) {
        available[i] = total_res[i] - totalAllocated[i];
    }

    /*  E  F  G
    p1  
    p2
    p3
    */

   int** need = new int* [num_of_process];
   for(int i = 0; i < num_of_process; i++) {
       need[i] = new int[num_of_res];
   }

    for(int i = 0; i < num_of_process; i++) {
        for(int j = 0; j < num_of_res; j++) {
            need[i][j] = max[i][j] - allocated[i][j];
        }
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