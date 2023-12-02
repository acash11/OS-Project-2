# OS-Project-2
Banker’s Algorithm for deadlock avoidance

## Introduction

A system in a safe state has no deadlocks, where a system in an unsafe state has a possibility of deadlock. The Banker's algorithm is used to define whether a system is in an unsafe or safe state, and thus can be used to avoid deadlock. For this, a process must define its maximum use of resources, it must be able to wait, and it must be able to return all its resources in a finite amount of time.

### Solving the problem at hand

Defined in this problem will be matrices showing the maximum allocated rescoures and currently allocated resources for each process in the system, usually referred to as "max" and "allocated". These matrices will be n by m, n being the number of processes in the system, and m being the number of different resources. There will also be a vector of m length, simply representing how much of each resource is available.

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
