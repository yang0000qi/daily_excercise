#include <iostream>
#include <string.h>

using namespace std;

int main()
{
    int str[10];
    int len = sizeof(str) / sizeof(int);
    int sum = 0;

    cerr << "length (str[10]) = " << len << endl;
    for(int i=0; i< len; i++)
    {
        str[i] = i;
    }

    for(int i=0; i< len; i++)
    {
        sum += str[i];
    }

    clog << "sum = " << sum <<endl;

}