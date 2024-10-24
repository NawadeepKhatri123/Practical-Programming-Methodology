#include <iostream>


template <class T>
using ELEM = std::vector<T>;

template <class T>
using VEC = std::vector<ELEM<T>>;

template <class T>
using action_t = T (*) (int);

template <class T>
using pred_t = bool (*) (T);

template <class T>
using map_t = T (*) (T,T);

int main(){
    template <class T>
    void printElem(ELEM<T> &v)

    template <class T>
    void initVec(VEC<T> &v, ELEM<T> &&cons)

    template <class T>
    void printVec(VEC<T> &v)

    template <class T>
    VEC<T> generate(int N, action_t<T> f)

    template<class T>
    VEC<T> zip(VEC<T> &v,VEC<T> &w )

    template<class T>
    VEC<T> filter(VEC<T> &v, pred_t<T> f)

    template<class T>
    VEC<T> map(VEC<T> &v, action_t<T> f) 

    template<class T>
    ELEM<T> reduce( VEC<T> &v, map_t<T> f, ELEM<T> ident)

}

template <class T>
using action_t = T (*) (T,T);

