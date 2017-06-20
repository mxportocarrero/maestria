#include <iostream>
#include <string>
#include <fstream>

using namespace std;

/* PUNTEROS A FUNCION */
template<class T>
bool Cless(T a, T b){ return a < b; };

template<class T>
bool Cgreater(T a, T b){ return a > b; };

template<class T>
struct CNode{
   T m_data;
   CNode<T> * m_next;
   CNode(T x):m_data(x), m_next(nullptr){};
};

template<class T>
class Clist{
   CNode<T> * m_head;
   bool (*compFunction)(T,T);
   public:
      Clist(bool func(T,T)):m_head(nullptr),compFunction(func){};
      bool buscar(T x, CNode<T> ** &p);
      bool insertar(T x);
      bool borrar(T x);
      void imprimir(){
         CNode<T> *p = m_head;
         while(p){
            cout << p->m_data << ", ";
            p = p->m_next;
         }
         cout << endl;
      }
      void clear(){
         while(m_head){
            CNode<T> *tmp = m_head;
            m_head = m_head->m_next;
            delete tmp;
         }
      }
};

template<class T>
Clist<T> getData(string fileName, bool func(T,T)){
   Clist<T> dataList(func);
   ifstream myFile(fileName);
   T data;
   while(myFile >> data){
      dataList.insertar(data);
   }
   return dataList;
}

int main(){
   for(int i = 1; i<=15;i++){
      string str = "testA_" + to_string(i) + ".txt";

      clock_t start = clock();

      Clist<int> dataList = getData<int>(str,Cgreater);

      clock_t end = clock();

      double time = (double) (end-start) / CLOCKS_PER_SEC * 1000.0;
      //dataList.imprimir();

      cout << time << endl;
      dataList.clear();
   }
}

template<class T>
bool Clist<T>::buscar(T x, CNode<T> ** &p){
   p = &m_head;
   while(*p && compFunction(x,(*p)->m_data))
      p = &((*p)->m_next);
   return *p && x == (*p)->m_data;
}

template<class T>
bool Clist<T>::insertar(T x){
   CNode<T> ** p;
   if(buscar(x,p)) return 0; // no se aceptan repetidos
   CNode<T> *tmp = new CNode<T>(x);
   tmp->m_next = *p;
   *p = tmp;
   return 1;
}

template<class T>
bool Clist<T>::borrar(T x){
   CNode<T> **p;
   if(!(buscar(x,p))) return 0;
   CNode<T> *tmp = *p;
   *p = (*p)->m_next;
   delete tmp;
   return 1;
}

