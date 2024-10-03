// al-martyn1's  wrapper over original Protothreads lib


#pragma once

#include "pt.h"
//
#include "pt-sem.h"



#define PTPP_WAITING    PT_WAITING   /* PT_WAIT_UNTIL, PT_WAIT_WHILE, PT_WAIT_THREAD, PT_SPAWN, PT_RESTART */
#define PTPP_YIELDED    PT_YIELDED   /* PT_YIELDED, PT_YIELD_UNTIL */
#define PTPP_EXITED     PT_EXITED    /* PT_EXIT */
#define PTPP_ENDED      PT_ENDED     /* PT_ENDED */


#define PTPP_IS_WAITING(code)                 ((code)==PT_WAITING)
#define PTPP_IS_YIELDED(code)                 ((code)==PT_YIELDED)
#define PTPP_IS_EXITED(code)                  ((code)==PT_EXITED)
#define PTPP_IS_ENDED(code)                   ((code)==PT_ENDED)
#define PTPP_IS_EXITED_OR_ENDED(code)         ((code)==PT_EXITED || (code)==PT_ENDED)


#define PTPP_INIT()                           PT_INIT(&(this->ptContext))


// #define PT_THREAD(name_args) char name_args


// Use next macros for childs of ProtothreadBase
#define PTPP_THREAD_INLINE_PROC(args)         int operator()( args )
#define PTPP_THREAD_INLINE_PROC_CONST(args)   int operator()( args ) const

#define PTPP_THREAD_PROC(cls, args)           int cls :: operator()( args )
#define PTPP_THREAD_PROC_CONST(cls, args)     int cls :: operator()( args ) const



// #define PTPP_BEGIN()                          PT_BEGIN(&(this->ptContext))
#define PTPP_BEGIN()                          { char PT_YIELD_FLAG = 1; (void)PT_YIELD_FLAG; LC_RESUME((&(this->ptContext))->lc)

#if 0
#define PTPP_END(code)                        do                               \
                                              {                                \
                                                  this->exitCode = code;       \
                                                  PT_END(&(this->ptContext));  \
                                              } while(0)
#endif

#define PTPP_END(code)                        this->exitCode = code;                               \
                                              LC_END((&(this->ptContext))->lc); PT_YIELD_FLAG = 0; \
                                              PT_INIT(&(this->ptContext)); return PT_ENDED;  }




/* Блокирует тред, пока условие не выполняется */
#define PTPP_WAIT_UNTIL(condition)            PT_WAIT_UNTIL(&(this->ptContext), condition)

/* Блокирует тред, пока условие выполняется */
#define PTPP_WAIT_WHILE(cond)                 PT_WAIT_WHILE(&(this->ptContext), cond)

// #define PT_WAIT_THREAD(pt, thread)
//#define PT_SPAWN(pt, child, thread)

#define PTPP_RESTART()                        PT_RESTART(&(this->ptContext))

#define PTPP_EXIT(code)                       do                               \
                                              {                                \
                                                  this->exitCode = code;       \
                                                  PT_EXIT(&(this->ptContext)); \
                                              } while(0)

#if 0
#define PTPP_EXIT()                           PT_EXIT()

#define PTPP_EXIT(code)                       do {                       \
                                                this->exitCode = code;   \
                                                PT_EXIT(&(this->ptContext));\
                                              } while(0)
#endif

// #define PT_SCHEDULE(f)

#define PTPP_YIELD()                          PT_YIELD(&(this->ptContext))
#define PTPP_YIELD_UNTIL(cond)                PT_YIELD_UNTIL(&(this->ptContext), cond)
#define PTPP_YIELD_WHILE(cond)                PTPP_YIELD_UNTIL(!(cond))

/////




// protothreads::
namespace protothreads
{

using PtContext = struct ::pt;


struct ThreadBase
{

protected:

    mutable PtContext ptContext;
    mutable int       exitCode = 0;

public:

    static const char* getResultCodeName(int code)
    {
        switch(code)
        {
            case PT_WAITING: return "PT_WAITING";
            case PT_YIELDED: return "PT_YIELDED";
            case PT_EXITED : return "PT_EXITED" ;
            case PT_ENDED  : return "PT_ENDED"  ;
            default        : return "<UNKNOWN>"  ;
        };
    }


    int getExitCode() { return exitCode; }

    ThreadBase()
    {
        PTPP_INIT();
    }




}; // struct ThreadBase




} // namespace protothreads
