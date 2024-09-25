#include <iostream>

int main(){
      double x{};    // creates a double variable x
      double y{};    // creates a double variable y

      std::cout << "ENTER A DOUBLE VALUE FOR X : ";
      std::cin >> x;                                    // new input for x
      std::cout << "ENTER A DOUBLE VALUE FOR Y : ";
      std::cin >> y;                                    //new input for y

      double* ptr1 = &x;                              // ptr1 points at x
      double* ptr2 = &y;                              // ptr2 points at y

      std::cout<<" x is "<<x<<" and y is "<< y <<"and the sum is "<<*ptr1+*ptr2<<std::endl;
      // so the contents inside the addresses that ptr1 & ptr2 is summed and printed.

      return 0;
}