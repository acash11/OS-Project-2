//Andrew Cash
//Operating Systems Fall 2023
//12/1/2023
//source code file for programming assignment 2, Banker’s Algorithm for deadlock avoidance

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

void outputMatrix(vector<vector<int>> x){
  for(int i = 0; i < processNum; ++i){
    for(int j = 0; j < resourceNum; ++j){
      std::cout << x[i][j];
    }
    std::cout << std::endl;
  }
  return;
}


int main(){

  //Opening input file//
  std::ifstream input("inputBank.txt");
  if (!input.is_open()){
      std::cerr << "Error: couldn't open file\n";
      exit(1);
  }
  //////////////////////

  //Taking in input txt file//
  char ch = 0;

  //inputting allocated and max matrix
  for(int k = 0; k < 2; ++k){
    for(int i = 0; i < processNum; ++i){
      for(int j = 0; j < resourceNum; ++j){

        if(!(input >> ch)){exit(1);}


        if(k == 0){
          allocated[i][j] = ch;
        }else{
          max[i][j] = ch;
        }


        std::cout << ch;
      }
    }
  }

  input.close();

  outputMatrix(allocated);
  outputMatrix(max);
  return 0;
  //next: type convert char input to integers for the matrices
}