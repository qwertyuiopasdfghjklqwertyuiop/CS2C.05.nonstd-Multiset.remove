#include <iostream>
#include <cmath>
#include "./multiset.h"

using nonstd::MultiSet;
int main(const int argc, char ** argv){
/*   MultiSet<int> test;
   test.insert(8);
   test.insert(10);
   test.insert(9);
   test.insert(12);


   test.remove(10);*/

   if(argc != 3)
   {
      std::cerr << "./main BIGGEST_NUMBER NUM_INSERTIONS" << std::endl;
      exit(1);
   }

   srand(time(NULL));
   MultiSet<int> test;

   const int BIGGEST_NUMBER = std::stoi(*(argv+1));
   const int NUM_INSERTIONS = std::stoi(*(argv+2));
   int myCounter = 0;
   int toCountFor = rand() % BIGGEST_NUMBER;

   
   for(int k = 0; k < NUM_INSERTIONS; k++)
   {
      int temp = rand() % BIGGEST_NUMBER;
      test.insert(temp);
      if(toCountFor == temp)
         myCounter++;
   }
   
   std::cout << "Size: " << test.size() << std::endl;
   std::cout << "Count for: " << toCountFor << std::endl;
   std::cout << "Counted: " << test.count(toCountFor) << std::endl;
   std::cout << "Removed: " << test.remove(toCountFor) << std::endl;
   std::cout << "Removed again: " << test.remove(toCountFor) << std::endl;
   std::cout << "New Size: " << test.size() << std::endl;
   return 0;
}

