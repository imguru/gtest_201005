#include <gmock/gmock.h>

struct Foo {
	virtual ~Foo() {}

	virtual void Pure(int n) = 0;
	virtual int Concreate(const char* str) {
		printf("Foo - Concreate\n");
	}
};

class MockFoo : public Foo {
public:
	MOCK_METHOD(void, Pure, (int n), (override));
	MOCK_METHOD(int, Concreate, (const char* str), (override));

	// 반드시 부모의 기능을 이용하는 별도의 함수를 통해 처리해야 한다.
	int ConcreateImpl(const char* str) {
		return Foo::Concreate(str);
	}
};

TEST(MockFoo, FooTest) {
	MockFoo mock;
	ON_CALL(mock, Concreate).WillByDefault([&](const char* str) {
		// 부모의 기본 구현을 이용하도록 위임하고 싶다.
		// return mock.Concreate(str);
		// 문제점: 재귀로 동작한다.
		return mock.ConcreateImpl(str);
	});

	mock.Concreate("aaa");

}
