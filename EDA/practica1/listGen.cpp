#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <time.h>
#include <string>

using namespace std;
void listGen(int sizeVector, string myFile){
   vector<int> v;
   for(int i = 0; i < sizeVector;i++) v.push_back(i);
   random_shuffle(v.begin(),v.end());

   //for(int i= 0; i < v.size();i++) cout << " " << v[i];

   ofstream myfile(myFile);
   if(myfile.is_open()){
      for(int i= 0; i < v.size();i++) {
         myfile << " " << v[i];
         if(i%20==0) myfile << '\n';
      }
      myfile.close();
   }
}

int main(){
   srand(time(nullptr));

   for(int i= 1; i<= 15;i++){
      int sized = i*3000;
      string str = "testA_";
      str += to_string(i) + ".txt";
      listGen(sized,str);
   }
}

