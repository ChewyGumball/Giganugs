#include "Util/FileUtils.h"
#include "Util/StringUtils.h"

#include <assert.h>

#include <algorithm>
#include <fstream>
#include <sstream>

#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace {
	FW::FileWatcher* fileWatcher = new FW::FileWatcher(); 
	
	class UpdateListener : public FW::FileWatchListener
	{
	private:
		std::unordered_map<FW::String, std::vector<std::function<bool()>>> watchers;
		std::unordered_set<FW::String> watchedDirectories;

		std::unordered_set<std::function<bool()>*> duplicateChanges;
	public:
		UpdateListener()
		{}

		void handleFileAction(FW::WatchID watchID, const FW::String& directory, const FW::String& filename, FW::Action action)
		{
			if (action == FW::Action::Modified)
			{
				FW::String fullPath = directory + filename;
				if (watchers.count(fullPath) > 0)
				{
					for (auto& observer : watchers[fullPath]) {
						duplicateChanges.insert(&observer);
					}
				}
			}
		}

		void postProcess() {
			for (auto it = duplicateChanges.begin(); it != duplicateChanges.end();) {
				if ((**it)()) {
					it = duplicateChanges.erase(it);
				}
				else {
					++it;
				}
			}
		}

		void add(FW::String filename, std::function<bool()> observer)
		{
			watchers[filename].push_back(observer);
			FW::String filepath = filename.substr(0, filename.find_last_of(STRING_LITERAL("/\\")) + 1);
			if (watchedDirectories.count(filepath) == 0)
			{
				fileWatcher->addWatch(filepath, this);
				watchedDirectories.insert(filepath);
			}
		}
	} FileUpdateListener;
}

namespace Util::File
{
	std::string ReadWholeFile(std::string_view filename)
	{
		std::string filenameString(filename);
		std::ifstream file(filenameString, std::ios::in | std::ios::binary);
		if (!file) {
			assert(false); // Couldn't read file
		}

		std::ostringstream fileContents;
		fileContents << file.rdbuf();
		file.close();
		return fileContents.str();
	}

	std::vector<uint8_t> ReadBinary(const std::string& filename)
	{
		std::ifstream file(filename, std::ios::in | std::ios::binary);
		if (!file) {
			assert(false); // Couldn't read file
		}

		file.seekg(0, file.end);
		size_t length = file.tellg();
		file.seekg(0, file.beg);

		std::vector<uint8_t> data(length);
		file.read(reinterpret_cast<char*>(data.data()), length);

		return data;
	}

	void ProcessLines(const std::string& filename, std::function<void(const std::string_view&)> processor)
	{
		std::string file = ReadWholeFile(filename);
		size_t start = 0;
		size_t end = 0;
		size_t actualEnd = file.size();

		while (end != actualEnd)
		{
			if (file[end] == '\r' && end + 1 != actualEnd && file[end + 1] == '\n')
			{
				std::string_view line(&file[start], end - start);
				processor(line);
				start = end + 2;
				end += 1;
			}
			else if (file[end] == '\n')
			{
				std::string_view line(&file[start], end - start);
				processor(line);
				start = end + 1;
			}
			end = end + 1;
		}
	}

#if UNICODE
	void WatchForChanges(const std::string & filename, std::function<bool()> observer)
	{
		WatchForChanges(std::wstring(filename.begin(), filename.end()), observer);
	}
#endif

	std::vector<uint8_t> ReadPNG(const std::string & filename)
	{
		return std::vector<uint8_t>();
	}

	void WatchForChanges(const FW::String& filename, std::function<bool()> observer)
	{
		FileUpdateListener.add(filename, observer);
	}
	void MonitorFiles()
	{
		fileWatcher->update();
		FileUpdateListener.postProcess();
	}
}
