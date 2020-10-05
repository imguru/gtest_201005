
class Calculator {
public:
	double Display() { return 0; }

	void Enter(double v) {}
	void PressPlus() {}
	void PressMinus() {}
	void PressEquals() {}

	// Calculator(double v) {}
};

// #include "Calculator.h"
//-----------------------------------
// Test Fixture
//  정의: xUnit Test Pattern에서는 SUT를 실행하기 위해서 준비해야 하는 모든 것을 테스트 픽스쳐라고 합니다.
//        픽스쳐를 구성하는 모든 코드의 로직 부분을 "픽스쳐를 설치(Setup)한다" 라고 합니다.

// 픽스쳐 설치 방법 1.
//  1. Inline Fixture Setup
//    방법: 모든 픽스쳐 설치를 테스트 함수 안에서 수행한다.
//    장점: 픽스쳐를 설치하는 과정과 검증 로직이 테스트 함수 안에 존재하기 때문에, 인과관계를 쉽게 분석할 수 있다.
//    단점: 모든 테스트 코드 안에서 '코드 중복'이 발생한다.

#if 0
#include <gtest/gtest.h>

#define SPEC printf
TEST(CalculatorTest, PressPlus_2Plus2_Diplays4) {
	SPEC("PressPlus: 2 더하기 2를 하였을 때, 4의 결과가 나오는지 검증한다.\n");
	// Arrange - Fixture
	Calculator* calc = new Calculator;

	// Act
	calc->Enter(2);
	calc->PressPlus();
	calc->Enter(2);
	calc->PressEquals();

	// Assert
	ASSERT_EQ(calc->Display(), 4) << "2 + 2 하였을 때";
}

TEST(CalculatorTest, PlusTest) {
	// Arrange
	Calculator* calc = new Calculator;

	// Act
	calc->Enter(2);
	calc->PressPlus();
	calc->Enter(2);
	calc->PressEquals();

	// Assert
	if (calc->Display() == 4) {
		SUCCEED();
	} else {
		FAIL() << "2 + 2 하였을 때";
	}
}
#endif


#if 1
#include <gtest/gtest.h>

// 픽스쳐 설치 방법 
// 2. Delegate Setup(위임 설치)
//   방법: 픽스쳐 설치에 대한 코드를 별도의 테스트 유틸리티 함수를 통해 모듈화한다.
//         전역 함수로 제공하는 것이 아니라, CalculatorTest의 TestSuite 안에서 사용할 수 있도록 해야 한다.


//  1) CalculatorTest - TestSuite을 명시적으로 정의해야 합니다.
class CalculatorTest : public testing::Test {
// 3) TestCase 에서 사용할 다양한 테스트 유틸리티 함수를 제공하면 됩니다.
// 주의사항
//  - private으로 제공하면 안됩니다.
protected:
	Calculator* Create() { return new Calculator; }
	// Test Utility Method - Creation Method
};

//  2) 테스트 케이스를 만들 때, TEST 매크로가 아닌, TEST_F의 매크로를 통해 제공해야 합니다. 
#define SPEC printf
TEST_F(CalculatorTest, PressPlus_2Plus2_Diplays4) {
	SPEC("PressPlus: 2 더하기 2를 하였을 때, 4의 결과가 나오는지 검증한다.\n");
	// Arrange - Fixture
	Calculator* calc = Create();

	// Act
	calc->Enter(2);
	calc->PressPlus();
	calc->Enter(2);
	calc->PressEquals();

	// Assert
	ASSERT_EQ(calc->Display(), 4) << "2 + 2 하였을 때";
}

TEST_F(CalculatorTest, PlusTest) {
	// Arrange
	Calculator* calc = Create();

	// Act
	calc->Enter(2);
	calc->PressPlus();
	calc->Enter(2);
	calc->PressEquals();

	// Assert
	if (calc->Display() == 4) {
		SUCCEED();
	} else {
		FAIL() << "2 + 2 하였을 때";
	}
}
#endif






















