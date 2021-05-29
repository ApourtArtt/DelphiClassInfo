#include "ClassSearcher.h"
#include <iostream>
#include <Windows.h>
#include <Psapi.h>

std::string ClassSearcher::data;
std::map<std::string, ClassInfo> ClassSearcher::classesInfo;

bool ClassSearcher::Initialize(const std::vector<std::string>& ClassesName)
{
	MODULEINFO mInfo = { 0 };
	HMODULE hModuleExe = GetModuleHandle(NULL);
	if (hModuleExe == 0) return false;
	GetModuleInformation(GetCurrentProcess(), hModuleExe, &mInfo, sizeof(MODULEINFO));
	DWORD base = (DWORD)mInfo.lpBaseOfDll;
	DWORD size = (DWORD)mInfo.SizeOfImage;
	data.resize(size);
	memcpy(data.data(), (char*)base, size);

	for (auto className : ClassesName)
	{
		std::string pattern = getPattern(className);
		int pos = data.find(pattern);
		if (pos == std::string::npos)
		{
			std::cout << "wtf";
			return false;
		}
		int addr = base + pos;

		for (int32_t i = addr - 4;; i--)
		{
			if (i < base)
			{
				std::cout << "wtf";
				return false;
			}
			if (*(int32_t*)i == addr)
			{
				classesInfo.emplace(className, ClassInfo(className, *(int32_t*)(i + 4), i - 0x20, *(int32_t*)i));
				break;
			}
		}
	}
}

const ClassInfo ClassSearcher::GetClassInfoFromName(const std::string& ClassName)
{
	return classesInfo[ClassName];
}

std::string ClassSearcher::getPattern(const std::string& className)
{
	std::string pattern;
	pattern += className.size();
	pattern += className;
	return pattern;
}
