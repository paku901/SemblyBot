#ifndef PROCESS_LIST_H
#define PROCESS_LIST_H

namespace Sembly
{
    class ProcessList
    {
    public:
        static std::vector<DWORD> GetByName(const char* processName);
        static bool IsSearchingProcess(DWORD processID, const char* processName);
    };
}

#endif PROCESS_LIST_H // PROCESS_LIST_H
