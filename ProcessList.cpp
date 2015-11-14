#include "StdAfx.h"

namespace Sembly
{
    std::vector<DWORD> ProcessList::GetByName(const char* processName)
    {
        DWORD dwProcessList[4096] = { 0 };
        DWORD dwBytesReturned = 0;

        std::vector<DWORD> processList;

        // get a list to all active processes
        EnumProcesses(dwProcessList, sizeof(dwProcessList), &dwBytesReturned);

        // loop through the received list and check the name of the process
        DWORD numProcesses = dwBytesReturned / sizeof(DWORD);
        for (unsigned int i = 0; i < numProcesses; i++)
        {
            if (dwProcessList[i] == 0)
                continue;

            if (IsSearchingProcess(dwProcessList[i], processName))
            {
                LOG_INFO_EX(LogMessage::Process::Found, dwProcessList[i]);
                processList.push_back(dwProcessList[i]);
            }
        }

        return (processList);
    }

    bool ProcessList::IsSearchingProcess(DWORD processID, const char* processName)
    {
        TCHAR szProcessModuleName[MAX_PATH] = TEXT("<none>");

        // Get a handle to the process
        HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID);
        if (hProcess == nullptr)
        {
            LOG_WARNING_EX(LogMessage::Process::Open, GetLastError());
            return false;
        }

        // Get the process name
        HINSTANCE hMod;
        DWORD cbNeeded;

        if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded))
        {
            GetModuleBaseName(hProcess, hMod, szProcessModuleName, sizeof(szProcessModuleName) / sizeof(TCHAR));
        }

        // Close Handle 
        CloseHandle(hProcess);

        // Compare process name 
        if (strcmp(processName, szProcessModuleName) == 0)
        {
            return (true);
        }
        else
        {
            return (false);
        }
    }
}
