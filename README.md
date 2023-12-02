# OS-Project-2
Banker’s Algorithm for deadlock avoidance

## Introduction

A system in a safe state has no deadlocks, where a system in an unsafe state has a possibility of deadlock. The Banker's algorithm is used to define whether a system is in an unsafe or safe state, and thus can be used to avoid deadlock. For this, a process must define its maximum use of resources, it must be able to wait, and it must be able to return all its resources in a finite amount of time.

## Solving the Problem

Defined in this problem will be matrices showing the maximum allocated rescoures and currently allocated resources for each process in the system, usually referred to as "max" and "allocated". These matrices will be n by m, n being the number of processes in the system, and m being the number of different resources. There will also be a vector of m length, simply representing how much of each resource is available.

For this problem, we were to use an input file with a customized formatt to store the information that will be placed in the aforementioed vector and matrices. In my formatt, matrices max and allocated are referred to by characters 'M' and 'A', and vector avilable by 'V'. This character will be read, and then a switch statement is used to store the data in the right variable. The matrices are stored with type vector<vector<int>>, and the vector is simply vector<int>.

```c++
char ch = 0;                                          //input character
  //inputting matrices and vector
  for(int k = 0; k < 3; ++k){                           //3 things: Allocated Matrix, Max Matrix, Available Vector
    if(!(input >> ch)){exit(1);}                        //Takes in the format character, A M or V, representing Allocated, Max, and Available
    switch(ch){                                         //Switch statement for handling of each structure
      case 'A':                                         //A; Available Matrix. As per matrix being 3 by 5, Takes in next 15 characters from input file
        for(int i = 0; i < processNum; ++i){
          for(int j = 0; j < resourceNum; ++j){
            if(!(input >> ch)){exit(1);}
            allocated[i][j] = ch - '0';
          }
        }
        break;
      case 'M':                                         //M; Max Matrix. As per matrix being 3 by 5, Takes in next 15 characters from input file
        for(int i = 0; i < processNum; ++i){
          for(int j = 0; j < resourceNum; ++j){
            if(!(input >> ch)){exit(1);}
            max[i][j] = ch - '0';
          }
        }
        break;
      case 'V':                                         //V; Available Vector. As per there being 3 resources, Takes in next 3 characters from input file
        for(int i = 0; i < resourceNum; ++i){
          if(!(input >> ch)){exit(1);}
          available[i] = ch - '0';
        }
        break;
      default:                                         //Unrecognized character. Exits program.
        std::cout << "Input File Error: ";
        std::cout << "Unrecognized format character."; 
        std::cout << "Exiting Program.\n";
        exit(1);
        break;
    }
  }
```

By subtracting the max amount of resources a process will need to execute by the amount currently allocated to that process, you get the amount left needed, or rather, how much of each resource a process will need to obtain for it to run. So, by subtracting the matrix max by the matrix allocated, you obtain a matrix "need", which shows the needed resources for all processes.

#### Intialization of the "Need" Matrix

```c++
vector<vector<int>> need(processNum, vector<int>(resourceNum, 0));    

  for(int i = 0; i < processNum; ++i){                                     //
    for(int j = 0; j < resourceNum; ++j){                                  //
      need[i][j] = max[i][j] - allocated[i][j];                            //initializes need matrix as max[i,j] - allocated[i,j]
    }                                                                      //
  }                                                                        //
```

