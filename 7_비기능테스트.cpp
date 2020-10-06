#include <gtest/gtest.h>
#include <unistd.h>

// 비기능 테스트
//  - 기능적인 동작에 대한 부분이 아니라, 성능이나 메모리 등의 비기능적인 부분을 검증하는 것.

void foo() {
	sleep(3);
}

// 방법 1.
//   : 암묵적으로 호출되는 SetUp() / TearDown()을 이용합니다.
//    => 기능적인 코드는 테스트 케이스를 통해 검증하고, 비기능(시간) 검증은 SetUp / TearDown 이 수행한다.
class FooTest : public testing::Test {
protected:
	time_t startTime;
	void SetUp() override {
		startTime = time(0);
	}

	void TearDown() override {
		time_t endTime = time(0);
		time_t duration = endTime - startTime;

		EXPECT_LE(duration, 2) << "시간 초과: " << duration << " 초가 걸렸습니다.";
	}
};

// 방법 2.
//   : 별도의 테스트 유틸리티 함수(사용자 정의 단언문)을 제공한다.
//   => Google Test는 단언문이 매크로의 형식으로 제공된다.
//   => 매크로 함수는 한번만 수행되는 로직을 do {} while(0) 

#define EXPECT_TIMEOUT(fn, limit)						    \
	do {                                                    \
	    time_t startTime = time(0);                         \
	    fn;                                                 \
	    time_t endTime = time(0);                           \
	    time_t duration = endTime - startTime;              \
	    EXPECT_LE(duration, limit) << "시간 초과: " << duration << " 초가 걸렸습니다."; \
	} while (0)

TEST(FooTest2, Foo2) {
	EXPECT_TIMEOUT(foo(), 2);

	// int duration;
}

TEST_F(FooTest, Foo) {
	foo();
}

// foo() 함수는 2초 안에 수행되어야 한다.
#if 0
TEST_F(FooTest, Foo) {
	time_t startTime = time(0);
	foo();
	time_t endTime = time(0);
	time_t duration = endTime - startTime;

	EXPECT_LE(duration, 2) << "시간 초과: " << duration << " 초가 걸렸습니다.";
}
#endif
