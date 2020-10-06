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

	int actual = 10;

	// ASSERT_EQ(expected, actual) << "Reason 1";
	// ASSERT_EQ(expected, actual) << "Reason 2";   // 죽은 단언문
	EXPECT_EQ(expected, actual) << "Reason 1";
	EXPECT_EQ(expected, actual) << "Reason 2";   // 죽은 단언문 X
}
