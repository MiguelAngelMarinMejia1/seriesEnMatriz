#include <iostream>
#include <limits> //Biblioteca para evitar que se ingrese un dato no pedido

// Estas dos funciones hacen parte de la serie 2
bool esPrimo(int num);
bool esRepetido(int a[], int n, int tam);
//----------------

/* 
La serie 1 toma el 1 y se le suma 2, luego a ese resultado (3) se le suma 3,
despues a ese resultado (6) se le suma 4 y así sucesivamente

2,3,4,5,6,7,8,9 y 10 son los números que se suman
*/
int serie1(int a[], int tam);

// La serie dos se basa en la sucesion ordenada de numeros primo
int serie2(int a[], int tam);

// La serie 3 es la serie de fibonacci
int serie3(int a[], int tam);

int main(){

    int filas = 3;
    int columnas = 10;

    /* 
    Matriz de ejemplo
    
    {1, 3, 6, 10, 15, 21, 28, 36, 45, 55},
    {2, 3, 5, 7, 11, 13, 17, 19, 23, 29},
    {0, 1, 1, 2, 3, 5, 8, 13, 21, 34}
    
    */

    int matriz[filas][columnas];

    int temp = 0; // Una variable temporal para poner valor en la matriz
    for(int i = 0; i < filas; i++){
        for(int j = 0; j < columnas; j++){
            while (true){
                std::cout<< "Ingese el elemento de la fila #"<<i+1<<" y la columna #"<<j+1<<": ";
                
                //Verificamos si se ingresa el mismo tipo de dato que se pide
                if (!(std::cin>>temp)){
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout<< "Ingrese un numero entero por favor.\n";
                    continue;
                }
                break; 
            }          
            matriz[i][j] = temp; 
        }
    }
    
    std::cout<<"Teniendo la matriz:\n\n";

    //Calculando la cantidad de elementos tanto de las filas como las columnas

    for(int i = 0; i < filas; i++){
        for(int j = 0; j < columnas;j++){
            std::cout<<matriz[i][j]<<" | ";
        }
            std::cout<<"\n";
    }
    std::cout<<"\n";

    int s1 = serie1(matriz[0], columnas);
    int s2 = serie2(matriz[1], columnas);
    int s3 = serie3(matriz[2], columnas);


    // Aqui se verifica cuales series devolvieron algun error o si por el contrario no se encontro ninguno(-1)
    if(s1 == -1 && s2 == -1 && s3 == -1){
        std::cout<<"No hay codigo incorrecto, todo esta bien\n";
    } else if(s1 != -1 && s2 != -1 && s3 != -1){
        std::cout<<"Codigo incorrecto: ("<<matriz[0][s1]<<")-("<<matriz[1][s2]<<")-("<<matriz[2][s3]<<")\n\n";
        std::cout<<"Los errores se encuentran en los indices: ([0]["<<s1<<"])-([1]["<<s2<<"])-([2]["<<s3<<"])\n";
    }else if(s1 == -1 && s2 == -1){
        std::cout<<"Codigo incorrecto: ("<<matriz[2][s3]<<")\n\n";
        std::cout<<"El error se encuentra en el indice: ([2]["<<s3<<"])";
    }else if(s1 == -1 && s3 == -1){
        std::cout<<"Codigo incorrecto: ("<<matriz[1][s2]<<")\n\n";
        std::cout<<"El error se encuentra en el indice: ([1]["<<s2<<"])";
    }else if(s2 == -1 && s3 == -1){
        std::cout<<"Codigo incorrecto: ("<<matriz[0][s1]<<")\n\n";
        std::cout<<"El error se encuentra en el indice: ([0]["<<s1<<"])";
    }else if(s1 == -1){
        std::cout<<"Codigo incorrecto: ("<<matriz[1][s2]<<")-("<<matriz[2][s3]<<")\n\n";
        std::cout<<"Los errores se encuentran en los indices: ([1]["<<s2<<"])-([2]["<<s3<<"])\n";
    }else if(s2 == -1){
        std::cout<<"Codigo incorrecto: ("<<matriz[0][s1]<<")-("<<matriz[2][s3]<<")\n\n";
        std::cout<<"Los errores se encuentran en los indices: ([0]["<<s1<<"])-([2]["<<s3<<"])\n";
    }else if(s3 == -1){
        std::cout<<"Codigo incorrecto: ("<<matriz[0][s1]<<")-("<<matriz[1][s2]<<")\n\n";
        std::cout<<"Los errores se encuentran en los indices: ([0]["<<s1<<"])-([1]["<<s2<<"])\n";
    }

    return 0;
}

int serie1(int a[], int tam){

    // Lo que retorna es un indice del  array

    int sum = 2;

    // Si el primer elmento es diferente de 1, ese es el error
    if(a[0] != 1){
        return 0;
    }

    // Este for recorre el array y si no cumple con la serie, se encuentra el error 
    for(int i = 1; i < tam; i++){
        if (a[i] != a[i-1] + sum){
            return i;
        }
        sum++;
    }
    
    return -1;
}

// Esta funcion verifica si un numero es primo
bool esPrimo(int num){
    int cont = 0;

    if(num < 0 || num == 0){return false;}

    for(int i = 2; i < num; i++){
        if(num%i == 0){cont++;}
    }
    
    if(cont != 0){return false;}
    
    return true;
}

// Esta funcion verifica si un numero esta repetido en un array
bool esRepetido(int a[], int n, int tam){
    int cont = 0;
    
    for(int i = 0; i < tam; i++){
        if(n == a[i]){
            cont++;
        }
    }

    if(cont > 1){
        return true;
    }

    return false;
};

int serie2(int a[], int tam){
    
    // Lo que retorna es un indice del array

    for(int i = 0; i<tam - 1; i++){
        if(esPrimo(a[i])){
            if(esRepetido(a,a[i], tam)){
                // Si hay un numero repetido, es el que esta dañando la serie
                return i;
            }else if (a[i] > a[i + 1]){
                //Aqui se corrobora que el numero siguiente tambien sea un numero primo para poder comparar
                if(esPrimo(a[i+1])){
                    // Ya que es una serie ordenada, si el numero esta en una posicion incorrecta es el numero que daña la serie
                    return i;
                } else {
                    return i + 1;
                }
            }else{
                continue;
            }
        } else {
            return i;
        };
    }
    
    // Si el ultimo elmento es diferente del decimo numero primo, ese es el error
    if(a[9] != 29){
        return 9;
    }

    return -1;
}

int serie3(int a[], int tam){
   
    // Lo que retorna es un indice del array
   
    // Los dos primeros numeros en la serie de fibonacci son el 0 y el 1
    if(a[0] != 0){
        return 0;
    } else if(a[1] != 1){
        return 1;
    }

    // For par ver si el numero a verificar es la suma de los dos numeros anteriores, sino ese es el error
    for(int i = 2; i < tam; i++){
        if(a[i] != a[i-1] + a[i-2]){
            return i;
        }
    }
    
    return -1;
}