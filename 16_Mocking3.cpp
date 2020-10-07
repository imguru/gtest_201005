#include <gmock/gmock.h>

struct Element {};

class Foo {
public:
	virtual ~Foo() {}
	// 상속을 기반으로 모의 객체를 생성할 경우, 반드시 가상 소멸자를 제공해야 합니다.

	// 함수 오버로딩
	virtual int Add(Element x) {}
	virtual int Add(int times, Element x) {}
};

class MockFoo : public Foo {
public:
	// MOCK_METHOD(int, Add, (Element x), (override));
	
	// 아래 함수에 대해서만 행위 기반 검증을 수행하고, 위의 함수에 대해서는 부모의 구현을 이용하겠다.
	MOCK_METHOD(int, Add, (int times, Element x), (override));
	// Mock Method 의 매크로에 의해서, 다른 함수의 부모의 구현이 가려지는 현상
	//  => 컴파일 오류
	
	using Foo::Add;
};

TEST(MockTest, Sample) {
	MockFoo mock; // !!

	mock.Add(Element());  // 부모의 구현!!!!!
}

