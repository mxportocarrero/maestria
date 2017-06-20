#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

typedef vector<int> vint;

/*********************************/
template<class T>
struct CLess{
   inline bool operator()(T a, T b){return a < b;}
};

template<class T>
struct CGreater{
   inline bool operator()(T a, T b){return a > b;}
};
/*********************************/

template<class T>
vector<T> getData(string fileName){
   vector<T> dataList;
   ifstream myFile(fileName);
   T data;
   while(myFile >> data){
      dataList.push_back(data);
   }
   return dataList;
}

template<class T>
void imprimir(const vector<T>& lista){
   for(auto x: lista) cout << " " << x;
   cout << endl;
}

template<class T,class C>
vector<T> mergeLists(const vector<T> &Left,const vector<T>& Right){
   vector<T> mergedList;
   int i = 0,j = 0;

   C compFunctor;

   while(i + j < Left.size() + Right.size()){
      if(i == Left.size()){
         mergedList.push_back(Right[j]); j++;
      } else if (j == Right.size()){
         mergedList.push_back(Left[i]); i++;
      }else{
         if(compFunctor(Left[i],Right[j])){
            mergedList.push_back(Left[i]); i++;
         } else{
            mergedList.push_back(Right[j]); j++;
         }
      }
   }
   return mergedList;
}

template<class T,class C>
vector<T> mergeSort(const vector<T> &lista){
   if(lista.size() < 2) return lista;
   vector<T> LF, LR;
   for(int i = 0; i < lista.size()/2;i++) LF.push_back(lista[i]);
   for(int i = lista.size()/2;i<lista.size();i++) LR.push_back(lista[i]);
   //imprimir(LF);imprimir(LR);
   vector<T> LOF = mergeSort<T,C>(LF), LOR = mergeSort<T,C>(LR);
   //imprimir(LOF);imprimir(LOR);
   vector<T> mergedList = mergeLists<T,C>(LOF,LOR);
   return mergedList;
}

int main(){
   for(int i = 1; i<=15;i++){
      string str = "test_" + to_string(i) + "k.txt";
      vector<int> dataList = getData<int>(str);
      //imprimir<int>(dataList);

      clock_t start = clock();

      vector<int>mergedList = mergeSort<int,CGreater<int>>(dataList);

      clock_t end = clock();
      double time = (double) (end-start) / CLOCKS_PER_SEC * 1000.0;
      cout << time << endl;
      dataList.clear();
   }
}
