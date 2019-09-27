#include <stdio.h>
#include <stdlib.h>

typedef struct dataItem{
  int data;
  int index;
  int key;
  struct dataItem *nextItem;
} DataItem;

typedef struct soultionStruct{
  int sourceIndex;
  int targetsIndex;
  struct soultionStruct *nextSolution;
} SolutionStruct;

void createEmptyHashTable(int size, DataItem ***hashTable);
void insertInHash(int data, int index, DataItem **hashTable, int size);
void fillHashTable(int size, int *dataArray, DataItem **hashTable);
void printHashTable(DataItem **hashTable, int size);
SolutionStruct *findSum(int target, int *dataArray, int size, DataItem **hashTable);
void readSolutionSet(SolutionStruct **solutionSet);

int main(void){

  int dataArray[] = {1, 5, 6 ,7, 9, 2, 4, 4, 4, 2, 3, 10, 100, 67, 5};
  int size = 15;

  DataItem **hashTable = NULL;

  createEmptyHashTable(size, &hashTable);
  fillHashTable(size, dataArray, hashTable);
  printHashTable(hashTable, size);

  SolutionStruct* solutionSet = findSum(8, dataArray, size, hashTable);
  //readSolutionSet(solutionSet);

  return 0;
}

void createEmptyHashTable(int size, DataItem ***hashTable){

  *hashTable = malloc(size * sizeof(DataItem *));
  for(int i = 0; i <= size - 1; i++){

    (*hashTable)[i] = NULL;
  }
}

void insertInHash(int data, int index, DataItem **hashTable, int size){
    int key = data % size;

    DataItem *newEntry = malloc(sizeof(DataItem));

    newEntry->data = data;
    newEntry->index = index;
    newEntry->key = key;
    newEntry->nextItem = NULL;

    if(hashTable[key] == NULL){
      hashTable[key] = newEntry;
    }

    else{
      DataItem *currentDataItem = hashTable[key];

      while(currentDataItem->nextItem != NULL){
        currentDataItem = currentDataItem->nextItem;
      }

      currentDataItem->nextItem = newEntry;
    }


}

void fillHashTable(int size, int *dataArray, DataItem **hashTable){
  for(int i = 0; i <= size - 1; i++){
    insertInHash(dataArray[i], i, hashTable, size);
  }

}


void printHashTable(DataItem **hashTable, int size){
  printf("-----Hash Table Print Out-----\n");
  for(int i = 0; i <= size - 1; i++){
    printf("%d: ", i);
    DataItem *currentDataItem = hashTable[i];
    while(currentDataItem != NULL){
      printf("%d ", currentDataItem->data);
      currentDataItem = currentDataItem->nextItem;
    }
    printf("\n");
  }

}

SolutionStruct *findSum(int target, int *dataArray, int size, DataItem **hashTable){
  SolutionStruct *solutionSet = malloc(sizeof(SolutionStruct));
  solutionSet = NULL;
  for(int i = 0; i <= size - 1; i++){
    printf("%d of %d\n", i, size - 1);
    int lookup = target - dataArray[i];

    int key = lookup % size;

    DataItem *currentDataItem = hashTable[key];
    while(currentDataItem != NULL){
      if(currentDataItem->data == target && currentDataItem->index != i){
        SolutionStruct *newSolution = malloc(sizeof(SolutionStruct));

        newSolution->sourceIndex = i;
        newSolution->targetsIndex = currentDataItem->index;
        newSolution->nextSolution = solutionSet;

        solutionSet = newSolution;

      }

      currentDataItem = currentDataItem->nextItem;
    }
  }

  return solutionSet;
}

void readSolutionSet(SolutionStruct **solutionSet){
  printf("-----Solution Set-----\n");
  if(*solutionSet == NULL){
    printf("NO SOLUTIONS WERE FOUND\n");
    return;
  }

  SolutionStruct *currentSolution = *solutionSet;
  while(currentSolution != NULL){
    printf("[%d, %d]\n", currentSolution->sourceIndex, currentSolution->targetsIndex);

    currentSolution = currentSolution->nextSolution;
  }
}
