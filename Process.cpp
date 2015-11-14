#include "StdAfx.h"

namespace Sembly
{
    Process::Process()
    {
    }


    Process::~Process()
    {
        Close();
    }


    bool Process::Open(DWORD processID)
    {
        HANDLE process = OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, processID);
        if (process == nullptr)
        {
            LOG_ERROR_EX(LogMessage::Process::Open, GetLastError());
            return false;
        }

        if (this->process != nullptr)
        {
            Close();
        }

        this->process = process;
        this->pid = processID;

        return true;
    }

    bool Process::Close()
    {
        if (this->process == nullptr)
        {
            LOG_WARNING(LogMessage::Process::Close);
            return false;
        }

        CloseHandle(this->process);
        this->process = nullptr;
        return true;
    }

    bool Process::ReadText(const DWORD address, const char* buffer, const DWORD bufferSize)
    {
        if (this->process == nullptr)
        {
            LOG_ERROR(LogMessage::Process::ProcessIsNull);
            return 0;
        }

        if (bufferSize < 0)
        {
            return false;
        }

        if (buffer == nullptr)
            return false;
        
        for (unsigned int i = 0; i < bufferSize; i++)
        {
            if (ReadProcessMemory(this->process, (LPVOID)(address+i), (LPVOID)(buffer+i), 1, nullptr) == 0)
            {
                LOG_ERROR_EX(LogMessage::Process::Read, GetLastError());
                return false;
            }

            if (buffer[i] == '\0')
            {
                break;
            }
        }
        
        return true;
    }

    bool Process::WriteText(const DWORD address, const char* buffer, const DWORD bufferSize)
    {
        if (this->process == nullptr)
        {
            LOG_ERROR(LogMessage::Process::ProcessIsNull);
            return 0;
        }

        if (bufferSize < 0)
        {
            return false;
        }

        if (buffer == nullptr)
            return false;

        for (unsigned int i = 0; i < bufferSize; i++)
        {
            if (WriteProcessMemory(this->process, (LPVOID)address, (LPCVOID)buffer, bufferSize, nullptr) == 0)
            {
                LOG_ERROR_EX(LogMessage::Process::Write, GetLastError());
                return false;
            }
        }

        return true;
    }

    UINT32 Process::GetBaseAddress()
    {
        TCHAR szProcessModuleName[MAX_PATH] = TEXT("<none>");

        // Get a handle to the process
        HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, this->pid);
        if (hProcess == nullptr)
        {
            LOG_ERROR_EX(LogMessage::Process::Open, GetLastError());
            return 0;
        }

        // Get the base address of the module
        HINSTANCE hMod;
        DWORD cbNeeded;

        if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded))
        {
            GetModuleBaseName(hProcess, hMod, szProcessModuleName, sizeof(szProcessModuleName) / sizeof(TCHAR));
        }

        CloseHandle(hProcess);
        return ((UINT32)hMod);
    }

    BOOL Process::EnableDebugPrivilege(BOOL state)
    {
        HANDLE hToken = NULL; // handle to token
        LUID luid; // local unique identifier

        // retrieves the token from the current process which can be adjusted
        if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken))
        {
            return FALSE;
        }

        // retrieves the locally unique identifier which is represented by the privilege name
        if (!LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &luid))
        {
            return FALSE;
        }

        // token adjustment
        TOKEN_PRIVILEGES tokenPriv;
        tokenPriv.PrivilegeCount = 1;
        tokenPriv.Privileges[0].Luid = luid;
        tokenPriv.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

        // store new token in process
        if (!AdjustTokenPrivileges(hToken, FALSE, &tokenPriv, sizeof(TOKEN_PRIVILEGES), NULL, NULL))
        {
            return FALSE;
        }

        // everything went fine :D
        return TRUE;
    }
}