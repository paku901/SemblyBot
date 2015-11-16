#ifndef PROCESS_H
#define PROCESS_H

namespace Sembly
{
    class Process
    {
    public:
        //
        // Constructor
        //
        Process();

        //
        // Destructor
        //
        ~Process();

        //
        // Open / Close
        //
        bool Open(DWORD processID);
        bool Close();

        //
        // Read Methods
        //
        template <class T>
        T Read(const void* address);
        bool ReadText(const void* address, const char* buffer, const DWORD bufferSize);

        //
        // Write Methods
        //
        template <class T>
        bool Write(void* address, const T value);
        bool WriteText(void* address, const char* buffer, const DWORD bufferSize);

        //
        // Get Methods
        //
        UINT32 GetBaseAddress();
        HANDLE GetHandle();
        DWORD GetPid();
        
    private:
        HANDLE process;
        DWORD pid;
    };

    template <class T>
    T Process::Read(const void* address)
    {
        if (this->process == nullptr)
        {
            LOG_ERROR(LogMessage::Process::ProcessIsNull);
            return 0;
        }

        if (address == nullptr)
        {
            return 0;
        }            

        T readValue = T();
        if (ReadProcessMemory(this->process, address, &readValue, sizeof(readValue), nullptr) == 0)
        {
            LOG_ERROR_EX(LogMessage::Process::Read, GetLastError());
            return 0;
        }
        return (readValue);
    }

    template <class T>
    bool Process::Write(void* address, const T value)
    {
        if (this->process == nullptr)
        {
            LOG_ERROR(LogMessage::Process::ProcessIsNull);
            return 0;
        }

        if (address == nullptr)
        {
            return 0;
        }

        if (WriteProcessMemory(this->process, address, &value, sizeof(value), nullptr) == 0)
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