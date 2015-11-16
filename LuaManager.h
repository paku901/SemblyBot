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
        bool Initialize(); // must be called at before using any functions of this class
        void RegisterFunction(const char* pFunctionNameLua, lua_CFunction pFunctionNameC); // registers a C function which can be called from lua
        bool CallFunction(const char* pFunctionNameLua); // calls a function in lua
        bool RunScript(const char* pPathToLuaScript); // interprets and runs a text file with lua code
        bool RunString(const char* pLuaExecuteString); // interprets and runs a string with lua code

        //
        // Get first variable from stack
        //
        lua_Number GetNumberFromStack(); // returns the first variable on stack as number (useful when getting arguments from a lua function mapped to C/C++)
        char* GetStringFromStack(); // returns the first variable on stack as string (useful when getting arguments from a lua function mapped to C/C++)

        //
        // Push a variable onto stack
        //
        void PushNumberToStack(const lua_Number number); // pushes a number onto stack (useful when returning arguments from C/C++ function mapped to lua)
        void PushStringToStack(const char* string); // pushes a string onto stack (useful when returning arguments from C/C++ function mapped to lua)

        //
        // Set a c/c++ variable to lua
        //
        void SetGlobalString(const char* pVariableName, const char* pString); // sets a c/c++ variable which can be access in lua globally
        void SetGlobalNumber(const char* pVariableName, lua_Number number); // sets a c/c++ variable which can be access in lua globally

        //
        // Get a variable from lua to c/c++
        //
        char* GetGlobalString(const char* pVariableName); // returns a global lua variable
        lua_Number GetGlobalNumber(const char* pVariableName); // returns a global lua variable

    private:
        bool isInitialized;
    };
}

#endif // LUA_MANAGER_H