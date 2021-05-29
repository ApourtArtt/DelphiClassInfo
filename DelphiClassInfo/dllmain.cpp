#include <Windows.h>
#include "ClassSearcher.h"

void print(ClassInfo cl)
{
	printf("%s (%d, 0x%x) : VTable addr : %x\n", cl.GetName().c_str(), cl.GetClassSize(), cl.GetClassSize(), cl.GetVTable());
}

DWORD WINAPI MainThread(HMODULE hModule)
{
	ClassSearcher::Initialize({
		"TObject",
	});

	print(ClassSearcher::GetClassInfoFromName("TObject"));

	fclose((FILE*)stdout);
	FreeConsole();
	FreeLibraryAndExitThread(hModule, 0);
	return 1;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		AllocConsole();
		freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
		CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)MainThread, hModule, 0, nullptr);
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
