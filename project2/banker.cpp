//Andrew Cash
//Operating Systems Fall 2023
//12/1/2023
//Source code file for programming assignment 2, Banker’s Algorithm for deadlock avoidance

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using std::vector;

const int resourceNum = 3;
const int processNum = 5;
vector<vector<int>> allocated(processNum, vector<int>(resourceNum, 0));
vector<vector<int>> max(processNum, vector<int>(resourceNum, 0));
vector<vector<int>> need(processNum, vector<int>(resourceNum, 0));
vector<int> available(resourceNum, 0);

void outputMatrix(vector<vector<int>> &x){                                                //
  for(int i = 0; i < processNum; ++i){                                                    //
    for(int j = 0; j < resourceNum; ++j){                                                 //
      std::cout << x[i][j];                                                               //
    }                                                                                     //Outputs a vector vector of size processNum by resourceNum
    std::cout << std::endl;                                                               //Used for testing
  }                                                                                       //
  return;                                                                                 //
}                                                                                         //

bool workGreaterEqualNeedi(vector<vector<int>> &need, int &row, vector<int> &work){       //
  for(int i = 0; i < resourceNum; ++i){                                                   //
    if(!(need[row][i] <= work[i])){                                                       //
      return false;                                                                       //Function to compare needed resources vs current resources
    }                                                                                     //
  }                                                                                       //
  return true;                                                                            //
}                                                                                         //

void printVec(vector<int> x){
  for(int j = 0; j < x.size(); ++j){                                                      //
    std::cout << x[j] << " ";                                                             //Prints a vector
  }                                                                                       //
  std::cout << std::endl;
}

int main(){

  //Opening input file and taking in the formatted input//////////////////////////////////////////////////////////////////////////////////
  std::ifstream input("inputBank.txt");
  if (!input.is_open()){
      std::cerr << "Error: couldn't open file\n";
      exit(1);
  }

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

  input.close();

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  //outputMatrix(allocated);
  //outputMatrix(max);
  //for(int i = 0; i < available.size(); ++i){
  //  std::cout << available[i];
  //}
  //std::cout << std::endl;



  //Banker's Algorithm
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  vector<vector<int>> need(processNum, vector<int>(resourceNum, 0));    

  for(int i = 0; i < processNum; ++i){                                     //
    for(int j = 0; j < resourceNum; ++j){                                  //
      need[i][j] = max[i][j] - allocated[i][j];                            //initializes need matrix as max[i,j] - allocated[i,j]
    }                                                                      //
  }                                                                        //

  //outputMatrix(need);

  vector<int> work(resourceNum, 0);                                        //
  work = available;                                                        //Work vector equals available vector, but will be updated as resources are freed
  vector<bool> finish(processNum, false);                                  //Boolean vector representing processes that can finish
  vector<bool> lastFinish(processNum, true);                               //Will be compared to vector finish to end while loop. If "finish" doesn't change 
                                                                           //after looking at every process, then there is nothing left to find

  vector<int> safeSequence;                                                //Processes will be pushed onto this. In the end, will have the safe sequence.

  ///////////////////////


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
}