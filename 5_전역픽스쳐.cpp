// xUnit Test Framework의 공통의 기능이 아닌, Google Test의 고유의 기능입니다.
// 전역 픽스쳐(Global Fixture)
//  => 프로그램이 시작할 때, 호출되는 SetUp() / 프로그램이 종료하기 전에 호출되는 TearDown()을 정의합니다.


#include <gtest/gtest.h>

TEST(SampleTest1, Foo) {}
TEST(SampleTest2, Goo) {}
TEST(SampleTest3, Hoo) {}

// Google Test Framework에 등록되는 객체는 반드시 new를 통해 생성되어야 합니다.
class MyTestEnvironment : public testing::Environment {
public:
	~MyTestEnvironment() { printf("파괴\n"); }

	void SetUp() override {
		printf("프로그램 초기화 작업..\n");
	}

	void TearDown() override {
		printf("프로그램 종료 작업..\n");
	}
};

// 전역 픽스쳐 설정 방법
// 1. 전역 변수: main을 직접 제공하지 않을 때
//  전역 변수는 프로그램(main)이 시작되기 전에, 초기화 됩니다.
//  전역 변수의 초기화 루틴을 이용해서, 함수를 호출합니다.

// testing::Environment* env = testing::AddGlobalTestEnvironment(new MyTestEnvironment);
// 위 처럼 사용하는 것은 권장되지 않습니다.
// 전역 픽스쳐를 설정해야 한다면, main을 직접 제공하는 것이 좋습니다.

// 2. main 함수: main을 직접 제공할 때
int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);

	AddGlobalTestEnvironment(new MyTestEnvironment);

	return RUN_ALL_TESTS();
}















