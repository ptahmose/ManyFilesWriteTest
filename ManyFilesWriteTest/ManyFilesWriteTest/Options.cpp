#include "stdafx.h"
#include "Options.h"
#include "getopt.h"

using namespace std;

CCmdLineOptions::CCmdLineOptions()
{
}

bool CCmdLineOptions::Parse(int argc, wchar_t** argv)
{
	static const struct option long_options[] =
	{
		{ _T("dir"), required_argument, 0, _T('d') },
		{ _T("count"), required_argument, 0, _T('c') },
		{ _T("size"), required_argument, 0, _T('s') },
		{ _T("help"), no_argument, 0, _T('?') },
		{ 0, 0, 0, 0 }
	};

	for (;;)
	{
		int option_index;
		int c = getopt_long(argc, argv, L"d:c:s:", long_options, &option_index);
		if (c == -1)
		{
			break;
		}

		switch (c)
		{
		case _T('?'):
			//this->PrintUsage(log);
			return false;
		case _T('d'):
		{
			this->folder = optarg;
			wchar_t c = this->folder.at(this->folder.length() - 1);
			if (c != L'/' && c != '\\')
			{
				this->folder += L'\\';
			}

			break;
		}
		case _T('c'):
			this->numberOfFiles = ParseNumber(optarg);
			break;
		case _T('s'):
			this->sizeOfFile = ParseNumber(optarg);
			break;
		}
	}
}

static bool isEmpty(const wchar_t* s)
{
	for (;; ++s)
	{
		switch (*s)
		{
		case L'\0':
			return true;
		case L' ':
		case L'\t':
		case L'\n':
		case L'\r':
		case L'\f':
		case L'\v':
			continue;
		}

		return false;
	}
}

/*static*/std::uint32_t CCmdLineOptions::ParseNumber(const wchar_t* s)
{
	wchar_t* endPtr;
	uint32_t v = wcstoul(s, &endPtr, 10);
	if (endPtr == s || !isEmpty(endPtr))
	{
		throw std::invalid_argument("Invalid number.");
	}

	return v;
}