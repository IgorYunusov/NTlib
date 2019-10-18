#include <NTLib.h>

/*TODO:
- Call original main, wmain, WinMain etc. from these stubs
- Check how security check works
*/

#ifdef __cplusplus
extern "C" {
#endif

// DLL entry

BOOL WINAPI _DllMainCRTStartup(HANDLE  hDllHandle, DWORD dwReason, LPVOID lpreserved)
{
    return 0;
}

// Console entry

extern int main(int argc, char* argv[]);
extern int wmain(int argc, wchar_t* argv[]);

#if defined(_M_IX86)
#pragma comment(linker, "/alternatename:_main=_unspecified_main")
#pragma comment(linker, "/alternatename:_wmain=_unspecified_main")
#else
#pragma comment(linker, "/alternatename:main=unspecified_main")
#pragma comment(linker, "/alternatename:wmain=unspecified_main")
#endif

int unspecified_main(int argc, void* argv)
{
    return 0;
}

int mainCRTStartup(void)
{
    return main(0, 0);
}

int wmainCRTStartup(void)
{
    return wmain(0, 0);
}

// Windows app entry

int WinMainCRTStartup(void)
{
    return 0;
}

int wWinMainCRTStartup(void)
{
    return 0;
}

#ifdef __cplusplus
};
#endif
