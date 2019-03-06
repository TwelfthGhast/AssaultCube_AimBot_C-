#include <iostream>
#include <Windows.h>
#include <tlhelp32.h>
#include <vector>

using namespace std;

struct AC_player
{
	char pad_0x0000[0x4]; //0x0000
	std::vector<float> N0000069A;
    std::vector<float> N0000069D;
	char pad_0x001C[0xC]; //0x001C
	std::vector<float> N000006A3;
	std::vector<float> N000006A6;
	std::vector<float> N000006A9;
	char pad_0x0048[0x29]; //0x004C
	float N000006B7; //0x0078  Position of head at start of last jump
	char pad_0x007C[0x7C]; //0x007C
	int N0000071E; //0x00F8 Health
	int N0000071F; //0x00FC Armor
	char pad_0x0100[0xC]; //0x0100
	int N00000723; //0x010C Boolean? Is Dual MK-77 Pistols allowed/equipped...
	char pad_0x0110[0x4]; //0x0110
	int N00000725; //0x0114 MK-77 Pistol Ammo (Unchambered)
	int N00000726; //0x0118 TMP-M&A Carbine Ammo (Unchambered)
	int N00000727; //0x011C V-19 Combat Shotgun Ammo (Unchambered)
	int N00000728; //0x0120 A-ARD/10 Submachine Gun Ammo (Unchambered)
	int N00000729; //0x0124 Precision Tech AD-81 Sniper Rifle Ammo (Unchambered)
	int N0000072A; //0x0128 MTP-57 Assault Rifle Ammo (Unchambered)
	char pad_0x012C[0x8]; //0x012C
	int N00000799; //0x0134 Dual MK-77 Pistol Ammo (Unchambered)
	char pad_0x0138[0x4]; //0x0138
	int N0000072E; //0x013C MK-77 Pistol Ammo (Chambered)
	int N00000733; //0x0140 TMP-M&A Carbine Ammo (Chambered)
	int N00000734; //0x0144 V-19 Combat Shotgun Ammo (Chambered)
	int N00000735; //0x0148 A-ARD/10 Submachine Gun Ammo (Chambered)
	int N00000736; //0x014C Precision Tech AD-81 Sniper Rifle Ammo (Chambered)
	int N00000738; //0x0150 MTP-57 Assault Rifle Ammo (Chambered)
	char pad_0x0154[0x4]; //0x0154
	int N0000073B; //0x0158 Number of Grenades
	int N0000073C; //0x015C Dual MK-77 Pistol Ammo (Chambered)
	int N0000073D; //0x0160 Knife Delay
	int N0000073E; //0x0164 MK-77 Pistol Delay
	int N0000073F; //0x0168 TMP-M&A Carbine Delay
	int N00000740; //0x016C V-19 Combat Shotgun Delay
	int N00000741; //0x0170 A-ARD/10 Submachine Gun Delay
	int N00000742; //0x0174 Precision Tech AD-81 Sniper Rifle Delay
	int N00000743; //0x0178 MTP-57 Assault Rifle Delay
	char pad_0x017C[0x4]; //0x017C
	int N00000745; //0x0180 Grenade Delay
	int N000007F3; //0x0184 Dual MK-77 Pistol Delay
	int N00000747; //0x0188 Times knife has been swung
	int N00000748; //0x018C Times MK-77 Pistol has been shot
	int N00000749; //0x0190 Times TMP-M&A Carbine has been shot
	int N0000074A; //0x0194 Times V-19 Combat Shotgun has been shot
	int N0000074B; //0x0198 Times A-ARD/10 Submachine Gun has been shot
	int N0000074C; //0x019C Times Precision Tech AD-81 Sniper Rifle has been shot
	int N0000074D; //0x01A0 Times MTP-57 Assault Rifle Ammo has been shot
	char pad_0x01A4[0x4]; //0x01A4
	int N0000074F; //0x01A8 Times Grenade has been thrown
	int N00000750; //0x01AC Times Dual MK-77 Pistol has been shot
	char pad_0x01B0[0x48]; //0x01B0
	int N00000763; //0x01F8 Number of times Respawned
	int N00000764; //0x01FC Number of Kills
	char pad_0x0200[0x4]; //0x0200
	int N00000766; //0x0204 Number of Deaths
	char pad_0x0208[0x8]; //0x0208
	int N0000076B; //0x0210 Some sort of pointer to damage dealt?
	char pad_0x0214[0x4]; //0x0214
	int N0000076D; //0x0218 Some sort of pointer to damage taken?
	char pad_0x021C[0x110]; //0x021C
	int N000007D7; //0x032C Player Team
	char pad_0x0330[0x8]; //0x0330
	int N000007DA; //0x0338 Boolean; 1 = dead, 0 = alive
	char pad_0x033C[0xC4]; //0x033C

}; //Size=0x0400

