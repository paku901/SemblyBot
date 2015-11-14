#ifndef LOG_MESSAGE_H
#define LOG_MESSAGE_H

namespace Sembly
{
    struct LogMessage
    {
        struct Process
        {
            static char* Open;
            static char* Read;
            static char* Write;
            static char* Close;
            static char* Found;
            static char* ProcessIsNull;
        };
    };
}

#endif // LOG_MESSAGE_H