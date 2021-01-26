#ifndef STRAITX_LOG_HPP
#define STRAITX_LOG_HPP

#include "platform/result.hpp"
#include "platform/io.hpp"
#include "platform/compiler.hpp"

#define RED_ANSI     "\x1b[91m"
#define GREEN_ANSI   "\x1b[92m"
#define YELLOW_ANSI  "\x1b[93m"
#define BLUE_ANSI    "\x1b[94m"
#define MAGENTA_ANSI "\x1b[95m"
#define RESET_ANSI   "\x1b[0m"

#define Red(string) RED_ANSI string RESET_ANSI
#define Green(string) GREEN_ANSI string RESET_ANSI
#define Yellow(string) YELLOW_ANSI string RESET_ANSI
#define Blue(string) BLUE_ANSI string RESET_ANSI
#define Magenta(string) MAGENTA_ANSI string RESET_ANSI

#ifdef SX_DEBUG

#define DLog(source,error) StraitX::Output::Printf("[%]: %: %\n",error==Result::Success? "Info " : "Result",source, ResultNames[(int)error])
#define DLogTrace(...) {StraitX::Output::Printf("[Trace]: "); StraitX::Output::Printf(__VA_ARGS__); StraitX::Output::Printf("\n");}
#define DLogInfo(...)  {StraitX::Output::Printf("[Info ]: " GREEN_ANSI); StraitX::Output::Printf(__VA_ARGS__); StraitX::Output::Printf("\n" YELLOW_ANSI);}
#define DLogWarn(...)  {StraitX::Output::Printf("[Warn ]: " MAGENTA_ANSI); StraitX::Output::Printf(__VA_ARGS__); StraitX::Output::Printf("\n" RESET_ANSI);}
#define DLogError(...) {StraitX::Output::Printf("[Error]: " RED_ANSI); StraitX::Output::Printf(__VA_ARGS__); StraitX::Output::Printf("\n" RESET_ANSI);}
#define DLogSeparator() StraitX::Output::Print("===============================================================")

#else

#define DLog(source,error)  ((void)0)
#define DLogTrace(msg)      ((void)0)
#define DLogInfo(msg)       ((void)0)
#define DLogWarn(msg)       ((void)0)
#define DLogError(msg)      ((void)0)
#define DLogSeparator()     ((void)0)

#endif

#define Log(source,error) StraitX::Output::Printf("[%]: %: %\n",error==Result::Success? "Info " : "Result",source, ResultNames[(int)error])
#define LogTrace(...) {StraitX::Output::Printf("[Trace]: "); StraitX::Output::Printf(__VA_ARGS__); StraitX::Output::Printf("\n");}
#define LogInfo(...)  {StraitX::Output::Printf("[Info ]: " GREEN_ANSI); StraitX::Output::Printf(__VA_ARGS__); StraitX::Output::Printf("\n" RESET_ANSI);}
#define LogWarn(...)  {StraitX::Output::Printf("[Warn ]: " MAGENTA_ANSI); StraitX::Output::Printf(__VA_ARGS__); StraitX::Output::Printf("\n" RESET_ANSI);}
#define LogError(...) {StraitX::Output::Printf("[Error]: " RED_ANSI); StraitX::Output::Printf(__VA_ARGS__); StraitX::Output::Printf("\n" RESET_ANSI);}
#define LogSeparator() StraitX::Output::Print("===============================================================")

#endif // STRAITX_LOG_HPP