#include <iostream>

using namespace std;

/*=============FUNCTION OBJECTS ========*/
template<class T>
struct CLess{
   inline bool operator()(T a, T b){return a < b;}
};

template<class T>
struct CGreater{
   inline bool operator()(T a, T b){return a > b;}
};

/*============BINARY TREE NODE ==*/
template<class T>
struct CBNode{
    T mData;
    CBNode<T> *mSon[2];
    CBNode(T x):mData(x){};
};

/*============BINARY TREE ==*/
template<class T> class CBTreeIterator;

template<class T, class C>
class CBTree{
    friend CBTreeIterator<T>;

    typedef CBNode<T>* pNode;
    typedef CBNode<T> Node;
    typedef CBTreeIterator<T> iterator;

    pNode mRoot;
    C mCompFunctor;

public:
    CBTree():mRoot(nullptr){};
    bool buscar(T x, pNode* &p);
    bool insertar(T x);
    bool remover(T x);
    void inorderPrint(const pNode &root);

    pNode* reemplazar(const pNode* p);
    pNode getRoot(){return mRoot;}

    iterator begin(){

    }
};

template<class T>
class CBTreeIterator{

};
/*=======================================*/
/**=======================================**/
/**=======================================**/

int main(){
    CBTree<int,CLess<int>> A;
    A.insertar(4);
    A.insertar(5);
    A.insertar(3);
    A.insertar(7);
    CBNode<int>*p = A.getRoot();
    A.inorderPrint(p); cout << endl;
    A.remover(5);
    A.remover(4);
    A.inorderPrint(p);

} // fin del main

/**=======================================**/
/**=======================================**/
template<class T, class C>
bool CBTree<T,C>::buscar(T x, pNode * &p){
    /*
    p = &mRoot;
    while(*p && (*p)->mData != x){
        p = &((*p)->mSon[mCompFunctor((*p)->mData,x)]);
    }*/
    // Otra opción de codigo
    for(p = &mRoot; *p && (*p)->mData != x; p = &((*p)->mSon[mCompFunctor(x,(*p)->mData)]));
    //return *p != nullptr;
    return !!*p;
    //return (bool)*p;
}
/*=======================================*/
template<class T, class C>
bool CBTree<T,C>::insertar(T x){
    pNode *p;
    if(buscar(x,p)) return 0;
    *p = new Node(x);
    return 1;
}
/*=======================================*/
template<class T, class C>
bool CBTree<T,C>::remover(T x){
    pNode *p;
    if(!buscar(x,p)) return 0 ; // No se pudo borrar el elemento por q no esta en el arbol
    if((*p)->mSon[0] && (*p)->mSon[1]){
        pNode *q = reemplazar(p); // buscar al menor de los mayores y devuelve un puntero al puntero
        (*p)->mData = (*q)->mData;
        p = q; // asignamos el valor de q a p, cambiamos el puntero a puntero
    }
    pNode tmp = *p; //guardamos temporalmente el puntero al nodo q se va a eliminar
    *p = (*p)->mSon[!(*p)->mSon[0]]; // modificamos el puntero que va al nodo a eliminar y copiamos el  hijo derecho
    delete tmp; return 1; // operacion de eliminacion exitosa
}
/*=======================================*/
template<class T, class C>
CBNode<T>** CBTree<T,C>::reemplazar(const pNode* p){
    pNode * q = &((*p)->mSon[1]);
    while((*q)->mSon[0]) q = &((*q)->mSon[0]);
    return q;
}

/*=======================================*/
template<class T, class C>
void CBTree<T,C>::inorderPrint(const pNode &p){
    if(!p) return;
    inorderPrint(p->mSon[0]);
    cout << p->mData;
    inorderPrint(p->mSon[1]);
}
/*=======================================*/

