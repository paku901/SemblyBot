#include "StdAfx.h"

namespace Sembly
{
    LuaManager::LuaManager()
        : isInitialized(false)
    {}

    LuaManager::~LuaManager()
    {
        if (this->luaState == nullptr)
            return;

        lua_close(this->luaState);
        this->luaState = nullptr;
    }

    bool LuaManager::Initialize()
    {
        if (this->isInitialized)
            return false;

        this->luaState = luaL_newstate();
        if (this->luaState == nullptr)
        {
            LOG_ERROR(LogMessage::LuaManager::LuaStateIsNull)
            return false;
        }

        luaL_openlibs(luaState);

        this->isInitialized = true;

        return true;
    }

    void LuaManager::RegisterFunction(const char* pFunctionNameLua, lua_CFunction pFunctionNameC)
    {
        if (!this->isInitialized)
            return;

        if (pFunctionNameLua == nullptr || pFunctionNameC == nullptr)
            return;
        
        lua_register(this->luaState, pFunctionNameLua, pFunctionNameC);
    }

    bool LuaManager::CallFunction(const char* pFunctionNameLua)
    {
        if (!this->isInitialized)
            return false;

        if (pFunctionNameLua == nullptr)
            return false;

        int result = lua_getglobal(this->luaState, pFunctionNameLua);

        if (lua_isfunction(this->luaState, lua_gettop(this->luaState)))
        {
            lua_call(this->luaState, 0, 0);
            return true;
        }
        else
        {
            LOG_WARNING(LogMessage::LuaManager::LuaCallFailed)
            return false;
        }
    }

    bool LuaManager::RunScript(const char* pPathToLuaScript)
    {
        if (!this->isInitialized)
            return false;

        if (pPathToLuaScript == nullptr)
            return false;

        if (luaL_dofile(this->luaState, pPathToLuaScript) == 1)
        {
            LOG_ERROR(GET_LUA_ERROR(this->luaState))
            return false;
        }
        
        return true;
    }

    bool LuaManager::RunString(const char* pLuaExecuteString)
    {
        if (!this->isInitialized)
            return false;

        if (pLuaExecuteString == nullptr)
            return false;

        if (luaL_dostring(this->luaState, pLuaExecuteString) == 1)
        {
            LOG_ERROR(GET_LUA_ERROR(this->luaState))
            return false;
        }

        return true;
    }

    lua_Number LuaManager::GetNumberFromStack()
    {
        if (!this->isInitialized)
            return 0;

        int luaType = lua_type(this->luaState, lua_gettop(this->luaState));

        if (luaType == LUA_TNUMBER)
        {
            lua_Number number = lua_tonumber(this->luaState, lua_gettop(this->luaState));
            lua_pop(this->luaState, 1);
            return number;          
        }
        else
        {
            return 0;
        }
    }

    char* LuaManager::GetStringFromStack()
    {
        if (!this->isInitialized)
            return nullptr;

        int luaType = lua_type(this->luaState, lua_gettop(this->luaState));

        if (luaType == LUA_TSTRING)
        {
            char* string = (char*)lua_tostring(this->luaState, lua_gettop(this->luaState));
            lua_pop(this->luaState, 1);
            return string;
        }
        else
        {
            return nullptr;
        }
    }

    void LuaManager::PushNumberToStack(const lua_Number number)
    {
        if (!this->isInitialized)
            return;

        lua_pushnumber(this->luaState, number);
    }

    void LuaManager::PushStringToStack(const char* pString)
    {
        if (!this->isInitialized)
            return;

        if (pString == nullptr)
            return;

        lua_pushstring(this->luaState, pString);
    }

    void LuaManager::SetGlobalString(const char* pVariableName, const char* pString)
    {
        if (!this->isInitialized)
            return;

        if (pVariableName == nullptr || pString == nullptr)
            return;

        lua_pushstring(this->luaState, pString);
        lua_setglobal(this->luaState, pVariableName);
    }

    void LuaManager::SetGlobalNumber(const char* pVariableName, lua_Number number)
    {
        if (!this->isInitialized)
            return;

        if (pVariableName == nullptr)
            return;

        lua_pushnumber(this->luaState, number);
        lua_setglobal(this->luaState, pVariableName);
    }

    char* LuaManager::GetGlobalString(const char* pVariableName)
    {
        if (!this->isInitialized)
            return nullptr;

        if (pVariableName == nullptr)
            return nullptr;

        int luaType = lua_getglobal(this->luaState, pVariableName);

        if (luaType == LUA_TSTRING)
        {
            char* pString = (char*)lua_tostring(this->luaState, lua_gettop(this->luaState));
            lua_pop(this->luaState, 1);
            return pString;
        }
        else
        {
            lua_pop(this->luaState, 1);
            return nullptr;
        }
    }

    lua_Number LuaManager::GetGlobalNumber(const char* pVariableName)
    {
        if (!this->isInitialized)
            return 0;

        if (pVariableName == nullptr)
            return 0;

        int luaType = lua_getglobal(this->luaState, pVariableName);

        if (luaType == LUA_TNUMBER)
        {
            lua_Number number = lua_tonumber(this->luaState, lua_gettop(this->luaState));
            lua_pop(this->luaState, 1);
            return number;
        }
        else
        {
            lua_pop(this->luaState, 1);
            return 0;
        }
    }
}