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
using action_t = std::function<T(int)>;

template <class T>
using pred_t = std::function<bool(T)>;

template <class T>
using map_t = std::function<T(T, T)>;

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
    // Initialize two vectors of integers
    VEC<int> v;
    initVec(v, ELEM<int>{1, 2, 3, 4});

    VEC<int> w;
    initVec(w, ELEM<int>{-1, 3, -3, 4});

    std::cout << "Initial Vectors:" << std::endl;
    printVec(v);
    printVec(w);

    std::cout << std::string(10, '*') << std::endl;

    // Zip v and w
    VEC<int> z = zip(v, w);
    printVec(z);

    std::cout << std::string(10, '*') << std::endl;

    // Zip z with itself
    VEC<int> x = zip(z, z);
    printVec(x);

    std::cout << std::string(10, '*') << std::endl;

    // Generate squares of numbers from 0 to 9
    VEC<int> a = generate(10, [](int x) { return x * x; });
    printVec(a);

    // Filter out non-positive numbers from w
    VEC<int> y = filter(w, [](int x) { return x > 0; });
    printVec(y);

    // Map positive numbers in w to 1 and others to 0
    VEC<int> u = map(w, [](int x) { return x > 0 ? 1 : 0; });
    printVec(u);

    // Reduce u to sum of elements
    ELEM<int> e = reduce(u, [](int x, int y) { return x + y; }, ELEM<int>{0});
    printElem(e);

    std::cout << std::endl << std::string(10, '$') << std::endl;

    // Initialize vector of strings
    VEC<std::string> ws;
    initVec(ws, ELEM<std::string>{"hello", "there", "franco", "carlacci"});
    printVec(ws);

    // Reduce strings to a single string
    ELEM<std::string> es = reduce(ws, [](std::string a, std::string b) { return a + " " + b; }, ELEM<std::string>{""});
    printElem(es);

    // Initialize vector of characters
    VEC<char> wc;
    initVec(wc, ELEM<char>{'a', 'b', 'c', 'd'});

    std::cout << std::endl << std::string(10, '$') << std::endl;
    printVec(wc);

    // Reduce characters to the maximum character
    ELEM<char> ec = reduce(wc, [](char a, char b) { return a > b ? a : b; }, ELEM<char>{' '});
    std::cout << std::endl << std::string(10, '$') << std::endl;
    printElem(ec);

    return 0;
}

