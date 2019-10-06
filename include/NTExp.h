#pragma once

#include <Windows.h>

// ----------------------------------------
//   API Prolog

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _M_IX86
  #pragma pack(push, 4)
#elif _M_AMD64
  #pragma pack(push, 8)
#else
  #error NTLIB: Error, unknown architecture
#endif

#define NTCALL __stdcall

#ifdef NTLIB_COMPILATION
  #define NTDEF __declspec(dllexport) NTCALL
#else
  #define NTDEF __declspec(dllimport) NTCALL
#endif

#ifdef NTLIB_COMPILATION
  #define NATIVE_API(type, name, params) \
    type NTDEF Zw##name params { return (type)0; } \
    type NTDEF Nt##name params { return (type)0; }
  #define NATIVE_API_VOID(name, params) \
    VOID NTDEF name params{ return; }
  #define NTDLL_API(type, name, params) \
    type NTDEF name params { return (type)0; }
  #define NTDLL_API_VOID(name, params) \
    VOID NTDEF name params { return; }
#else
  #define NATIVE_API(type, name, params) \
    type NTDEF Zw##name params; \
    type NTDEF Nt##name params;
  #define NATIVE_API_VOID(name, params) \
    VOID NTDEF name params;
  #define NTDLL_API(type, name, params) \
    type NTDEF name params;
  #define NTDLL_API_VOID(name, params) \
    VOID NTDEF name params;
#endif

#define NTLIB_WIN_2K      0x0400
#define NTLIB_WIN_XP      0x0500
#define NTLIB_WIN_VISTA   0x0600
#define NTLIB_WIN_7       0x0601
#define NTLIB_WIN_8       0x0602
#define NTLIB_WIN_8_1     0x0603
#define NTLIB_WIN_10_TH1  0x0A00
#define NTLIB_WIN_10_TH2  0x0A01
#define NTLIB_WIN_10_RS1  0x0A02
#define NTLIB_WIN_10_RS2  0x0A03
#define NTLIB_WIN_10_RS3  0x0A04
#define NTLIB_WIN_10_RS4  0x0A05
#define NTLIB_WIN_10_RS5  0x0A06
#define NTLIB_WIN_10_19H1 0x0A07
#define NTLIB_WIN_MAX     0xFFFF

#ifndef NTLIB_WIN_VERSION
  #define NTLIB_WIN_VERSION NTLIB_WIN_MAX
#endif

#define NTLIB_KERNEL_MODE 0
#define NTLIB_USER_MODE   1

#ifndef NTLIB_CPU_MODE
  #define NTLIB_CPU_MODE NTLIB_USER_MODE
#endif

// ----------------------------------------
//   Include zone

