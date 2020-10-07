#include <string>

struct IFileSystem {
	virtual ~IFileSystem() {}

	virtual bool IsValid(const std::string& name) = 0;
};

class FileSystem : public IFileSystem {
public:
	bool IsValid(const std::string& name) override {
		// ...
		return false;
	}
};

class Logger {
	IFileSystem* fs;
public:
	Logger(IFileSystem* p = nullptr) : fs(p) {
		if (fs == nullptr) {
			fs = new FileSystem;
		}
	}

	bool IsValidLogFilename(const std::string& filename) {
		//---------- CUT(테스트 대상 코드 영역)
		size_t index = filename.find_last_of(".");
		std::string name = filename.substr(0, index);

		if (name.size() < 5) {
			return false;
		}
		//---------- CUT(테스트 대상 코드 영역)

		return fs->IsValid(filename);
	}
};

#include <gmock/gmock.h>

class MockFileSystem : public IFileSystem {
public:
	MOCK_METHOD(bool, IsValid, (const std::string& filename), (override));
};

using testing::Return;
using testing::NiceMock;

TEST(LoggerTest, IsValidFilename_NameLoggerThan5Chars_ReturnsTrue) {
	NiceMock<MockFileSystem> mock;
	Logger logger(&mock);
	std::string validFilename = "valid.log";
	ON_CALL(mock, IsValid(validFilename)).WillByDefault(Return(true));

	EXPECT_TRUE(logger.IsValidLogFilename(validFilename)) << "파일명이 다섯글자 이상일 때";
}

TEST(LoggerTest, IsValidFilename_NameShorterThan5Chars_ReturnsFalse) {
	NiceMock<MockFileSystem> mock;
	Logger logger(&mock);
	std::string invalidFilename = "bad.log";
	ON_CALL(mock, IsValid(invalidFilename)).WillByDefault(Return(true));

	EXPECT_FALSE(logger.IsValidLogFilename(invalidFilename)) << "파일명이 다섯글자 미만일 때";
}
