#include <gmock/gmock.h>

struct Foo {
	virtual ~Foo() {}
	virtual void Say() = 0;
};

class MockFoo : public Foo {
public:
	MOCK_METHOD(void, Say, (), (override));
};

void foo(Foo* p) {
	p->Say();
}

// 1. Naggy Mock - default
// mock에 대해서, mocking된 메소드가 호출되었는데, 검증을 수행하고 있지 않을 경우,
// 경고가 발생한다.
#if 0
GMOCK WARNING:
Uninteresting mock function call - returning directly.
    Function call: Say()
#endif

// 2. Nice Mock
//   모의객체를 행위 기반 검증이 아닌 다른 용도로 사용하고 싶다.
//   EXPECT_CALL을 지정하지 않아도, 경고가 발생하지 않길 원한다.

// 3. Strict Mock
//   행위 기반 검증을 수행하지 않는 Mock에 대해서, 테스트가 실패하도록 만들고 싶다.
//   => 단위 테스트를 작성하는 비용이 증가할 수 있다.
//      테스트를 통과하기 위한 기준이 높아진다.

using testing::NaggyMock;
using testing::NiceMock;
using testing::StrictMock;

TEST(MockTest, Sample) {
	// NiceMock<MockFoo> mock;
	StrictMock<MockFoo> mock;

	// EXPECT_CALL(mock, Say());

	// mock.Say();
	foo(&mock);
}



