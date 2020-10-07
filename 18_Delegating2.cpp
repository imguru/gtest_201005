
// 18_Delegating.cpp

#include <gmock/gmock.h>

struct Foo {
	virtual ~Foo() {}

	virtual int Add(int a, int b) = 0;
	virtual int Sub(int a, int b) = 0;
};

class FakeFoo : public Foo {
public:
	int Add(int a, int b) override { 
		printf("FakeFoo - Add\n");
		return a + b; 
	}
	int Sub(int a, int b) override { 
		printf("FakeFoo - Add\n");
		return a - b; 
	}
};

class MockFoo : public Foo {
public:
	MOCK_METHOD(int, Add, (int a, int b), (override));
	MOCK_METHOD(int, Sub, (int a, int b), (override));

	void DelegateToFake() {
		ON_CALL(*this, Add).WillByDefault([this](int a, int b) {
			return fake.Add(a, b);
		});

		ON_CALL(*this, Sub).WillByDefault([this](int a, int b) {
			return fake.Sub(a, b);
		});
	}
private:
	FakeFoo fake;
};

using testing::NiceMock;

TEST(MockFoo, FooTest) {
	NiceMock<MockFoo> mock;
	mock.DelegateToFake();

	// EXPECT_CALL(mock, Add(10, 20));
	// EXPECT_CALL(mock, Sub(30, 20));

	EXPECT_EQ(mock.Add(10, 20), 30);
	EXPECT_EQ(mock.Sub(30, 20), 10);
	// printf("%d\n", mock.Add(10, 20));
	// printf("%d\n", mock.Sub(30, 20));
}



// Google Mock
//  => Test Double Framework
//    : Google Mock을 이용하면, 행위 기반 검증도 수행할 수 있지만,
//      Stub / Fake가 제공하는 기능도 구현이 가능하다.

// 테스트 대역(xUnit Test Pattern) 
//  1. Stub: 특수한 상황을 시뮬레이션 한다.
//  2. Fake: 아직 준비되지 않은 의존 객체로 인해 테스트가 불가능할 경우, 가벼운 객체로 대체해서 검증한다.
//  3. Spy: 검증하고자 하는 상태가 존재하지 않을 경우, 목격한 일을 기록해두었다가 검증에서 사용할 수 있는 기능을 제공한다.
//  4. Mock: 행위 기반 검증
