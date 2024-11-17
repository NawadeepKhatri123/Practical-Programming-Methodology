
#include <iostream>
#include <vector>
#include <string>
#include <functional>

// Define the template types
template <class T>
using ELEM = std::vector<T>;

template <class T>
using VEC = std::vector<ELEM<T>>;

template <class T>
using action_t = T (*)(int);

template <class T>
using pred_t = bool (*)(T);

template <class T>
using map_t = T (*)(T, T);

// Function prototypes
template <class T>
void printElem(ELEM<T> &v);

template <class T>
void initVec(VEC<T> &v, ELEM<T> &&cons);

template <class T>
void printVec(VEC<T> &v);

template <class T>
VEC<T> generate(int N, action_t<T> f);

template <class T>
VEC<T> zip(VEC<T> &v, VEC<T> &w);

template <class T>
VEC<T> filter(VEC<T> &v, pred_t<T> f);

template <class T>
VEC<T> map(VEC<T> &v, action_t<T> f);

template <class T>
ELEM<T> reduce(VEC<T> &v, map_t<T> f, ELEM<T> ident);

// Function implementations
template <class T>
void printElem(ELEM<T> &v) {
    for (const T &elem : v) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

template <class T>
void initVec(VEC<T> &v, ELEM<T> &&cons) {
    v.push_back(std::move(cons));
}

template <class T>
void printVec(VEC<T> &v) {
    for (auto &elem : v) {
        printElem(elem);
    }
}

template <class T>
VEC<T> generate(int N, action_t<T> f) {
    VEC<T> vec;
    for (int i = 0; i < N; ++i) {
        ELEM<T> elem;
        elem.push_back(f(i));
        vec.push_back(std::move(elem));
    }
    return vec;
}

template <class T>
VEC<T> zip(VEC<T> &v, VEC<T> &w) {
    VEC<T> result;
    size_t minSize = std::min(v.size(), w.size());
    for (size_t i = 0; i < minSize; ++i) {
        ELEM<T> elem;
        elem.insert(elem.end(), v[i].begin(), v[i].end());
        elem.insert(elem.end(), w[i].begin(), w[i].end());
        result.push_back(std::move(elem));
    }
    return result;
}

template <class T>
VEC<T> filter(VEC<T> &v, pred_t<T> f) {
    VEC<T> result;
    for (auto &elem : v) {
        ELEM<T> filteredElem;
        for (auto &value : elem) {
            if (f(value)) {
                filteredElem.push_back(value);
            }
        }
        if (!filteredElem.empty()) {
            result.push_back(std::move(filteredElem));
        }
    }
    return result;
}

template <class T>
VEC<T> map(VEC<T> &v, action_t<T> f) {
    VEC<T> result;
    for (auto &elem : v) {
        ELEM<T> transformedElem;
        for (auto &value : elem) {
            transformedElem.push_back(f(value));
        }
        result.push_back(std::move(transformedElem));
    }
    return result;
}

template <class T>
ELEM<T> reduce(VEC<T> &v, map_t<T> f, ELEM<T> ident) {
    for (auto &elem : v) {
        for (auto &value : elem) {
            ident[0] = f(ident[0], value);
        }
    }
    return ident;
}

// Main program
int main() {
    VEC<int> v;
    initVec(v, ELEM<int>{1, 2, 3, 4});

    VEC<int> w;
    initVec(w, ELEM<int>{-1, 3, -3, 4});
    printVec(v);
    printVec(w);

    std::cout << std::string(10, '*') << std::endl;

    VEC<int> z = zip(v, w);
    printVec(z);

    std::cout << std::string(10, '*') << std::endl;

    VEC<int> x = zip(z, z);
    printVec(x);

    std::cout << std::string(10, '*') << std::endl;

    VEC<int> a = generate(10, [](int x) { return x * x; }); // Function to generate squares
    printVec(a);

    VEC<int> y = filter(w, [](int x) { return x > 0; }); // Filter positive values
    printVec(y);

    VEC<int> u = map(w, [](int x) { return x > 0 ? 1 : 0; }); // Map to 1 if positive, 0 otherwise
    printVec(u);

    ELEM<int> e = reduce(u, [](int x, int y) { return x + y; }, ELEM<int>{0}); // Reduce to sum
    printElem(e);

    std::cout << std::endl << std::string(10, '$') << std::endl;

    VEC<std::string> ws;
    initVec(ws, ELEM<std::string>{"hello", "there", "franco", "carlacci"});
    printVec(ws);

    ELEM<std::string> es = reduce(ws, [](std::string a, std::string b) { return a + " " + b; }, ELEM<std::string>{""});
    printElem(es);

    VEC<char> wc;
    initVec(wc, ELEM<char>{'a', 'b', 'c', 'd'});

    std::cout << std::endl << std::string(10, '$') << std::endl;
    printVec(wc);

    ELEM<char> ec = reduce(wc, [](char a, char b) { return a > b ? a : b; }, ELEM<char>{' '}); // Reduce to max char
    std::cout << std::endl << std::string(10, '$') << std::endl;
    printElem(ec);

    return 0;
}

