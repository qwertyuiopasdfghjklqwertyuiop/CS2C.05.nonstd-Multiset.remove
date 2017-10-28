#include <iostream>
#include <cmath>
#include "./multiset.h"

using nonstd::MultiSet;
int main(){
   int toCountFor = rand() % 10;
   int myCounter = 0;

   srand(time(NULL));
   MultiSet<int> test;
   for(int k = 0; k < 10; k++)
   {
      int temp = rand() % 10;
      test.insert(temp);
      if(toCountFor == temp)
         myCounter++;
   }

   std::cout << myCounter << std::endl;
   std::cout << test.count(toCountFor) << std::endl;
   std::cout << test.size() << std::endl;
   return 0;
}

