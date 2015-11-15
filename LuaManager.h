#ifndef LUA_MANAGER_H
#define LUA_MANAGER_H

#include "lua.hpp"

#define GET_LUA_ERROR(luaState) lua_tostring(luaState, -1)

namespace Sembly
{
    class LuaManager
    {
    public:
        lua_State* luaState;
        //
        // Constructor
        //
        LuaManager();

        //
        // Destructor
        //
        virtual ~LuaManager();

        //
        // Common Methods
        //
        bool Initialize();
        void RegisterFunction(const char* pFunctionNameLua, lua_CFunction pFunctionNameC);
        bool CallFunction(const char* pFunctionNameLua);
        bool RunScript(const char* pPathToLuaScript);
        bool RunString(const char* pLuaExecuteString);
        void Close();

    private:
        bool isInitialized;
    };
}

#endif // LUA_MANAGER_H