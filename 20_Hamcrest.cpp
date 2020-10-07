// 20_Hamcrest.cpp
//   => 비교 표현의 확장 라이브러리
//   => Matcher라이브러리 시작
#include <gmock/gmock.h>

int foo() { return 200; }

using testing::Eq;
using testing::Gt;
using testing::Lt;
using testing::AllOf;

TEST(HamcrestTest, Sample1) {
	EXPECT_EQ(foo(), 100);
	// foo의 반환값이 10보다 크고 200보다 작아야 한다.
	int result = foo();
	EXPECT_TRUE(result > 10 && result < 200);

	// Hamcrest Style
	EXPECT_THAT(foo(), Eq(100));
	EXPECT_THAT(foo(), AllOf(Gt(10), Lt(200)));
}
