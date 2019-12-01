/*
 * This file is part of the Process Hacker project - https://processhacker.sf.io/ 
 *
 * You can redistribute this file and/or modify it under the terms of the 
 * Attribution 4.0 International (CC BY 4.0) license. 
 * 
 * You must give appropriate credit, provide a link to the license, and 
 * indicate if changes were made. You may do so in any reasonable manner, but 
 * not in any way that suggests the licensor endorses you or your use.
 */

#ifndef _NTXCAPI_H
#define _NTXCAPI_H

NTDLL_API(BOOLEAN, __stdcall, RtlDispatchException, (
    _In_ PEXCEPTION_RECORD ExceptionRecord,
    _In_ PCONTEXT ContextRecord
))

NTDLL_API_VOID(__stdcall, RtlRaiseStatus, (
    _In_ NTSTATUS Status
))

NTDLL_API_VOID(__stdcall, RtlRaiseException, (
    _In_ PEXCEPTION_RECORD ExceptionRecord
))

NATIVE_API(NTSTATUS, NTCALL, /*Nt*/Continue, (
    _In_ PCONTEXT ContextRecord,
    _In_ BOOLEAN TestAlert
))

NATIVE_API(NTSTATUS, NTCALL, /*Nt*/RaiseException, (
    _In_ PEXCEPTION_RECORD ExceptionRecord,
    _In_ PCONTEXT ContextRecord,
    _In_ BOOLEAN FirstChance
))

__analysis_noreturn
NTDLL_API_VOID(__stdcall, RtlAssert, (
    _In_ PVOID VoidFailedAssertion,
    _In_ PVOID VoidFileName,
    _In_ ULONG LineNumber,
    _In_opt_ PSTR MutableMessage
))

#define RTL_ASSERT(exp) \
    ((!(exp)) ? (RtlAssert((PVOID)#exp, (PVOID)__FILE__, __LINE__, NULL), FALSE) : TRUE)
#define RTL_ASSERTMSG(msg, exp) \
    ((!(exp)) ? (RtlAssert((PVOID)#exp, (PVOID)__FILE__, __LINE__, msg), FALSE) : TRUE)
#define RTL_SOFT_ASSERT(_exp) \
    ((!(_exp)) ? (DbgPrint("%s(%d): Soft assertion failed\n   Expression: %s\n", __FILE__, __LINE__, #_exp), FALSE) : TRUE)
#define RTL_SOFT_ASSERTMSG(_msg, _exp) \
    ((!(_exp)) ? (DbgPrint("%s(%d): Soft assertion failed\n   Expression: %s\n   Message: %s\n", __FILE__, __LINE__, #_exp, (_msg)), FALSE) : TRUE)

#endif
