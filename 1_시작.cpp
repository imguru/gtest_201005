
// 1_시작.cpp

#include <gtest/gtest.h>


// 테스트를 만드는 방법
// 1.10 이전
// TestCase
//    Test
//    Test

// 1.10 이후
// TestSuite: 동일한 픽스쳐를 가지는 테스트케이스의 집합
//    TestCase
//    TestCase
//
//  1) 테스트케이스에서 아무것도 수행하지 않으면, 성공한다.
//  2) 작성 중인 테스트케이스는 반드시 실패하도록 해야 한다.
//  3) FAIL() 매크로 함수를 통해, 명시적으로 테스트를 실패할 수 있습니다.
//  4) 테스트가 실패할 경우, 실패의 원인을 지정해야 합니다.

// 테스트케이스를 만드는 방법
// - TEST(TestSuiteName, TestCaseName)

// TestSuiteName.TestCase1
TEST(TestSuiteName, TestCase1) {
	SUCCEED();
}

// TestSuiteName.TestCase2
TEST(TestSuiteName, TestCase2) {
	SUCCEED();
}

// SampleTest.Foo
TEST(SampleTest, Foo) {
	FAIL() << "작성 중입니다.";
}











