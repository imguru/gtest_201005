
// 2_3A.cpp
// : 단위 테스트를 구성하는 방법.

// SUT(System Under Test): 테스트 대상 시스템
//  = CUT(Class Under Test) / CUT(Code Under Test): 테스트 대상 코드(클래스)
class Calculator {
public:
	double Display() { return 0; }

	void Enter(double v) {}
	void PressPlus() {}
	void PressMinus() {}
	void PressEquals() {}
};

// #include "Calculator.h"
//-----------------------------------

#include <gtest/gtest.h>
// TestSuite -> CalculatorTest / CalculatorSpec

// 3A
// 1. Arrange: 객체를 생성하고, 필요한 경우 설정하고 준비한다.
// 2. Act: 객체의 작용을 가한다.
// 3. Assert: 기대하는 바를 단언한다.

// 단위 테스트 코드의 품질 - Effective Unit Testing
// 1. 가독성
// 2. 유지보수성
// 3. 신뢰성
//
// - 테스트케이스의 이름을 통해, 해당 테스트가 어떤 동작을 수행하는지 알 수 있도록 해야 한다.
//  => 예) 테스트대상함수_시나리오_기대값
//  => 모든 테스트 케이스는 자신의 동작에 대한 부분을 로깅하자.

// - 테스트케이스의 코드 안에서 흐름 제어 구문을 사용하지 않는 것이 좋다.
//   : 조건문, 반복문, 예외처리 등의 구문
//   => 테스트 유틸리티 함수를 이용해서, 별도의 함수나 클래스로 분리해서 사용해야 한다.
//   => 단언 매크로 함수를 이용하면 된다.


#define SPEC printf

TEST(CalculatorTest, PressPlus_2Plus2_Diplays4) {
	SPEC("PressPlus: 2 더하기 2를 하였을 때, 4의 결과가 나오는지 검증한다.\n");
	// Arrange
	Calculator* calc = new Calculator;

	// Act
	calc->Enter(2);
	calc->PressPlus();
	calc->Enter(2);
	calc->PressEquals();

	// Assert
	ASSERT_EQ(calc->Display(), 4) << "2 + 2 하였을 때";

	// calc->Display()의 값이 4이어야 한다.
	#if 0
	if (calc->Display() == 4) {
		SUCCEED();
	} else {
		FAIL() << "2 + 2 하였을 때";
	}
	#endif
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