#define MEM_EXTENDED_PARAMETER_TYPE_BITS 8

    typedef struct MEM_EXTENDED_PARAMETER {
        struct {
            DWORD64 Type : MEM_EXTENDED_PARAMETER_TYPE_BITS;
            DWORD64 Reserved : 64 - MEM_EXTENDED_PARAMETER_TYPE_BITS;
        } DUMMYSTRUCTNAME;
        union {
            DWORD64 ULong64;
            PVOID   Pointer;
            SIZE_T  Size;
            HANDLE  Handle;
            DWORD   ULong;
        } DUMMYUNIONNAME;
    } MEM_EXTENDED_PARAMETER, *PMEM_EXTENDED_PARAMETER;

    typedef struct _CFG_CALL_TARGET_INFO {
        ULONG_PTR Offset;
        ULONG_PTR Flags;
    } CFG_CALL_TARGET_INFO, *PCFG_CALL_TARGET_INFO;

    typedef struct _PROCESS_MITIGATION_CONTROL_FLOW_GUARD_POLICY {
        union {
            DWORD Flags;
            struct {
                DWORD EnableControlFlowGuard : 1;
                DWORD EnableExportSuppression : 1;
                DWORD StrictMode : 1;
                DWORD ReservedFlags : 29;
            } DUMMYSTRUCTNAME;
        } DUMMYUNIONNAME;
    } PROCESS_MITIGATION_CONTROL_FLOW_GUARD_POLICY, *PPROCESS_MITIGATION_CONTROL_FLOW_GUARD_POLICY;

    typedef struct _PROCESS_MITIGATION_FONT_DISABLE_POLICY {
        union {
            DWORD Flags;
            struct {
                DWORD DisableNonSystemFonts : 1;
                DWORD AuditNonSystemFontLoading : 1;
                DWORD ReservedFlags : 30;
            } DUMMYSTRUCTNAME;
        } DUMMYUNIONNAME;
    } PROCESS_MITIGATION_FONT_DISABLE_POLICY, *PPROCESS_MITIGATION_FONT_DISABLE_POLICY;

    typedef struct _PROCESS_MITIGATION_IMAGE_LOAD_POLICY {
        union {
            DWORD Flags;
            struct {
                DWORD NoRemoteImages : 1;
                DWORD NoLowMandatoryLabelImages : 1;
                DWORD PreferSystem32Images : 1;
                DWORD AuditNoRemoteImages : 1;
                DWORD AuditNoLowMandatoryLabelImages : 1;
                DWORD ReservedFlags : 27;
            } DUMMYSTRUCTNAME;
        } DUMMYUNIONNAME;
    } PROCESS_MITIGATION_IMAGE_LOAD_POLICY, *PPROCESS_MITIGATION_IMAGE_LOAD_POLICY;

    typedef struct _PROCESS_MITIGATION_SYSTEM_CALL_FILTER_POLICY {
        union {
            ULONG Flags;
            struct {
                ULONG FilterId : 4;
                ULONG ReservedFlags : 28;
            } DUMMYSTRUCTNAME;
        } DUMMYUNIONNAME;
    } PROCESS_MITIGATION_SYSTEM_CALL_FILTER_POLICY, *PPROCESS_MITIGATION_SYSTEM_CALL_FILTER_POLICY;

    typedef struct _PROCESS_MITIGATION_PAYLOAD_RESTRICTION_POLICY {
        union {
            ULONG Flags;
            struct {
                ULONG EnableExportAddressFilter : 1;
                ULONG AuditExportAddressFilter : 1;
                ULONG EnableExportAddressFilterPlus : 1;
                ULONG AuditExportAddressFilterPlus : 1;
                ULONG EnableImportAddressFilter : 1;
                ULONG AuditImportAddressFilter : 1;
                ULONG EnableRopStackPivot : 1;
                ULONG AuditRopStackPivot : 1;
                ULONG EnableRopCallerCheck : 1;
                ULONG AuditRopCallerCheck : 1;
                ULONG EnableRopSimExec : 1;
                ULONG AuditRopSimExec : 1;
                ULONG ReservedFlags : 20;
            } DUMMYSTRUCTNAME;
        } DUMMYUNIONNAME;
    } PROCESS_MITIGATION_PAYLOAD_RESTRICTION_POLICY, *PPROCESS_MITIGATION_PAYLOAD_RESTRICTION_POLICY;

    typedef struct _PROCESS_MITIGATION_CHILD_PROCESS_POLICY {
        union {
            ULONG Flags;
            struct {
                ULONG NoChildProcessCreation : 1;
                ULONG AuditNoChildProcessCreation : 1;
                ULONG AllowSecureProcessCreation : 1;
                ULONG ReservedFlags : 29;
            } DUMMYSTRUCTNAME;
        } DUMMYUNIONNAME;
    } PROCESS_MITIGATION_CHILD_PROCESS_POLICY, *PPROCESS_MITIGATION_CHILD_PROCESS_POLICY;

    typedef struct _PROCESS_MITIGATION_SIDE_CHANNEL_ISOLATION_POLICY {
        ULONG reserved;
    } PROCESS_MITIGATION_SIDE_CHANNEL_ISOLATION_POLICY, *PPROCESS_MITIGATION_SIDE_CHANNEL_ISOLATION_POLICY;

    typedef GUID* PGUID;

    typedef enum _OS_DEPLOYEMENT_STATE_VALUES
    {
    OS_DEPLOYMENT_STANDARD = 1,
         OS_DEPLOYMENT_COMPACT
     } OS_DEPLOYEMENT_STATE_VALUES;

    typedef enum _PNP_VETO_TYPE {
        PNP_VetoTypeUnknown,
        PNP_VetoLegacyDevice,
        PNP_VetoPendingClose,
        PNP_VetoWindowsApp,
        PNP_VetoWindowsService,
        PNP_VetoOutstandingOpen,
        PNP_VetoDevice,
        PNP_VetoDriver,
        PNP_VetoIllegalDeviceRequest,
        PNP_VetoInsufficientPower,
        PNP_VetoNonDisableable,
        PNP_VetoLegacyDriver,
        PNP_VetoInsufficientRights,
        PNP_VetoAlreadyRemoved
    } PNP_VETO_TYPE, *PPNP_VETO_TYPE;

    typedef UCHAR SE_SIGNING_LEVEL, *PSE_SIGNING_LEVEL;

    typedef _IMAGE_RUNTIME_FUNCTION_ENTRY RUNTIME_FUNCTION, *PRUNTIME_FUNCTION;

#ifndef _WIN64
    typedef FARPROC PGET_RUNTIME_FUNCTION_CALLBACK;