class bypass{
    int processID;
public:
    //Get ID of a process given its name
    int get_procID(const char target[]){
        cout << "Function: get_procID called." << endl;
        processID = 0;
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
        }
        cout << "Function: get_procID resolved." << endl;
    }

    //Attach to a running process
    HANDLE hook(DWORD access){
        cout << "Function: hook called." << endl;
        HANDLE processHandle = OpenProcess(
            access,    //Permission level you are seeking
            FALSE,     //Do child processes inherit permissions?
            processID  //ProcessID you are hooking into
        );
        if(processHandle == NULL){
            cout << GetLastError() << endl;
            exit(1);
        } else {
            return processHandle;
            cout << "Function: hook resolved." << endl;
        }
    }

    //Detach from a running process
    void unhook(HANDLE processHandle){
        cout << "Function: unhook called." << endl;
        cout << "HANDLE: " << processHandle << endl;
        int result = CloseHandle(processHandle);
        if(result == 0){
            cout << GetLastError() << endl;
            exit(1);
        } else {
            cout << "Function: unhook resolved." << endl;
        }
    }

    int readInt(int readIntAddress, HANDLE processHandle){
        int temp;
        bool result = ReadProcessMemory(
            processHandle,
            (LPCVOID)readIntAddress,     //Address we are trying to hook. Change to address of varInt
            &temp,             //Buffer we are writing to
            sizeof(int),        //Size of things we are reading
            NULL
        );
        if(result==0){
            cout << "An error occurred with function: readInt - " << GetLastError() << endl;
        } else {
            return temp;
            cout << "Function: readInt resolved." << endl;
        }
    }

    void readPlayer(unsigned char* outstr, int playerAddress, HANDLE processHandle){
        cout << "Function: readPlayer called." << endl;
        bool result = ReadProcessMemory(
            processHandle,
            (LPCVOID)playerAddress,                //Address we are trying to hook. Change to address of varInt
            outstr,                        //Buffer we are writing to
            sizeof(AC_player),                     //Size of things we are reading
            NULL
        );
        if(result==0){
            cout << "An error occurred with function: readPlayer - " << GetLastError() << endl;
        } else {
            cout << "Function: readPlayer resolved." << endl;
        }
    }
};


int main(void){
    bypass AC_bypass;
    AC_bypass.get_procID("ac_client.exe");
    AC_player player;
    cout << sizeof(AC_player) << endl;
    HANDLE hProcess = AC_bypass.hook(PROCESS_VM_READ);
    int ptrToPlayer = 0x00509B74;
    int dr_playerAddress = AC_bypass.readInt(ptrToPlayer, hProcess);
    cout << hex << uintptr_t(dr_playerAddress) << endl;
    unsigned char player_data[sizeof(AC_player)];
    while(1){
        //get 1024 chars starting from derefenced address containing player struct;
        AC_bypass.readPlayer(player_data, dr_playerAddress, hProcess);
        //Copy char/byte array in order to populate our player structure
        memcpy(&player, player_data, sizeof(AC_player));
        cout << dec << player.N00000735 << endl;
        Sleep(1);
    }
    AC_bypass.unhook(hProcess);
    return 0;
}
