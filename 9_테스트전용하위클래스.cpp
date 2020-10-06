#include <stdio.h>

class Engine {
public:
	Engine() { printf("Engine()\n"); }
	virtual ~Engine() {}

	virtual void Start() {
		printf("Engine Start\n");
	}
};

class Car {
	Engine* engine;
public:
	Car(Engine* p) : engine(p) {}

	void Go() {
		//....
		// engine->Start();
		//....
	}
};

//----------------------------------
#include <gtest/gtest.h>

// 문제점: Engine 객체에서 Start 되었는지에 대한 상태가 존재하지 않기 때문에, 검증을 수행할 수 없다.
// 해결방법
//   테스트 전용 하위 클래스 패턴
//     제약: 사용하는 함수가 가상함수로 제공되어 있어야 한다.
//     테스트 하고자 하는 클래스가 테스트를 위한 기능을 제공하고 있지 않다면,
//     테스트 코드 안에서 자식 클래스를 통해, 해당 기능을 제공한다.
//
//     1) SUT의 protected 필드 / 메소드에 접근하고자 할 때
//     2) SUT의 가상함수가 제대로 호출되었는지 여부를 검증하고자 할 때

class TestEngine : public Engine {
	bool isStart;
public:
	TestEngine() : isStart(false) {}

	void Start() override {
		Engine::Start();         // 부모의 기능을 그대로 수행한다.
		isStart = true;
	}

	bool IsStart() const { return isStart; }
};

// Car 객체에 Go가 호출되었을 때, Engine의 Start가 제대로 호출되었는지 여부를 검증하고 싶다.
class CarTest : public testing::Test {};

TEST_F(CarTest, GoTest) {
	TestEngine engine;
	Car car(&engine);

	car.Go();

	EXPECT_TRUE(engine.IsStart()) << "Car객체가 Go를 호출하였을 때";
}




#if 0
TEST_F(CarTest, GoTest) {
	Engine engine;
	Car car(&engine);

	car.Go();
}
#endif
























