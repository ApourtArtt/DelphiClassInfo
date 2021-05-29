#pragma once
#include <string>
#include <map>
#include <vector>

class ClassInfo
{
public:
	ClassInfo() : size(0), addrPtrVTable(0), addrPtrName(0) {}
	ClassInfo(const std::string& Name, uint32_t Size, uintptr_t AddrPtrVTable, uintptr_t AddrPtrName)
		: name(Name)
		, size(Size)
		, addrPtrVTable(AddrPtrVTable)
		, addrPtrName(AddrPtrName)
	{}

	const std::string& GetName()		const { return name; }
	const uint32_t GetClassSize()		const { return size; }
	const uintptr_t GetAddressPtrVTable()	const { if (addrPtrVTable == 0) return 0; return addrPtrVTable; }
	const uintptr_t GetVTable()		const { if (addrPtrVTable == 0) return 0; return *(uintptr_t*)addrPtrVTable; }
	const uintptr_t GetAddressPtrName()	const { if (addrPtrName == 0) return 0; return addrPtrName + 1; }
	const uintptr_t GetNameAddress()	const { if (addrPtrName == 0) return 0; return *(uintptr_t*)(addrPtrName + 1); }

private:
	std::string name;
	uint32_t size;
	uintptr_t addrPtrVTable;
	uintptr_t addrPtrName;
};

class ClassSearcher
{
public:
	static bool Initialize(const std::vector<std::string>& ClassesName);
	static const ClassInfo& GetClassInfoFromName(const std::string& ClassName);

private:
	static std::string getPattern(const std::string& className);

	static std::string data;
	static std::map<std::string, ClassInfo> classesInfo;
};
