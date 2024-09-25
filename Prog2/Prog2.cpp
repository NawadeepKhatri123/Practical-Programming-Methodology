#include <iostream>

int main(){
      double x{};
      double y{};

      std::cout << "ENTER A DOUBLE VALUE FOR X : ";
      std::cin >> x;
      std::cout << "ENTER A DOUBLE VALUE FOR Y : ";
      std::cin >> y;

      double* ptr1 = &x;
      double* ptr2 = &y;

      std::cout<<" x is "<<x<<" and y is "<<y<<"and the sum is "<<*ptr1+*ptr2<<std::endl;

}