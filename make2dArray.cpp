
/*
  Author:Irvin Samuel
  Date: April 22, 2019
  Purpose: to Populate a 2d pointer with a certain datatype
*/

#include <iostream>
#include "make2dArray.h"

using namespace std;

int main()
{
   int **a;
   // make a 2 x 2 array
   make2dArray(a,2,2);

   // assign values to all elements of the array
   a[0][0] = 1; a[0][1] = 2; a[1][0] = 3; a[1][1] = 4;

   // output assigned values
   cout << a[0][0] << ' ' << a[0][1] << endl;
   cout << a[1][0] << ' ' << a[1][1] << endl;
   return 0;
}
