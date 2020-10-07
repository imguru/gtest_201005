
#include <gmock/gmock.h>

struct Foo {
public:
	virtual ~Foo() {}

	virtual void First() {}
	virtual void Second() {}
	virtual void Third() {}
	virtual void Forth() {}
};

struct MockFoo : public Foo {
public:
	MOCK_METHOD(void, First, (), (override));
	MOCK_METHOD(void, Second, (), (override));
	MOCK_METHOD(void, Third, (), (override));
	MOCK_METHOD(void, Forth, (), (override));
};

void foo(Foo* p) {
	p->First();
	p->Second();
	p->Third();
	p->Forth();
}

using testing::InSequence;
// 호출 순서 검증
//  : EXPECT_CALL은 기본적으로 호출 순서를 고려하지 않는다.
// 1. InSequence seq;
//    First -> Second -> Third -> Forth
TEST(MockTest, Sample1) {
	InSequence seq; // 생성되는 시점에, 호출 순서를 기록하기 위해 준비 작업 / 파괴되는 시점에 검증을 수행한다.
	MockFoo mock;	// Google Mock은 모의 객체가 파괴되는 시점에 검증을 수행한다.

	EXPECT_CALL(mock, Third());
	EXPECT_CALL(mock, Forth());
	EXPECT_CALL(mock, First());
	EXPECT_CALL(mock, Second());

	foo(&mock);
}

















