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

























