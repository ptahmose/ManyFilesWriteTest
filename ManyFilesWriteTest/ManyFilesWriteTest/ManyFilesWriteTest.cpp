// ManyFilesWriteTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Options.h"

void WriteFile(const wchar_t* filename, size_t size)
{
	void* pData = malloc(size);
	HANDLE h = CreateFile(
						filename,
						GENERIC_WRITE,
						FILE_SHARE_READ,
						NULL,
						CREATE_ALWAYS,
						FILE_ATTRIBUTE_NORMAL,
						NULL);
	DWORD numberOfBytesWritten;
	BOOL B = WriteFile(h, pData, size, &numberOfBytesWritten, NULL);
	CloseHandle(h);
	free(pData);
}

int _tmain(int argc, _TCHAR* argv[])
{
	CCmdLineOptions options;
	options.Parse(argc, argv);

	std::wstringstream stream;
	for (std::uint32_t i = 0; i < options.GetNumberOfFiles(); ++i)
	{
		stream << options.GetFolderName() << L"FILE#" << i + 1 << L".bin";
		WriteFile(stream.str().c_str(), options.GetSizeOfFile());
		stream.str(L"");
		stream.clear();
	}

	return 0;
}

