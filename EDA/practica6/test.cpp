#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <ctime>
#include <queue>

typedef std::vector<int> vint;

/**Imprimiendo el vector**/
void printVector(vint  w){
    for(auto & x : w) std:: cout << x << " ";
    std::cout << std::endl;
}


template <typename T>
struct cmpLess { inline bool operator()(const T &t1, const T &t2) const { return (t1 < t2); } };

template <typename T>
struct cmpGreater { inline bool operator()(const T &t1, const T &t2) const { return (t2 < t1); } };

/**
=====================================================
DECLARACION DE LAS FUNCIONES PUBLICAS
=====================================================
**/

/**================= INSERT SORT =================**/
template <typename RandomAccessIterator>
inline void InsertSort(RandomAccessIterator start, RandomAccessIterator end) {
  cmpLess < typename RandomAccessIterator::value_type > lessThan;
  InsertSort(start,end,lessThan);
}
/**================= SELECT SORT =================**/
template <typename RandomAccessIterator>
inline void SelectSort(RandomAccessIterator start, RandomAccessIterator end) {
  cmpLess < typename RandomAccessIterator::value_type > lessThan;
  SelectSort(start, end, lessThan);
}
/**================= STABLE SELECT SORT =================**/
template <typename RandomAccessIterator>
inline void StableSelectSort(RandomAccessIterator start, RandomAccessIterator end) {
  cmpLess < typename RandomAccessIterator::value_type > lessThan;
  StableSelectSort(start, end, lessThan);
}
/**================= HEAPSORT =================**/
template <typename RandomAccessIterator>
inline void HeapSort(RandomAccessIterator start, RandomAccessIterator end) {
  cmpLess < typename RandomAccessIterator::value_type > lessThan;
  HeapSort(start, end, lessThan);
}
/**================= MERGE SORT =================**/
template <typename RandomAccessIterator>
inline void MergeSort(RandomAccessIterator start, RandomAccessIterator end) {
  cmpLess < typename RandomAccessIterator::value_type > lessThan;
  MergeSort(start, end, lessThan);
}
/**================= ITERATIVE MERGE SORT =================**/
template <typename RandomAccessIterator>
inline void IterativeMergeSort(RandomAccessIterator start, RandomAccessIterator end) {
  cmpLess < typename RandomAccessIterator::value_type > lessThan;
  IterativeMergeSort(start, end, lessThan);
}
/**================= LOMUTO QUICK SORT =================**/
template <typename RandomAccessIterator>
inline void LomutoQuickSort(RandomAccessIterator start, RandomAccessIterator end) {
  cmpLess < typename RandomAccessIterator::value_type > lessThan;
  LomutoQuickSort(start, end, lessThan);
}


