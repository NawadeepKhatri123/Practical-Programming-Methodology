#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// Template Type Aliases
template <class T>
using ELEM = std::vector<T>;

template <class T>
using VEC = std::vector<ELEM<T>>;

template <class T>
using action_t = T(*)(int);

template <class T>
using pred_t = bool(*)(T);

template <class T>
using map_t = T(*)(T, T);

// Function to print an ELEM<T>
template <class T>
void printElem(ELEM<T>& v) {
    std::cout << "[";
    for (size_t i = 0; i < v.size(); ++i) {
        std::cout << v[i];
        if (i < v.size() - 1) std::cout << " , ";
    }
    std::cout << "]";
}

// Function to initialize a VEC<T>
template <class T>
void initVec(VEC<T>& v, ELEM<T>&& cons) {
    v.push_back(cons);
}

// Function to print a VEC<T>
template <class T>
void printVec(VEC<T>& v) {
    std::cout << "[";
    for (size_t i = 0; i < v.size(); ++i) {
        if (v[i].size() == 1) {
            // If the ELEM<T> has only one element, print it directly
            std::cout << v[i][0];
        } else {
            // Otherwise, print the ELEM<T> as a group with parentheses
            std::cout << "(";
            for (size_t j = 0; j < v[i].size(); ++j) {
                std::cout << v[i][j];
                if (j < v[i].size() - 1) std::cout << " ";
            }
            std::cout << ")";
        }
        if (i < v.size() - 1) std::cout << " , ";
    }
    std::cout << "]" << std::endl; // End after printing VEC<T>
}

// Function to generate a VEC<T> based on an action_t<T>
template <class T>
VEC<T> generate(int N, action_t<T> f) {
    VEC<T> result;
    for (int i = 0; i < N; ++i) {
        result.push_back(ELEM<T>{f(i)});
    }
    return result;
}

// Function to zip two VEC<T> objects
template <class T>
VEC<T> zip(VEC<T>& v, VEC<T>& w) {
    VEC<T> result;
    size_t size = std::min(v.size(), w.size());
    for (size_t i = 0; i < size; ++i) {
        ELEM<T> elem;
        elem.insert(elem.end(), v[i].begin(), v[i].end());
        elem.insert(elem.end(), w[i].begin(), w[i].end());
        result.push_back(elem);
    }
    return result;
}

// Function to filter a VEC<T> based on a pred_t<T>
template <class T>
VEC<T> filter(VEC<T>& v, pred_t<T> f) {
    VEC<T> result;
    for (auto& elem : v) {
        if (elem.size() == 1 && f(elem[0])) {
            result.push_back(elem);
        }
    }
    return result;
}

// Function to map a VEC<T> using an action_t<T>
template <class T>
VEC<T> map(VEC<T>& v, action_t<T> f) {
    VEC<T> result;
    for (auto& elem : v) {
        ELEM<T> newElem;
        for (auto& val : elem) {
            newElem.push_back(f(val));
        }
        result.push_back(newElem);
    }
    return result;
}

// Function to reduce a VEC<T> into an ELEM<T>
template <class T>
ELEM<T> reduce(VEC<T>& v, map_t<T> f, ELEM<T> ident) {
    ELEM<T> result = ident;
    for (auto& elem : v) {
        for (auto& val : elem) {
            if (result.empty()) {
                result.push_back(val);
            } else {
                result[0] = f(result[0], val);
            }
        }
    }
    return result;
}

// Test Functions
int f(int x) { return x * x; }                    // Squares a number
bool g(int x) { return x > 0; }                   // Returns true if > 0
int h(int x) { return x % 2; }                    // Returns 0 or 1
int k(int x, int y) { return x + y; }             // Adds two numbers
std::string k(std::string x, std::string y) { return x + y; } // Concatenates strings
char k(char x, char y) { return x; }              // Returns first char

int main() {
    VEC<int> v;
    initVec(v, ELEM<int>{1, 2, 3, 4});
    VEC<int> w;
    initVec(w, ELEM<int>{-1, 3, -3, 4});
    printVec(v);
    std::cout << std::string(10, '*') << std::endl;
    printVec(w);
    std::cout << std::string(10, '*') << std::endl;

    VEC<int> z = zip(v, w);
    printVec(z);
    std::cout << std::string(10, '*') << std::endl;

    VEC<int> x = zip(z, z);
    printVec(x);
    std::cout << std::string(10, '*') << std::endl;

    VEC<int> a = generate(10, f);
    printVec(a);

    VEC<int> y = filter(w, g);
    printVec(y);

    VEC<int> u = map(w, h);
    printVec(u);

    ELEM<int> e = reduce(u, k, ELEM<int>{0});
    printElem(e);

    std::cout << std::endl << std::string(10, '$') << std::endl;

    VEC<std::string> ws;
    initVec(ws, ELEM<std::string>{"hello", "there", "franco", "carlacci"});
    printVec(ws);
    ELEM<std::string> es = reduce(ws, k, ELEM<std::string>{""});
    printElem(es);

    VEC<char> wc;
    initVec(wc, ELEM<char>{'a', 'b', 'c', 'd'});
    std::cout << std::endl << std::string(10, '$') << std::endl;
    printVec(wc);
    ELEM<char> ec = reduce(wc, k, ELEM<char>{' '});
    std::cout << std::endl << std::string(10, '$') << std::endl;
    printElem(ec);

    return 0;
}

