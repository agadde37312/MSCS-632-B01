// C++: Demonstrating Static Typing and Scope

#include <iostream>
using namespace std;

string var1 = "I'm global";

void outerFunction() {
    string var2 = "I'm in outside function";

    {
        string var3 = "I'm in inside block";
        cout << var3 << endl;  // Accessible
        cout << var2 << endl;  // Accessible
        cout << var1 << endl; // Accessible
    }

     //cout << var2 << endl;  // Error: var2 is not accessible here due to block scope
}

int main() {
    outerFunction();
    return 0;
}
