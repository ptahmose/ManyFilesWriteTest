#pragma once

class CCmdLineOptions
{
private:
	std::wstring folder;
	std::uint32_t numberOfFiles;
	std::uint32_t sizeOfFile;

public:
	CCmdLineOptions();
	bool Parse(int argc, wchar_t** argv);

	const std::wstring& GetFolderName() const { return this->folder; }
	std::uint32_t GetNumberOfFiles() const { return this->numberOfFiles; }
	std::uint32_t GetSizeOfFile() const { return this->sizeOfFile; }

private:
	static std::uint32_t ParseNumber(const wchar_t* s);
};
