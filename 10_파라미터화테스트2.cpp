
bool IsPrime(int value) {
	for (int i = 2; i < value; ++i) {
		if (value % i == 0)
			return false;
	}

	return true;
}

#include <gtest/gtest.h>
#include <vector>

class PrimeTest : public testing::TestWithParam<int> {
protected:
	void SetUp() override {}
	void TearDown() override {}
	static void SetUpTestSuite() {}
	static void TearDownTestSuite() {}
};

int data[] = { 2, 3, 5, 7, 11, 13, 17, 19, 21 };

std::vector<int> GetParameterValues() {
	std::vector<int> v;
	// 데이터 파일에서 로드하는 코드를 작성하면 됩니다.
	v.push_back(2);
	v.push_back(3);
	v.push_back(5);

	return v;
}

// INSTANTIATE_TEST_SUITE_P(primeValues, PrimeTest, testing::ValuesIn(data));
// INSTANTIATE_TEST_SUITE_P(primeValues, PrimeTest, testing::ValuesIn(GetParameterValues()));
INSTANTIATE_TEST_SUITE_P(primeValues, PrimeTest, testing::Range(0, 10, 2));
													// [0, 10)

// Values:    나열
// ValuesIn:  정의되어 있는 컨테이너(배열, vector, list) 
//            함수도 지원합니다.
// Range(begin, end, step = 1);

TEST_P(PrimeTest, IsPrime) {
	EXPECT_TRUE(IsPrime(GetParam()));
}






