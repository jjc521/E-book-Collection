// ImportFun.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <windows.h>

DWORD RVAToOffset(LPVOID lpBase,DWORD VirtualAddress)
{
	IMAGE_DOS_HEADER *dosHeader;
	IMAGE_NT_HEADERS *ntHeader;
	IMAGE_SECTION_HEADER *SectionHeader;
	int NumOfSections;
	dosHeader=(IMAGE_DOS_HEADER*)lpBase;
	ntHeader=(IMAGE_NT_HEADERS*)((BYTE*)lpBase+dosHeader->e_lfanew);
	NumOfSections=ntHeader->FileHeader.NumberOfSections;
	for (int i=0;i<NumOfSections;i++)
	{
		SectionHeader=(IMAGE_SECTION_HEADER*)((BYTE*)lpBase+dosHeader->e_lfanew+sizeof(IMAGE_NT_HEADERS))+i;
		if(VirtualAddress>SectionHeader->VirtualAddress&&VirtualAddress<SectionHeader->VirtualAddress+SectionHeader->SizeOfRawData)
		{
			DWORD AposRAV=VirtualAddress-SectionHeader->VirtualAddress;
			DWORD Offset=SectionHeader->PointerToRawData+AposRAV;
			return Offset;
		}
	}
	return 0;
}

int main(int argc, char* argv[])
{
	//打开文件
	HANDLE hFile=CreateFile(argv[1],GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if(hFile==INVALID_HANDLE_VALUE)
	{
		printf("CreateFile Failed\n");
		return 0;
	}
	//创建内存映射文件的内核对象
	HANDLE hMap=CreateFileMapping(hFile,NULL,PAGE_READONLY,NULL,NULL,NULL);
	if(hMap==INVALID_HANDLE_VALUE)
	{
		printf("CreateFileMapping Failed\n");
		return 0;
	}
	//把文件映射入内存
	LPVOID lpBase=MapViewOfFile(hMap,FILE_MAP_READ,0,0,0);
	if(lpBase==NULL)
	{
		printf("MapViewOfFile Failed\n");
		return 0;	
	}
	IMAGE_DOS_HEADER *dosHeader;
	IMAGE_NT_HEADERS *ntHeader;
	IMAGE_IMPORT_BY_NAME *ImportName;
	//lpBase由MapViewOfFile函数返回
	dosHeader=(IMAGE_DOS_HEADER*)lpBase;
	//检测是否是有效的PE文件
	if (dosHeader->e_magic!=IMAGE_DOS_SIGNATURE)
	{
		printf("This is not a windows file\n");
		return 0;
	}
	//定位到PE header
	ntHeader=(IMAGE_NT_HEADERS*)((BYTE*)lpBase+dosHeader->e_lfanew);
	if(ntHeader->Signature!=IMAGE_NT_SIGNATURE)
	{
		printf("This is not a win32 file\n");
		return 0;
	}
	//定位到导入表
	IMAGE_IMPORT_DESCRIPTOR *ImportDec=(IMAGE_IMPORT_DESCRIPTOR*)((BYTE*)lpBase+RVAToOffset(lpBase,ntHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress));
	while(ImportDec->FirstThunk)
	{
		//得到DLL文件名
		char *pDllName=(char*)((BYTE*)lpBase+RVAToOffset(lpBase,ImportDec->Name));
		printf("\nDLL文件名：%s\n",pDllName);
		//通过OriginalFirstThunk定位到PIMAGE_THUNK_DATA结构数组
		PIMAGE_THUNK_DATA pThunk=(PIMAGE_THUNK_DATA)((BYTE*)lpBase+RVAToOffset(lpBase,ImportDec->OriginalFirstThunk));
		while(pThunk->u1.Function)
		{
			//判断函数是用函数名导入的还是序号导入的
			if(pThunk->u1.Ordinal& IMAGE_ORDINAL_FLAG32)
			{
				//输出序号
				printf("从此DLL模块导出的函数的序号：%x\n",pThunk->u1.Ordinal&0xFFFF);
			}
			else
			{
				//得到IMAGE_IMPORT_BY_NAME结构中的函数名
				ImportName=(IMAGE_IMPORT_BY_NAME*)((BYTE*)lpBase+RVAToOffset(lpBase,(DWORD)pThunk->u1.AddressOfData));
				printf("从此DLL模块导出的函数的函数名：%s\n",ImportName->Name);
			}
			pThunk++;
		}
		ImportDec++;
	}
	UnmapViewOfFile(lpBase);
	CloseHandle(hMap);
	CloseHandle(hFile);
	return 0;
}
