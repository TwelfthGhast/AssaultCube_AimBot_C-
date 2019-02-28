#include <iostream>
#include <Windows.h>

using namespace std;

int main(void){

    int varInt = 123456;
    string varString = "DefaultString";
    char arrChar[128] = "Long char right there ->";
    int *ptr2int;
    ptr2int = &varInt;
    int **ptr2ptr;
    ptr2ptr = &ptr2int;
    int ***ptr2ptr2;
    ptr2ptr2 = &ptr2ptr;

    while(1){
        cout << "Process ID: " << dec << GetCurrentProcessId() << "\n" << endl;

        cout << "varInt\t\t0x" << hex << uppercase << uintptr_t(&varInt) << " = " << dec << varInt << endl;
        cout << "varString\t0x" << hex << uppercase << uintptr_t(&varString) << " = " << varString << endl;
        cout << "arrChar\t\t0x" << hex << uppercase << uintptr_t(&arrChar) << " = " << arrChar << endl;
        cout << "ptr2int\t\t0x" << hex << uppercase << uintptr_t(&ptr2int) << " = 0x" << uintptr_t(ptr2int) << endl;
        cout << "ptr2ptr\t\t0x" << hex << uppercase << uintptr_t(&ptr2ptr) << " = 0x" << uintptr_t(ptr2ptr) << endl;
        cout << "ptr2ptr2\t0x" << hex << uppercase << uintptr_t(&ptr2ptr2) << " = 0x" << uintptr_t(ptr2ptr2) << endl;

        cout << "\n" << "------------------------------" << endl;

        cout << "Press ENTER to print again.";
        cin.get();
        Sleep(500);
        cout << "------------------------------" << endl;
        Sleep(500);

    }
    return 0;
}

