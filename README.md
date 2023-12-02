# OS-Project-2: Banker’s Algorithm for Deadlock Avoidance

Andrew Cash - 12/1/2023

## Introduction

A system in a safe state has no deadlocks, whereas a system in an unsafe state has a possibility of deadlock. The Banker's algorithm is used to define whether a system is in an unsafe or safe state, and thus can be used to avoid deadlock. For this, a process must define its maximum use of resources, it must be able to wait, and it must be able to return all its resources in a finite amount of time.

## Solving the Problem

Defined in this problem will be matrices showing the maximum allocated resources and currently allocated resources for each process in the system, usually referred to as "max" and "allocated". These matrices will be n by m, n being the number of processes in the system, and m being the number of different resources. There will also be a vector of m length, simply representing how much of each resource is available.

For this problem, we were to use an input file with a customized format to store the information that will be placed in the aforementioned vector and matrices. In my format, matrices max and allocated are referred to by characters 'M' and 'A', and vector available by 'V'. This character will be read, and then a switch statement is used to store the data in the right variable. The matrices are stored with type vector<vector<int>>, and the vector is simply vector<int>.

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

#### Initialization of the "Need" Matrix

```c++
vector<vector<int>> need(processNum, vector<int>(resourceNum, 0));    

  for(int i = 0; i < processNum; ++i){                                     //
    for(int j = 0; j < resourceNum; ++j){                                  //
      need[i][j] = max[i][j] - allocated[i][j];                            //initializes need matrix as max[i,j] - allocated[i,j]
    }                                                                      //
  }                                                                        //
```

Once processes are done running their resources will be released. Thus, it is necessary to keep track of which resources are available after that happens. Here, vector "work" will be used for that. It is initialized to be the same as the avialable vector, but the number of resources released after each process runs will be added to the contents of the vector work.

Two more vectors will be used. First, Boolean vector finish, which is length m, or rather, the number of processes. It will simply be used to keep track of which processes have executed and which haven't. Also, there is Boolean vector lastFirst. It will be used to end the while loop surrounding the for loop that goes through each process. It is set equal to the vector first. If no values of vector first change after checking each process, then the loop ends, as either the safe sequence is found, or the system is not in a safe state.

## The Safety Algorithm

The Safety Algorithm will essentially loop over every process that hasn't been able to execute, and check if the resources it needs are available. If they aren't, the next process is checked, if they are, then those resources are released, and added to vector work, which means more resources are available for the other processes. The number of that process reflected in the Boolean vector finish is also changed to be true. This will continue until there is no change in the vector finish after checking all processes, at which point it will be clear if the system is safe or not by the contents of the vector finish. Below is the code for this algorithm, which also has some print statements to help track the program.

```c++
while(finish!=lastFinish){                                               //This will check over every process until no more processes are becoming free.

    lastFinish = finish;                                                   //Set for comparison. If there is no change, end the loop.
    
    for(int i = 0; i < processNum; ++i){                                   //Goes through each process

      if(finish[i] == false){                                              //If this true, then the process has already been confirmed, no need to check

          std::cout << "Checking Process " << i << std::endl;              //
                                                                           //Printing which process i and the resources needed from need matrix
          std::cout << "Needs of process " << i << ": ";                   //
          printVec(need[i]);                                               //

          std::cout << "Current resources: ";                              //Printing current resources from work vector
          printVec(work);                                                  //

        if(workGreaterEqualNeedi(need, i, work)){                          //
          std::cout << "P" << i << " can finish\n";                        //If the resource need of this process i is less than or equal to the current resources available
          finish[i] = true;                                                //then process i can currently finish. Set it's corresponding element to be true, and push onto safe sequence
          safeSequence.push_back(i);                                       //

          std::cout << "Resources freed: ";                                //
          for(int j = 0; j < work.size(); ++j){                            //
            work[j] = work[j] + allocated[i][j];                           //Since Process i is finished, its resources are free. Add them to the current working resources.
            std::cout << allocated[i][j] << " ";                           //Print out the freed resources
          }                                                                //
          std::cout << std::endl;                                          //

          for(int i = 0; i < safeSequence.size(); ++i){                    //
            std::cout << "P" << safeSequence[i] << " -> ";                 //Show the current safe sequence
          }                                                                //
          std::cout << std::endl;                                          //

        }
        else{                                                              //
          std::cout << "P" << i << " can't go\n";                          //Resource need is greater than currently available, process i can't go, remains false in "finish"
        }                                                                  //
      }
    }
  }

  for(int i = 0; i < processNum; ++i){
    if(!finish[i]){
      std::cout << "\nSystem is NOT IN SAFE STATE\n";
      return 0;
    } 
  }
  std::cout << "\nSystem is in a safe state\n";
  std::cout << "The safe sequence: \n";
  for(int i = 0; i < processNum-1; ++i){
    std::cout << "P" << safeSequence[i] << " -> ";
  }
  std::cout << "P" << safeSequence[processNum-1] << std::endl;
  return 0;
```

### Input and Output

Below is an example of this program's input and output.

```
A 010
  200
  302
  211
  002

M 753
  322
  902
  222
  433

V 332
```

```
Checking Process 0
Needs of process 0: 7 4 3 
Current resources: 3 3 2 
P0 can't go
Checking Process 1
Needs of process 1: 1 2 2 
Current resources: 3 3 2 
P1 can finish
Resources freed: 2 0 0 
P1 -> 
Checking Process 2
Needs of process 2: 6 0 0 
Current resources: 5 3 2 
P2 can't go
Checking Process 3
Needs of process 3: 0 1 1 
Current resources: 5 3 2 
P3 can finish
Resources freed: 2 1 1 
P1 -> P3 -> 
Checking Process 4
Needs of process 4: 4 3 1 
Current resources: 7 4 3 
P4 can finish
Resources freed: 0 0 2 
P1 -> P3 -> P4 -> 
Checking Process 0
Needs of process 0: 7 4 3 
Current resources: 7 4 5 
P0 can finish
Resources freed: 0 1 0 
P1 -> P3 -> P4 -> P0 -> 
Checking Process 2
Needs of process 2: 6 0 0 
Current resources: 7 5 5 
P2 can finish
Resources freed: 3 0 2 
P1 -> P3 -> P4 -> P0 -> P2 -> 

System is in a safe state
The safe sequence: 
P1 -> P3 -> P4 -> P0 -> P2
```
