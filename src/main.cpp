#include <iostream>
#include <cmath>
#include "./multiset.h"

using nonstd::MultiSet;
int main(){
   srand(time(NULL));
   MultiSet<int> test;

   std::cout << test.size() << std::endl;
   int toCountFor = 1;
   test.insert(1);
   test.insert(0);
   std::cout << test.size() << std::endl;


/*   int myCounter = 0;

   
   for(int k = 0; k < 1000; k++)
   {
      int temp = rand() % 101;
      test.insert(temp);
      if(toCountFor == temp)
         myCounter++;
   }*/
   test.remove(toCountFor);
   std::cout << "Size: " << test.size() << std::endl;
   std::cout << "Count for: " << toCountFor << std::endl;
   std::cout << "Counted: " << test.count(toCountFor) << std::endl;
   std::cout << "Removed: " << test.remove(toCountFor) << std::endl;
   std::cout << "Removed again: " << test.remove(toCountFor) << std::endl;
   std::cout << "New Size: " << test.size() << std::endl;
   return 0;
}

