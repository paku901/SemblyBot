#include "StdAfx.h"

namespace Sembly
{
    //
    // Constructor
    //
    LuaManager::LuaManager()
        : isInitialized(false)
    {

    }

    //
    // Destructor
    //
    LuaManager::~LuaManager()
    {
        if (this->luaState != nullptr)
        {
            Close();
        }
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
        
        lua_register(this->luaState, pFunctionNameLua, pFunctionNameC);
    }

    bool LuaManager::CallFunction(const char* pFunctionNameLua)
    {
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

        if (luaL_dofile(this->luaState, pPathToLuaScript) == 1)
        {
            // log error with dynamic lua message
            LOG_ERROR(GET_LUA_ERROR(this->luaState))
            return false;
        }
        
        return true;
    }

    bool LuaManager::RunString(const char* pLuaExecuteString)
    {
        if (!this->isInitialized)
            return false;

        if (luaL_dostring(this->luaState, pLuaExecuteString) == 1)
        {
            // log error with dynamic lua message
            LOG_ERROR(GET_LUA_ERROR(this->luaState))
            return false;
        }

        return true;
    }

    void LuaManager::Close()
    {
        if (this->luaState == nullptr)
            return;

        lua_close(this->luaState);
        this->luaState = nullptr;
    }
}