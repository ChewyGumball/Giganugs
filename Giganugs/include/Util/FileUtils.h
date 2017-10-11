#pragma once
#include <functional>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

#include "lib/SimpleFileWatcher/FileWatcher.h"

namespace Util::File
{
	std::string ReadWholeFile(std::string_view filename);

	std::vector<uint8_t> ReadBinary(const std::string& filename);

	void ProcessLines(const std::string& filename, std::function<void(const std::string_view&)> processor);
#if UNICODE
	void WatchForChanges(const std::string& filename, std::function<bool()> observer);
#endif
	void WatchForChanges(const FW::String& filename, std::function<bool()> observer);
	void MonitorFiles();
}
