
bool IsPrime(int value) {
	for (int i = 2; i < value; ++i) {
		if (value % i == 0)
			return false;
	}

	return true;
}

#include <gtest/gtest.h>

// 파라미터화 테스트(Parameterized Test Pattern)
//  : xUnit Test Framework이 제공하는 기능입니다.
//   - 입력 데이터를 바꿔가면서, 수차례 반복 검사하는 테스트에서 코드 중복을 없애는 테스트 방법.

// 1. TestSuite - testing::TestWithParam<T>
class PrimeTest : public testing::TestWithParam<int> {
protected:
	void SetUp() override {}
	void TearDown() override {}
	static void SetUpTestSuite() {}
	static void TearDownTestSuite() {}
};

// 2. DataSet 정의 - 전역 변수
//  => GoogleTest 매크로를 제공하고 있습니다.
// INSTANTIATE_TEST_SUITE_P(변수명, TestSuite
// 1.10 이전 - INSTANTIATE_TEST_CASE_P
INSTANTIATE_TEST_SUITE_P(primeValues, PrimeTest, 
	testing::Values(2, 3, 5, 7, 11, 13, 17, 19, 21));

// 3. 해당 데이터를 이용하는 테스트 케이스를 작성하면 됩니다.
// TEST    - 암묵적인 Test Suite
// TEST_F  - 명시적인 Test Suite
// TEST_P  - 파라미터화 Test Suite
// => 입력 데이터 셋의 크기 만큼 아래의 테스트 케이스가 수행됩니다.
TEST_P(PrimeTest, IsPrime) {
	EXPECT_TRUE(IsPrime(GetParam()));
}

#if 0
int data[] = { 2, 3, 5, 7, 11, 13, 17, 19, 21 };
TEST(PrimeTest, IsPrime) {
	// 1. 반복문을 통해 검증한다.
	//   : 테스트케이스 코드 안에서 흐름제어 구문을 사용하지 않는 것이 좋다.
	for (int i = 0 ; i < sizeof(data) / sizeof(data[0]) ; ++i) {
		EXPECT_TRUE(IsPrime(data[i]));
	}
}

TEST(PrimeTest, IsPrime2) {
	// 2. 나열
	//   : 데이터가 많을 경우, 코드 중복으로 인한 유지보수에 문제가 있다.
	EXPECT_TRUE(IsPrime(2));
	EXPECT_TRUE(IsPrime(3));
	EXPECT_TRUE(IsPrime(5));
	EXPECT_TRUE(IsPrime(7));
	EXPECT_TRUE(IsPrime(11));
	EXPECT_TRUE(IsPrime(13));
	EXPECT_TRUE(IsPrime(17));
	EXPECT_TRUE(IsPrime(19));
	// EXPECT_TRUE(IsPrime(21));
}
#endif
