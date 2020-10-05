class Calculator {
public:
	double Display() { return 0; }

	void Enter(double v) {}
	void PressPlus() {}
	void PressMinus() {}
	void PressEquals() {}

	// Calculator(double v) {}
};

#include <gtest/gtest.h>
#define SPEC printf

// 방법 3. 암묵적 설치(Implicit Setup)
//  : 여러 테스트케이스에서 같은 픽스쳐 설치의 코드를 암묵적으로 호출되는 SetUp 함수에서 생성한다.
//  => 명시적인 Test Suite 클래스 정의가 필요합니다.
//  => xUnit Test Framework이 제공하는 기능입니다.
//  장점: 테스트 코드 중복을 제거하고, 꼭 필요하지 않은 상호작용을 캡슐화할 수 있다. 
//  단점: 픽스쳐 설치 코드가 테스트 함수 밖에 존재하기 때문에, 테스트 함수만으로 테스트 코드를 이해하기 어려울 수 있다.

class CalculatorTest : public testing::Test {
protected:
	Calculator* calc;

	// 각 테스트케이스를 수행하기 전에, 자동적으로 호출된다.
	void SetUp() override {
		printf("SetUp()\n");
		calc = new Calculator;
	}
};

TEST_F(CalculatorTest, PressPlus_2Plus2_Diplays4) {
	SPEC("PressPlus: 2 더하기 2를 하였을 때, 4의 결과가 나오는지 검증한다.\n");
	// Arrange - Fixture
	// Calculator* calc = new Calculator;

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
	// Calculator* calc = new Calculator;

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
