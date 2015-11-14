#ifndef PROCESS_H
#define PROCESS_H

namespace Sembly
{
    class Process
    {
    private:
        HANDLE process;
        DWORD pid;

    public:
        Process();
        ~Process();

        bool Open(DWORD processID);
        bool Close();

        template <class T>
        T Read(const DWORD address);
        bool ReadText(const DWORD address, const char* buffer, const DWORD bufferSize);

        template <class T>
        bool Write(const DWORD address, const T value);
        bool WriteText(const DWORD address, const char* buffer, const DWORD bufferSize);

        UINT32 GetBaseAddress();
        BOOL EnableDebugPrivilege(BOOL state);

    };

    template <class T>
    T Process::Read(const DWORD address)
    {
        if (this->process == nullptr)
        {
            LOG_ERROR(LogMessage::Process::ProcessIsNull);
            return 0;
        }

        T readValue = T();
        if (ReadProcessMemory(this->process, (LPVOID)address, &readValue, sizeof(readValue), nullptr) == 0)
        {
            LOG_ERROR_EX(LogMessage::Process::Read, GetLastError());
            return 0;
        }
        return (readValue);
    }

    template <class T>
    bool Process::Write(const DWORD address, const T value)
    {
        if (this->process == nullptr)
        {
            LOG_ERROR(LogMessage::Process::ProcessIsNull);
            return 0;
        }

        if (WriteProcessMemory(this->process, (LPVOID)address, &value, sizeof(value), nullptr) == 0)
        {
            LOG_ERROR_EX(LogMessage::Process::Write, GetLastError());
            return (false);
        }
        else
        {
            return (true);
        }
    }
}
#endif // PROCESS_H