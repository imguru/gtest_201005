#include <string>

class FileSystem {
public:
	virtual bool IsValid(const std::string& name) {
		// ...
		return false;
	}

};

// 아래 단위 테스트의 문제점
//  : 협력 객체의 결과에 따라 단위 테스트의 결과가 변화된다.
//  결함 국소화: 단위 테스트가 실패하였을 때, 실패의 지점을 바로 알아낼 수 있다. 

class Logger {
public:
	// hello.log
	//  요구사항: 확장자를 제외한, 파일의 이름이 5글자 이상이어야 한다.
	bool IsValidLogFilename(const std::string& filename) {
		//---------- CUT(테스트 대상 코드 영역)
		size_t index = filename.find_last_of(".");
		std::string name = filename.substr(0, index);

		if (name.size() < 5) {
			return false;
		}
		//---------- CUT(테스트 대상 코드 영역)

		FileSystem* fs = new FileSystem;
		return fs->IsValid(filename);
	}
};

#include <gtest/gtest.h>

// 1. filename이 다섯글자 이상일 때, true를 반환하는지를 검증한다.
TEST(LoggerTest, IsValidFilename_NameLoggerThan5Chars_ReturnsTrue) {
	Logger logger;
	std::string validFilename = "valid.log";

	EXPECT_TRUE(logger.IsValidLogFilename(validFilename)) << "파일명이 다섯글자 이상일 때";
}

// 2. filename이 다섯글자 미만일 때, false를 반환하는지를 검증한다.
TEST(LoggerTest, IsValidFilename_NameShorterThan5Chars_ReturnsFalse) {
	Logger logger;
	std::string invalidFilename = "bad.log";

	EXPECT_FALSE(logger.IsValidLogFilename(invalidFilename)) << "파일명이 다섯글자 미만일 때";
}















