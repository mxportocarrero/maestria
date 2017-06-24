#include <iostream>
#include <string>
#include <fstream>

using namespace std;

template<class T>
struct CLess{
   inline bool operator()(T a, T b){return a < b;}
};

template<class T>
struct CGreater{
   inline bool operator()(T a, T b){return a > b;}
};



template<class T>
struct CNode{
   T m_data;
   CNode<T> * m_next;
   CNode(T x):m_data(x), m_next(nullptr){};
};

/*============BINARY TREE ==*/
template<class T,class C> class listIterator;

template<class T,class C>
class Clist{
    friend class listIterator<T,C>;

   CNode<T> * m_head;
   C compFunctor;

   public:
       typedef listIterator<T,C> iterator;
      Clist():m_head(nullptr){};
      inline bool buscar(T x, CNode<T> ** &p);
      inline bool insertar(T x);
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

template<class T, classC

/*=============================*/

template<class T, class C>
Clist<T,C> getData(string fileName){
   Clist<T,C> dataList;
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

      Clist<int,CGreater<int>> dataList = getData<int,CGreater<int>>(str);

      clock_t end = clock();

      double time = (double) (end-start) / CLOCKS_PER_SEC * 1000.0;

      cout << time << endl;
      dataList.clear();
   }
}

template<class T,class C>
inline bool Clist<T,C>::buscar(T x, CNode<T> ** &p){
   p = &m_head;
   while(*p && compFunctor(x, (*p)->m_data))
      p = &((*p)->m_next);
   return *p && x == (*p)->m_data;
}

template<class T,class C>
inline bool Clist<T,C>::insertar(T x){
   CNode<T> ** p;
   if(buscar(x,p)) return 0; // no se aceptan repetidos
   CNode<T> *tmp = new CNode<T>(x);
   tmp->m_next = *p;
   *p = tmp;
   return 1;
}

template<class T, class C>
bool Clist<T,C>::borrar(T x){
   CNode<T> **p;
   if(!(buscar(x,p))) return 0;
   CNode<T> *tmp = *p;
   *p = (*p)->m_next;
   delete tmp;
   return 1;
}
