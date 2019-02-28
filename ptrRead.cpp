#include <iostream>
#include <Windows.h>
#include <tlhelp32.h>

using namespace std;

int get_procID(const char target[]){
    cout << "Function: get_procID called." << endl;
    int processID = 0;
    //Create a snapshot of currently running processes
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if(snap==INVALID_HANDLE_VALUE){
        cout << GetLastError() << endl;
        exit(1);
    }

    PROCESSENTRY32 pe32;
    // Set the size of the structure before using it.
    pe32.dwSize = sizeof(PROCESSENTRY32);

    // Retrieve information about the first process and exit if unsuccessful
    if(!Process32First(snap, &pe32) )
    {
        cout << GetLastError() << endl;
        CloseHandle(snap);          // clean the snapshot object
        exit(1);
    }

    //Cycle through Process List
    do {
        //Uncomment below to show all running processes
        //printf("%s\t\t\t%d\n",pe32.szExeFile,pe32.th32ProcessID);
        if(strcmp(pe32.szExeFile, target)==0) {
            processID = pe32.th32ProcessID;
        }
    } while (Process32Next(snap, &pe32));

    if(processID == 0){
        cout << "Process not found. Exiting..." << endl;
        exit(1);
    } else {
        return processID;
        cout << "Function: get_procID resolved." << endl;
    }
}

HANDLE hook(DWORD access, int hook_processID){
    cout << "Function: hook called." << endl;
    HANDLE processHandle = OpenProcess(
        access,    //Permission level you are seeking
        FALSE,     //Do child processes inherit permissions?
        hook_processID  //ProcessID you are hooking into
    );
    if(processHandle == NULL){
        cout << GetLastError() << endl;
        exit(1);
    }
    cout << "HANDLE: " << processHandle << endl;
    return processHandle;
    cout << "Function: hook resolved." << endl;
}

int main(void){
    int pid = get_procID("dummy.exe");
    cout << pid << endl;
    HANDLE hProcess = hook(PROCESS_VM_READ, pid);
    int temp;
    ReadProcessMemory(
        hProcess,
        (LPCVOID)0x6DFE4C,     //Address we are trying to hook. Change to address of varInt
        &temp,             //Buffer we are writing to
        sizeof(int),        //Size of things we are reading
        NULL
    );
    cout << hex << uintptr_t(temp) << endl;
    cout << (LPCVOID)temp << endl;
    ReadProcessMemory(
        hProcess,
        (LPCVOID)temp,     //Address we are trying to hook. Change to address of varInt
        &temp,             //Buffer we are writing to
        sizeof(int),        //Size of things we are reading
        NULL
    );
    cout << dec << temp << endl;
    return 0;
}
