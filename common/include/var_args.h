#ifndef VAR_ARGS_H
#define VAR_ARGS_H

typedef void const * argList;

#define initArgList(list, lastNamedArg)  {list = &lastNamedArg; list += sizeof(void *);}

#define nextArg(list, type)  *(type *)list; list += sizeof(void *)

#endif // VAR_ARGS_H