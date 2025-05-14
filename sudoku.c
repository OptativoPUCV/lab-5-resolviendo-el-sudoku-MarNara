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
  /*int ver[10];
  for(int k = 0; k < 9;k++){
    for(int i =)
  }
*/
  return 1;
}


List* get_adj_nodes(Node* n){
    List* list=createList();
    //comprobar si hay o no uno
    int esta = 0;
    //recorrer el sudoku
    for(int i = 0; i < 9 && !esta; i++){
      for(int j = 0; j < 9 && !esta; j++){
        if(n->sudo[i][j] == 0)
        {
          esta = 1;
          for(int v = 1; v <= 9; v++){
            Node* nuevo_nodo = copy(n);//recordar que necesito una copia del nodo no un nuevo nodo
            nuevo_nodo->sudo[i][j] = v;
            pushBack(list, nuevo_nodo);//agrego el nodo

          }
        }
        
      }
    }
    return list;
}


int is_final(Node* n){
    return 0;
}

Node* DFS(Node* initial, int* cont){
  return NULL;
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