/**
=====================================================
DEFINICION DE LAS FUNCIONES DE ORDENAMIENTO
*START ACCEDE AL PRIMER ELEMENTO DEL VECTOR
*END VA AL ÚLTIMO ELEMENTO DEL VECTOR +1
*(END-1) ACCEDE AL ULTIMO ELEMENTO DEL VECTOR
=====================================================
**/
/**================= INSERT SORT =================**/
template <typename RandomAccessIterator, typename LessThan>
inline void InsertSort(RandomAccessIterator start, RandomAccessIterator end, LessThan &lessThan) {
    int sz = end-start;
    vint vec;
    auto i = start;
    vec.push_back(*(i++));

    for(; i != end ; ++i){
        int counter = 0;
        vint::iterator it = vec.begin();
        while( counter < vec.size() && lessThan( *(it+counter),*i ) ) counter++;
        vec.insert(it+counter,*i);
    }

    for(int i = 0; i <sz;++i) *(start + i) = vec[i];
}
/**================= SELECT SORT =================**/
template <typename RandomAccessIterator, typename LessThan>
inline void SelectSort(RandomAccessIterator start, RandomAccessIterator end, LessThan &lessThan) {
  int iSZ = end-start, sSZ = 0;
  while(iSZ > 0){
    auto minimun = start + sSZ;
    for(auto i = minimun; i != end; i++){
        if( lessThan( *i,*minimun ) ) minimun = i;
    }
    typename RandomAccessIterator::value_type tmp = *(start + sSZ);
    //std::cout<< "(" << *start << "," << *minimun << "," << tmp << ")";
    *(start + sSZ) = *minimun;
    *minimun = tmp;
    iSZ--; sSZ++;
  }
}
/**================= STABLE SELECT SORT =================**/
template <typename RandomAccessIterator, typename LessThan>
inline void StableSelectSort(RandomAccessIterator start, RandomAccessIterator end, LessThan &lessThan) {
  int iSZ = end-start, sSZ = 0;
  while(iSZ > 0){
     auto minimun = start + sSZ;

     for(auto i = minimun; i != end; i++){
        if( lessThan( *i,*minimun ) ) minimun = i;
    }

    typename RandomAccessIterator::value_type tmp = *minimun;

    for(auto i = minimun; i != start + sSZ;i--){
        *i = *(i-1);
    }
    *(start+sSZ) = tmp;

    iSZ--;sSZ++;
  }
}
/**================= HEAPSORT =================**/
template <typename RandomAccessIterator, typename LessThan>
inline void HeapSort(RandomAccessIterator start, RandomAccessIterator end, LessThan &lessThan) {
  // Adicione el código de Heap Sort, use std::make_heap y std::pop_heap.
  const int sz = end-start;

  std::make_heap(start,end,lessThan);
  for(int i = 0; i < sz;i++){
        std::pop_heap(start,end-i,lessThan);
  }
}
/**================= MERGE SORT =================**/
template <typename RandomAccessIterator, typename LessThan>
inline void MergeSort(RandomAccessIterator start, RandomAccessIterator end, LessThan &lessThan) {
    if(end-start < 2) return;
    int sz = end-start;
    int partition = (end-start)/2;

    vint vec1(start,start + partition);
    //printVector(vec1);std::cout << std::endl;
    vint vec2(start + partition,end);
    //std::cout << "v2:";printVector(vec2);std::cout << std::endl;

    MergeSort(vec1.begin(),vec1.end());

    MergeSort(vec2.begin(),vec2.end());
    //printVector(vec2);

    for(int i = 0, j = 0; i+j < sz;){
        if(i == vec1.size()){
            *(start + i + j) = *(vec2.begin()+j);j++;
        }
        else if(j == vec2.size()){
            *(start + i + j) = *(vec1.begin()+i);i++;
        }
        else {
            if( lessThan(*(vec1.begin()+i),*(vec2.begin()+j)) ){
                *(start + i + j) = *(vec1.begin()+i);i++;
            }else{
                *(start + i + j) = *(vec2.begin()+j);j++;
            }
        }
    }
}
/**================= ITERATIVE MERGE SORT =================**/
template <typename RandomAccessIterator, typename LessThan>
inline void IterativeMergeSort(RandomAccessIterator start, RandomAccessIterator end, LessThan &lessThan) {
  // Adicione el código de Merge Sort.
  std::queue<vint> Cola;
  for(auto x = start; x != end; x++){
    vint tmp = {*x};
    Cola.push(tmp);
  }
  while(Cola.size() > 1){
    vint vec1 = Cola.front(); Cola.pop();
    vint vec2 = Cola.front(); Cola.pop();

    int sz = vec1.size() + vec2.size();

    vint tmp(sz); vint::iterator startTmp = tmp.begin();

    for(int i = 0, j = 0; i+j < sz;){
        if(i == vec1.size()){
            *(startTmp + i + j) = *(vec2.begin()+j);j++;
        }
        else if(j == vec2.size()){
            *(startTmp + i + j) = *(vec1.begin()+i);i++;
        }
        else {
            if( lessThan(*(vec1.begin()+i),*(vec2.begin()+j)) ){
                *(startTmp + i + j) = *(vec1.begin()+i);i++;
            }else{
                *(startTmp + i + j) = *(vec2.begin()+j);j++;
            }
        }
    }
    Cola.push(tmp);
  } // fin del bucle while
  for(int i = 0; i < end-start;i++){
    *(start + i) = *(Cola.front().begin()+i);
  }
}
/**================= LOMUTO QUICK SORT =================**/
template<typename RandomAccessIterator, typename LessThan>
int LomutoPartition(RandomAccessIterator start, RandomAccessIterator end, LessThan &lessThan){
    auto low = start, high = end-1;
    int middle = 0;
    typename RandomAccessIterator::value_type pivot = *start;
    auto i = low + 1;


    return middle;
}

template <typename RandomAccessIterator, typename LessThan>
inline void LomutoQuickSort(RandomAccessIterator start, RandomAccessIterator end, LessThan &lessThan) {
  // Adicione el código de Quick Sort de Lomuto.
}
/**
=====================================================
FUNCION MAIN DEL CODIGO
=====================================================
**/

int main(int argc, char** argv) {

/**Typedef de un puntero a funcion a recibe dos iteradores y que devuelve un void**/
  typedef void (*SORT_ALGORITHM)(std::vector<int>::iterator, std::vector<int>::iterator);

/*los vectores deben llenarse a partir de 1000 para que esten desordenados*/

  for ( auto & i : {500}){

    vint w(i),v;

    std::iota(w.begin(), w.end(), 1);

    for(auto a = w.begin(), _a = w.begin()+i/100; a < w.end(); _a += i/100)
    {
      std::shuffle (a, _a, std::default_random_engine(std::time(0)));
      a = _a;
    }

    // retire el comentario para estudiar datos completamente desordenados:
    //std::shuffle (w.begin(), w.end(), std::default_random_engine(std::time(0)));

    /** VECTOR DE PUNTEROS A FUNCIONES DE ORDENAMIENTO **/
    std::vector<SORT_ALGORITHM> sort_algorithms = {LomutoQuickSort};

    for ( auto & sort_algorithm : sort_algorithms){
      v = w;

      std::clock_t inicio = std::clock();
      sort_algorithm(v.begin(),v.end());
      std::cout << 1000.0 * (double)(std::clock()-inicio)/(double)CLOCKS_PER_SEC << ", " << std::flush;
      printVector(v);
    }

    std::cout << std::endl;
  }
  return 0;
} // FIN DEL MAIN
