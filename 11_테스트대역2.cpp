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

// 아래의 Logger는 테스트 대역을 적용할 수 없는 설계입니다.
//  : 제품 코드가 테스트 대역을 적용할 수 있어야 합니다.
//  
//  협력 객체 
//     강한 결합: 협력 객체의 구체적인 타입에 의존하는 것
//     약한 결합: 협력 객체의 구체적인 타입에 의존하는 것이 아니라, 인터페이스나 추상 클래스를 통해 이용하는 것
//             => 교체 가능한 느슨한 디자인이 적용되어 있다.

// 1. 협력 객체의 인터페이스를 정의한다.
// 2. 협력 객체를 이용할 때, 인터페이스 타입을 이용해야 한다.
// 3. 협력 객체를 직접 생성하면, 강한 결합이 형성된다.
//    new는 구체적인 타입의 정보가 필요합니다.
//    => 외부에서 생성해서, 전달받아야 합니다.
//     : DI(Dependency Injection)
//      1) 생성자 주입: 협력 객체가 필수적일 때
//      2) 메소드 주입: 협력 객체가 선택적일 때
//      문제점: 보일러플레이트가 발생합니다.
//          B* b = new B;
//          C* c = new C;
//          A a(b, c);
//          => DI의 보일러플레이트를 제거하기 위해, DI Framework를 사용합니다.
//             - 러닝 커브가 있습니다.
//          Java / Android => Dagger2(Google)
//          C++ => https://github.com/google/fruit

// 리팩토링을 할 때, 기존의 객체 사용법과 동일하게 유지하는 것이 중요하다.
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

		// IFileSystem* fs = new FileSystem;
		return fs->IsValid(filename);
	}
};

#include <gtest/gtest.h>

// Stub
class TestFileSystem : public IFileSystem {
public:
	bool IsValid(const std::string& filename) override { 
		return true; 
	}
};


// 1. filename이 다섯글자 이상일 때, true를 반환하는지를 검증한다.
TEST(LoggerTest, IsValidFilename_NameLoggerThan5Chars_ReturnsTrue) {
	TestFileSystem fs;
	Logger logger(&fs);
	std::string validFilename = "valid.log";

	EXPECT_TRUE(logger.IsValidLogFilename(validFilename)) << "파일명이 다섯글자 이상일 때";
}

// 2. filename이 다섯글자 미만일 때, false를 반환하는지를 검증한다.
TEST(LoggerTest, IsValidFilename_NameShorterThan5Chars_ReturnsFalse) {
	TestFileSystem fs;
	Logger logger(&fs);
	std::string invalidFilename = "bad.log";

	EXPECT_FALSE(logger.IsValidLogFilename(invalidFilename)) << "파일명이 다섯글자 미만일 때";
}

// Test Double(테스트 대역)
//  xUnit Test Pattern
//   1) Test Stub     => Stub
//   2) Fake Object   => Fake
//   3) Test Spy      => Spy
//   4) Mock Object   => Mock

