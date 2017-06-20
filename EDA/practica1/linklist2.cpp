#include <iostream>
#include <string>
#include <fstream>

/* POLIMORFISMO Y FUNCIONES VIRTUALES */
template<class T>
class Sorter{
   public:
   virtual bool compare(T a, T b)=0;
};

template<class T>
class CGreater:public Sorter<T>{
   public:
      virtual bool compare(T a, T b){ return a > b;}
};

template<class T>
class CLess:public Sorter<T>{
   public:
      virtual bool compare(T a, T b){ return a < b;}
};

using namespace std;

template<class T>
struct CNode{
   T m_data;
   CNode<T> * m_next;
   CNode(T x):m_data(x), m_next(nullptr){};
};

template<class T>
class Clist{
   CNode<T> * m_head;
   Sorter<T> *compFunction;
   public:
      Clist(Sorter<T> *func):m_head(nullptr),compFunction(func){};
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
Clist<T> getData(string fileName, Sorter<T> *cmp){
   Clist<T> dataList(cmp);
   ifstream myFile(fileName);
   T data;
   while(myFile >> data){
      dataList.insertar(data);
   }
   return dataList;
}

int main(){
   Sorter<int> *comp = new CGreater<int>();
   for(int i = 1; i<=15;i++){
      string str = "testA_" + to_string(i) + ".txt";

      clock_t start = clock();

      Clist<int> dataList = getData<int>(str,comp);

      clock_t end = clock();

      double time = (double) (end-start) / CLOCKS_PER_SEC * 1000.0;

      cout << time << endl;
      dataList.clear();
   }
}

template<class T>
bool Clist<T>::buscar(T x, CNode<T> ** &p){
   p = &m_head;
   while(*p && compFunction->compare(x, (*p)->m_data))
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