#endif

#define SE_SIGNING_LEVEL_UNCHECKED         0x00000000
#define SE_SIGNING_LEVEL_UNSIGNED          0x00000001
#define SE_SIGNING_LEVEL_ENTERPRISE        0x00000002
#define SE_SIGNING_LEVEL_CUSTOM_1          0x00000003
#define SE_SIGNING_LEVEL_AUTHENTICODE      0x00000004
#define SE_SIGNING_LEVEL_CUSTOM_2          0x00000005
#define SE_SIGNING_LEVEL_STORE             0x00000006
#define SE_SIGNING_LEVEL_CUSTOM_3          0x00000007
#define SE_SIGNING_LEVEL_ANTIMALWARE       SE_SIGNING_LEVEL_CUSTOM_3
#define SE_SIGNING_LEVEL_MICROSOFT         0x00000008
#define SE_SIGNING_LEVEL_CUSTOM_4          0x00000009
#define SE_SIGNING_LEVEL_CUSTOM_5          0x0000000A
#define SE_SIGNING_LEVEL_DYNAMIC_CODEGEN   0x0000000B
#define SE_SIGNING_LEVEL_WINDOWS           0x0000000C
#define SE_SIGNING_LEVEL_CUSTOM_7          0x0000000D
#define SE_SIGNING_LEVEL_WINDOWS_TCB       0x0000000E
#define SE_SIGNING_LEVEL_CUSTOM_6          0x0000000F

#define PHNT_COMPILE 1
#define PHNT_NO_INLINE_INIT_STRING

#include <ntexp\ntstatus.h>
#include <ntexp\ntcommon.h>

#include <ntexp\ntkeapi.h>

#include <ntexp\ntldr.h>
#include <ntexp\ntexapi.h>
#include <ntexp\ntmmapi.h>

#include <ntexp\ntobapi.h>
#include <ntexp\ntpsapi.h>

#include <ntexp\ntdbg.h>
#include <ntexp\ntioapi.h>
#include <ntexp\ntlpcapi.h>
#include <ntexp\ntpfapi.h>
#include <ntexp\ntpnpapi.h>
#include <ntexp\ntpoapi.h>
#include <ntexp\ntregapi.h>
#include <ntexp\ntnls.h>
#include <ntexp\ntrtl.h>

#include <ntexp\ntgdi.h>
#include <ntexp\ntmisc.h>
#include <ntexp\ntpebteb.h>
#include <ntexp\ntsam.h>
#include <ntexp\ntseapi.h>
#include <ntexp\ntsmss.h>
#include <ntexp\nttmapi.h>
#include <ntexp\nttp.h>
#include <ntexp\ntwow64.h>
#include <ntexp\ntxcapi.h>
#include <ntexp\subprocesstag.h>
#include <ntexp\winsta.h>


#include <ntexp\ntstatus.h>
#include <ntexp\ntcommon.h>
#include <ntexp\ntdbg.h>
#include <ntexp\ntexapi.h>
#include <ntexp\ntgdi.h>
#include <ntexp\ntioapi.h>
#include <ntexp\ntkeapi.h>
#include <ntexp\ntldr.h>
#include <ntexp\ntlpcapi.h>
#include <ntexp\ntmisc.h>
#include <ntexp\ntmmapi.h>
#include <ntexp\ntnls.h>
#include <ntexp\ntobapi.h>
#include <ntexp\ntpebteb.h>
#include <ntexp\ntpfapi.h>
#include <ntexp\ntpnpapi.h>
#include <ntexp\ntpoapi.h>
#include <ntexp\ntpsapi.h>
#include <ntexp\ntregapi.h>
#include <ntexp\ntrtl.h>
#include <ntexp\ntsam.h>
#include <ntexp\ntseapi.h>
#include <ntexp\ntsmss.h>
#include <ntexp\nttmapi.h>
#include <ntexp\nttp.h>
#include <ntexp\ntwow64.h>
#include <ntexp\ntxcapi.h>
#include <ntexp\subprocesstag.h>
#include <ntexp\winsta.h>


// ----------------------------------------
//   API Epilog

#undef NTLIB_WIN_XP
#undef NTLIB_WIN_VISTA
#undef NTLIB_WIN_7
#undef NTLIB_WIN_8
#undef NTLIB_WIN_8_1
#undef NTLIB_WIN_10_TH1
#undef NTLIB_WIN_MAX
#undef NTLIB_WIN_VERSION 

#undef NTCALL
#undef NTDEF

#undef NATIVE_API

#undef NTDLL_API
#undef NTDLL_API_VOID

#undef LDR_API

#pragma pack(pop)

#ifdef __cplusplus
}
#endif
