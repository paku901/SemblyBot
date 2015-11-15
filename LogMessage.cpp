#include "StdAfx.h"

namespace Sembly
{
    char* LogMessage::Process::Open = "Failed to open process.";
    char* LogMessage::Process::Read = "Failed to read process.";
    char* LogMessage::Process::Write = "Failed to write process.";
    char* LogMessage::Process::Close = "Process is already closed.";
    char* LogMessage::Process::Found = "Found process.";
    char* LogMessage::Process::ProcessIsNull = "Process is null.";
    
    char* LogMessage::LuaManager::LuaStateIsNull = "luaState is null.";
    char* LogMessage::LuaManager::LuaCallFailed = "lua_call failed.";
    
}