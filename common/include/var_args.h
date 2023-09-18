#ifndef VAR_ARGS_H
#define VAR_ARGS_H

typedef void * argList;

#define initArgList(list, lastNamedArg)  {list = &lastNamedArg; --list;}

#define nextArg(argList, type)  ((type)--argList)

#endif VAR_ARGS_H