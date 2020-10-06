#include <gtest/gtest.h>

// 1. Assertions
// ASSERT_XX
//        EQ / NE / LT / LE / GT / GE / TRUE / FALSE
//   - 단언문이 실패할 경우, 이후의 코드는 수행되지 않는다.
//   => 하나의 테스트 케이스 안에서 하나의 단언문 사용하는 것이 좋다.
//   => 문제점: 하나의 기능에 대해서, 많은 테스트 케이스를 작성해야 한다.

// EXPECT_XX
//        EQ / NE / LT / LE / GT / GE / TRUE / FALSE
//   - 단언문이 실패하더라도, 이후의 코드는 수행된다.
//   - 하나의 단언문이 실패한다면, 테스트의 결과는 실패이다.
//   => 죽은 단언문의 문제가 발생하지 않는다.
//   => 하나의 테스트 케이스 안에서 여러 값을 검증하는 용도로 사용할 수 있다.
TEST(GoogleTest, Sample1) {
	int expected = 42;

	int actual = 42;

	// ASSERT_EQ(expected, actual) << "Reason 1";
	// ASSERT_EQ(expected, actual) << "Reason 2";   // 죽은 단언문
	EXPECT_EQ(expected, actual) << "Reason 1";
	EXPECT_EQ(expected, actual) << "Reason 2";   // 죽은 단언문 X
}

#include <string>

// 2. 문자열
//   C-Style: const char* / char*
//   C++    : std::string
// 핵심: C 스타일의 문자열을 사용할 경우, 문자열 비교를 위해 다른 단언문을 사용해야 합니다.
//       EXPECT_STREQ/NE
//       EXPECT_STRCASEEQ/NE 
TEST(GoogleTest, Sample2) {
	std::string s1 = "hello";
	std::string s2 = "hello";

	EXPECT_EQ(s1, s2);

	const char* s3 = "Hello";
	const char* s4 = s2.c_str();

	// EXPECT_STREQ(s3, s4);  // !!
	EXPECT_STRCASEEQ(s3, s4);  // !!
}

// 3. 부동 소수점 - float / double
//   => 부동 소수점 비교를 위한 전용 단언 매크로가 존재합니다.
//   EXPECT_FLOAT_EQ / EXPECT_DOUBLE_EQ
//   EXPECT_FLOAT_NE / EXPECT_DOUBLE_NE
//
//   * 오차 범위를 직접 설정하고 싶다.
//   EXPECT_NEAR
TEST(GoogleTest, Sample3) {
	double a = 0.7;
	double b = 0.1 * 7;

	// EXPECT_EQ(a, b);
	EXPECT_DOUBLE_EQ(a, b);  // 4ULP's(오차)
	EXPECT_NEAR(a, b, 0.000000001);
}

// 4. 예외 테스트
//   : 비정상적인 상태에 도달했을 때, 기대했던 예외가 발생하는지 여부를 검증한다.
void IsValidFilename(const std::string& filename) {
	if (filename.empty()) {
		throw std::invalid_argument("filename should not empty!");
	}

	// ...
}

// 중요: 테스트케이스를 작성할 때, 잘못된 형태에서 테스트가 온전히 실패하는지 확인해야 합니다.

// 초기의 예외 검증을 지원하지 않는 단위 테스트 프레임워크에서 사용하는 방법입니다.
// => Google Test는 아래의 검증을 단언 매크로를 통해 제공하고 있습니다.
//    EXPECT_THROW: 기대한 예외가 발생하면 성공
//    EXPECT_ANY_THROW: 예외가 발생하면 성공
TEST(GoogleTest, Sample4) {
	// 테스트케이스의 변수명을 작성할 때, 의도가 나타나도록 작성하는 것은 테스트 케이스의 가독성에 좋습니다.
	std::string emptyFilename = "";
	
	EXPECT_THROW(IsValidFilename(emptyFilename), std::invalid_argument) << "빈 파일명을 전달하였을 때";
	EXPECT_ANY_THROW(IsValidFilename(emptyFilename)) << "빈 파일명을 전달하였을 때";
}

TEST(GoogleTest, Sample4_Bad) {
	std::string filename = "";

	try {
		IsValidFilename(filename);
		FAIL() << "기대한 예외가 발생하지 않았음.";
	} catch (std::invalid_argument& e) {
		SUCCEED();
	} catch (...) {
		FAIL() << "기대한 예외가 아닌 다른 예외가 발생하였음.";
	}
}

























