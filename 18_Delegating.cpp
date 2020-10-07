
// 18_Delegating.cpp

#include <gmock/gmock.h>

struct Foo {
	virtual ~Foo() {}

	virtual int Add(int a, int b) = 0;
	virtual int Sub(int a, int b) = 0;
};


class MockFoo : public Foo {
public:
	MOCK_METHOD(int, Add, (int a, int b), (override));
	MOCK_METHOD(int, Sub, (int a, int b), (override));
};

// Google Mock을 이용해서, Mocking된 메소드에 대해서,
// 실제 구현 객체에게 해당 메소드의 동작을 위임하는 것이 가능하다.

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

// 위임
// ON_CALL
//    => .WillByDefault

TEST(MockFoo, FooTest) {
	MockFoo mock;
	FakeFoo fake;
	// Delegate - 위임 기능
	ON_CALL(mock, Add).WillByDefault([&](int a, int b) {
		return fake.Add(a, b);
	});
	ON_CALL(mock, Sub).WillByDefault([&](int a, int b) {
		return fake.Sub(a, b);
	});

	EXPECT_CALL(mock, Add(10, 20));
	EXPECT_CALL(mock, Sub(30, 20));

	printf("%d\n", mock.Add(10, 20));
	printf("%d\n", mock.Sub(30, 20));
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
