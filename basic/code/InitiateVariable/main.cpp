#include <iostream>

using namespace std;
void doNothing(int&)
{

}
int main()
{
    cout << "Hello world!" << endl;
    int x;
    // make the compiler think we're assigning a value to this variable
    doNothing(x);
    // who knows what we'll get, because x is uninitialized
    std::cout<<x;
    return 0;
}
