//
//  MUHookRelease.h
//  MUHookDemo
//
//  Created by Magic-Unique on 2018/12/27.
//  Copyright © 2018 unique. All rights reserved.
//

#import <Foundation/Foundation.h>

#if DEBUG == 1
#else

#pragma mark - Main

#define MUHMain                                 static __attribute__((constructor)) initialize

#pragma mark - Quick Statement

#define _MUHClass(c)                            objc_getClass(#c)
#define MUHClass(c)                             _MUHClass(c)

#define MUHSendClassMsg(c, factory)             [MUHClass(c) factory]

#define MUHAlloc(c)                             ((c *)[MUHClass(c) alloc])

#define MUHAllocInitWith(c, init)               [MUHAlloc(c) init]

#define MUHInitClass(c)                         init_##c

#pragma mark - Implementation

#define _MUHInstanceImplementation(c, name, returnType, args...) \
__unused static returnType (*_unique_objc_ori$##c##$##name)   ( c * self, SEL _cmd, ##args ); \
__unused static returnType   _unique_objc_new$##c##$##name    ( c * self, SEL _cmd, ##args )
#define MUHInstanceImplementation(c, name, returnType, args...) _MUHInstanceImplementation(c, name, returnType, ##args)

#define _MUHClassImplementation(c, name, returnType, args...) \
__unused static returnType (*_unique_objc_ori$##c##$##name)   ( __strong const Class self, SEL _cmd, ##args ); \
__unused static returnType   _unique_objc_new$##c##$##name    ( __strong const Class self, SEL _cmd, ##args )
#define MUHClassImplementation(c, name, returnType, args...) _MUHClassImplementation(c, name, returnType, ##args)

#define _MUHSymbolImplementation(symbol, returnType, args...) \
_Pragma("clang diagnostic push") \
_Pragma("clang diagnostic ignored \"-Wstrict-prototypes\"") \
__unused static returnType (*_unique_symbol_ori$##symbol)(args); \
__unused static returnType   _unique_symbol_new$##symbol (args)  \
_Pragma("clang diagnostic pop")
#define MUHSymbolImplementation(symbol, returnType, args...) _MUHSymbolImplementation(symbol, returnType, ##args)

#pragma mark - Execute Orig or Super

#define _MUHOrig(c, name, args...)          (!_unique_objc_ori$##c##$##name?0:_unique_objc_ori$##c##$##name (self, _cmd, ##args))
#define MUHOrig(c, name, args...)           _MUHOrig(c, name, ##args)

#define _MUHSuper(c, name, args...)         (!_unique_objc_ori$##c##$##name?0:_unique_objc_ori$##c##$##name (self, _cmd, ##args))
#define MUHSuper(c, name, args...)          _MUHSuper(c, name, ##args)

#define _MUHSymbolOrig(symbol, args...)     (_unique_symbol_ori$##symbol(args))
#define MUHSymbolOrig(symbol, args...)      _MUHSymbolOrig(symbol, ##args)

#pragma mark - Hook

#define _MUHHookInstanceMessage(c, name, sel) \
MUHookInstanceMessageEx(objc_getClass( #c ), @selector(sel), (IMP)&_unique_objc_new$##c##$##name, (IMP*)&_unique_objc_ori$##c##$##name)
#define MUHHookInstanceMessage(c, name, sel) _MUHHookInstanceMessage(c, name, sel)

#define _MUHHookClassMessage(c, name, sel) \
MUHookClassMessageEx(objc_getClass( #c ), @selector(sel), (IMP)&_unique_objc_new$##c##$##name, (IMP*)&_unique_objc_ori$##c##$##name)
#define MUHHookClassMessage(c, name, sel) _MUHHookClassMessage(c, name, sel)

#define _MUHHookSymbolFunction(symbol) \
MURebindSymbol(#symbol, _unique_symbol_new$##symbol, (void *)&_unique_symbol_ori$##symbol)
#define MUHHookSymbolFunction(symbol) _MUHHookSymbolFunction(symbol)

#pragma mark - Create

#define _MUHAddInstanceMethod(c, name, sel, encode) \
MUAddInstanceMessageEx(objc_getClass( #c ), @selector(sel), (IMP)&_unique_objc_new$##c##$##name, #encode , (IMP*)&_unique_objc_ori$##c##$##name)
#define MUHAddInstanceMethod(c, name, sel, encode) _MUHAddInstanceMethod(c, name, sel, encode)

#define _MUHAddClassMethod(c, name, sel, encode) \
MUAddClassMessageEx(objc_getMetaClass( #c ), @selector(sel), (IMP)&_unique_objc_new$##c##$##name, #encode , (IMP*)&_unique_objc_ori$##c##$##name)
#define MUHAddClassMethod(c, name, sel, encode) _MUHAddClassMethod(c, name, sel, encode)

#endif
