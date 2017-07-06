#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <ctime>

typedef std::vector<int> vint;

template <typename T>
struct cmpLess { inline bool operator()(const T &t1, const T &t2) const { return (t1 < t2); } };

template <typename T>
struct cmpGreater { inline bool operator()(const T &t1, const T &t2) const { return (t2 < t1); } };


template <typename RandomAccessIterator>
inline void InsertSort(RandomAccessIterator start, RandomAccessIterator end) {
  cmpLess < typename RandomAccessIterator::value_type > lessThan;
  InsertSort(start, end, lessThan);
}

template <typename RandomAccessIterator>
inline void SelectSort(RandomAccessIterator start, RandomAccessIterator end) {
  cmpLess < typename RandomAccessIterator::value_type > lessThan;
  SelectSort(start, end, lessThan);
}

template <typename RandomAccessIterator>
inline void StableSelectSort(RandomAccessIterator start, RandomAccessIterator end) {
  cmpLess < typename RandomAccessIterator::value_type > lessThan;
  StableSelectSort(start, end, lessThan);
}

template <typename RandomAccessIterator>
inline void HeapSort(RandomAccessIterator start, RandomAccessIterator end) {
  cmpLess < typename RandomAccessIterator::value_type > lessThan;
  HeapSort(start, end, lessThan);
}

template <typename RandomAccessIterator>
inline void MergeSort(RandomAccessIterator start, RandomAccessIterator end) {
  cmpLess < typename RandomAccessIterator::value_type > lessThan;
  MergeSort(start, end, lessThan);
}

template <typename RandomAccessIterator>
inline void IterativeMergeSort(RandomAccessIterator start, RandomAccessIterator end) {
  cmpLess < typename RandomAccessIterator::value_type > lessThan;
  IterativeMergeSort(start, end, lessThan);
}

template <typename RandomAccessIterator>
inline void LomutoQuickSort(RandomAccessIterator start, RandomAccessIterator end) {
  cmpLess < typename RandomAccessIterator::value_type > lessThan;
  LomutoQuickSort(start, end, lessThan);
}

template <typename RandomAccessIterator>
inline void HoareQuickSort(RandomAccessIterator start, RandomAccessIterator end) {
  cmpLess < typename RandomAccessIterator::value_type > lessThan;
  HoareQuickSort(start, end, lessThan);
}

template <typename RandomAccessIterator>
inline void YaroslavskiyQuickSort(RandomAccessIterator start, RandomAccessIterator end) {
  cmpLess < typename RandomAccessIterator::value_type > lessThan;
  YaroslavskiyQuickSort(start, end, lessThan);
}


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

template <typename RandomAccessIterator, typename LessThan>
inline void SelectSort(RandomAccessIterator start, RandomAccessIterator end, LessThan &lessThan) {
  int sz = end-start;


}

template <typename RandomAccessIterator, typename LessThan>
inline void StableSelectSort(RandomAccessIterator start, RandomAccessIterator end, LessThan &lessThan) {
  // Adicione el código de Selection Sort estable.
}

template <typename RandomAccessIterator, typename LessThan>
inline void HeapSort(RandomAccessIterator start, RandomAccessIterator end, LessThan &lessThan) {
  // Adicione el código de Heap Sort, use std::make_heap y std::pop_heap.
}

template <typename RandomAccessIterator, typename LessThan>
inline void MergeSort(RandomAccessIterator start, RandomAccessIterator end, LessThan &lessThan) {
  // Adicione el código de Merge Sort.
}

template <typename RandomAccessIterator, typename LessThan>
inline void IterativeMergeSort(RandomAccessIterator start, RandomAccessIterator end, LessThan &lessThan) {
  // Adicione el código de Merge Sort.
}

template <typename RandomAccessIterator, typename LessThan>
inline void LomutoQuickSort(RandomAccessIterator start, RandomAccessIterator end, LessThan &lessThan) {
  // Adicione el código de Quick Sort de Lomuto.
}

template <typename RandomAccessIterator, typename LessThan>
inline void HoareQuickSort(RandomAccessIterator start, RandomAccessIterator end, LessThan &lessThan) {
  // Adicione el código de Quick Sort de Hoare.
}

template <typename RandomAccessIterator, typename LessThan>
inline void YaroslavskiyQuickSort(RandomAccessIterator start, RandomAccessIterator end, LessThan &lessThan) {
  // Adicione el código de Quick Sort con doble pivot y corte a insertion sort con pocos elementos.
}

/**
FUNCION MAIN DEL CODIGO
**/

int main(int argc, char** argv) {

  typedef void (*SORT_ALGORITHM)(std::vector<int>::iterator, std::vector<int>::iterator);

  for ( auto & i : {100,1000,10000,100000,1000000,10000000,100000000}){

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
    std::vector<SORT_ALGORITHM> sort_algorithms = {InsertSort,  SelectSort, StableSelectSort, HeapSort, MergeSort, IterativeMergeSort, LomutoQuickSort, HoareQuickSort };

    if ( i > 100000 && i < 100000000)
    {
      sort_algorithms = {HeapSort, MergeSort, IterativeMergeSort, LomutoQuickSort, HoareQuickSort };
      std::cout << "-, -, -, ";
    }

    if (i == 100000000)
    {
      sort_algorithms = {IterativeMergeSort, LomutoQuickSort, HoareQuickSort };
      std::cout << "-, -, -, -, -, ";
    }

    for ( auto & sort_algorithm : sort_algorithms){
      v = w;
      std::clock_t inicio = std::clock();
      sort_algorithm(v.begin(),v.end());
      std::cout << 1000.0 * (double)(std::clock()-inicio)/(double)CLOCKS_PER_SEC << ", " << std::flush;
    }

    std::cout << std::endl;
  }
  return 0;
} // FIN DEL MAIN
