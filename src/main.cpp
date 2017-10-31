#include <iostream>
#include <cmath>
#include "./multiset.h"

using nonstd::MultiSet;
int main(){
   srand(time(NULL));

   int toCountFor = rand() % 101;
   int myCounter = 0;

   MultiSet<int> test;
   for(int k = 0; k < 1000; k++)
   {
      int temp = rand() % 101;
      test.insert(temp);
      if(toCountFor == temp)
         myCounter++;
   }

   std::cout << "Size: " << test.size() << std::endl;
   std::cout << "Count for: " << toCountFor << std::endl;
   std::cout << "Counted: " << myCounter << std::endl;
   std::cout << "Removed: " << test.remove(toCountFor) << std::endl;
   std::cout << "Removed again: " << test.remove(toCountFor) << std::endl;
   std::cout << "New Size: " << test.size() << std::endl;
   return 0;
}

