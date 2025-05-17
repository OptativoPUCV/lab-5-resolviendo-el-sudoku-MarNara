#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
  //int ver[10] = {0}; 
  //validar por partes, porque dice que por su culpa me sale mal el get
  //validar las ilas
  for(int i = 0; i < 9;i++){
    int ver[10]= {0};//iniciar un arreglo de 10 para verificar si ya aparecieron numeros del 1 al 9.

    for(int j = 0; j < 9; j++){
      int numero = n->sudo[i][j];
      if(numero && ver[numero]){ // si ya apareció no es valido
        return 0;
      }
      ver[numero] = 1;//aqui marcamos la primera aparicion del num
    }
  }

  //validar las columnas
  for(int i = 0; i < 9;i++){
    int ver[10]= {0};
    for(int j = 0; j < 9; j++){
      int numero = n->sudo[j][i];
      if(numero && ver[numero]){
        return 0;
      }
      ver[numero] = 1;
    }
  }

  //validar las submatrices, usar k y l
  //revisar cada numero o bloque en el que se encuentra el numero de la matriz realizando un "doble matriz"
  for(int bloqueNum_k = 0; bloqueNum_k < 3; bloqueNum_k++){
    for(int bloqueNum_l = 0; bloqueNum_l < 3; bloqueNum_l++){
      int ver[10] = {0};
      for(int k = 0; k < 3;k++){
        for(int l = 0; l < 3; l++){
          int numero = n->sudo[k][l];
          if(numero && ver[numero]){
            return 0;
          }
          ver[numero] = 1;
        }
      }
    }
  }
  
  /*
  int ver[10];
  for(int i = 0; i < 9;i++){
    for(int k = 0 ; k < 10; k++){
      ver[k] = 0;
    } 
    for(int j = 0; j < 9; j++){
      int numero = n->sudo[i][j];
      if(numero && ver[numero]){
        return 0;
      }
      ver[numero] = 1;
      
      int h = 3 * (i/3) + (j /3);
      int p;  
      for(p=0;p<9;p++){
        int i=3*(h/3) + (p/3) ;
        int j=3*(h%3) + (p%3) ;
        printf("%d ",n->sudo[i][j]);
        if(p%3 == 2) printf("\n");
      }
      printf("\n");
      
    }
  }*/
  return 1;
}


List* get_adj_nodes(Node* n){
    List* list=createList();
    //comprobar si hay o no uno
    int esta = 0;
    //recorrer el sudoku
    for(int i = 0; i < 9 && !esta; i++){//
      for(int j = 0; j < 9 && !esta; j++){//
        if(n->sudo[i][j] == 0)
        {
          esta = 1;
          for(int v = 1; v <= 9; v++){
            Node* nuevo_nodo = copy(n);//recordar que necesito una copia del nodo no un nuevo nodo
            nuevo_nodo->sudo[i][j] = v;
            if(is_valid(nuevo_nodo)){
              pushBack(list, nuevo_nodo);//agrego el nodo
            }
            else{
              free(nuevo_nodo);
            }
            
            

          }
        }
        
      }
    }
    return list;
}


int is_final(Node* n){
  for(int i = 0; i < 9; i++){
    for(int j = 0; j < 9; j++){
      if(n->sudo[i][j] == 0){//recordar que sudo es una matriz :(
        return 0;
      } 
    }
  }
  return 1;
    
}

/*1. Cree un stack S (pila) e inserte el nodo.
2. Mientras el stack S(pila) no se encuentre vacío:

   a) Saque y elimine el primer nodo de S./
   
   b) Verifique si corresponde a un estado final, si es así retorne el nodo./
   
   c) Obtenga la lista de nodos adyacentes al nodo. /
   
   d) Agregue los nodos de la lista (uno por uno) al stack S. //probar con while
   
   e) Libere la memoria usada por el nodo.
   
3. Si terminó de recorre el grafo sin encontrar una solución, retorne NULL.

Almacene en la variable cont, la cantidad de iteraciones que realiza el algoritmo.*/

Node* DFS(Node* initial, int* cont){
  
  Stack* pila = createStack();//S
  push(pila, initial);
  
  while(!is_empty(pila)){
    Node* new_nodo = (Node*)top(pila);
    pop(pila);
    
    if(is_final(new_nodo)){
      return new_nodo;
    }
    List * lista_adja = get_adj_nodes(new_nodo);
    //usar el primer nodo para recorrer la lista
    Node* current_nodo = (Node*)first(lista_adja);//nodo para recorrer la lista
    while(current_nodo != NULL) {  //para agregar se usaba push
      push(pila, current_nodo);
      //aumentar cont
      cont++,
      //pasar al siguiente
      current_nodo = (Node*) next(lista_adja);
    }
    free(new_nodo);
    return NULL;
  }
  
  
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/