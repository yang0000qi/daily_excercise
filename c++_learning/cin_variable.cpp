#include <iostream>

using namespace std;

int main()
{
    int sum = 0, value = 0;
    int cnt;
    while(cin >> value)
    {
        sum += value;
        cnt++;
        cout << "The " << cnt << "st has cin : " << value << endl;
    }

    cout << "sum = " << sum << endl;

    return 0;
}