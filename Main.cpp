#include "StdAfx.h"

void main()
{
    Sembly::LuaManager luaManager;
    luaManager.Initialize();
    luaManager.RunString("print(12345)");

    /*
    auto processList = Sembly::ProcessList::GetByName("HookingExample.exe");

    if (processList.size() > 0)
    {
        Sembly::Process process;
        process.Open(processList[0]);
        char szBuffer[512] = { 0 };
        process.ReadText(0x0135F038, szBuffer, sizeof(szBuffer)); //0x0028fb70
        std::cout << szBuffer << std::endl;

        process.WriteText(0x0135F038, "1234567", 8);

        ZeroMemory(szBuffer, sizeof(szBuffer));
        process.ReadText(0x0135F038, szBuffer, sizeof(szBuffer)); //0x0028fb70
        std::cout << szBuffer << std::endl;
        //char x = process.Read<char>(0x0116F000);

    }
    */
}