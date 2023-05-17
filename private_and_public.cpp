#include <bits/stdc++.h>
#include <iostream>
using namespace std;

class obj {
private:
    int a = 2;

public:
    int b = 1;
};

int main()
{
    obj* o = new obj();
    cout << o->b << endl;
}