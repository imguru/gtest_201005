
// 19_동작검증(행위 기반 검증)

#include <gmock/gmock.h>

struct Foo {
	virtual ~Foo() {}

	virtual int Add(int a, int b) { return a + b; }
	virtual void Say(const char* message) = 0;
};

class MockFoo : public Foo {
public:
	MOCK_METHOD(int, Add, (int a, int b), (override));
	MOCK_METHOD(void, Say, (const char* message), (override));
};

// 동작 검증
// 1. 호출 여부 - EXPECT_CALL
void foo(Foo* p) {
	p->Add(10, 20);
	p->Say("hello");
}

TEST(MockTest, Sample1) {
	MockFoo mock;

	EXPECT_CALL(mock, Add(10, 20));
	EXPECT_CALL(mock, Say("hello"));

	foo(&mock);
}

// 2. 호출 횟수
//   => EXPECT_CALL(...).Times(N);
void goo(Foo* p) {
	p->Add(10, 20);
	p->Add(10, 20);
	p->Add(20, 30);
	p->Add(30, 20);
}

// 1) 인자 Matcher - Google Mock이 제공하는 강력한 기능
//  => Matching 규칙에 따라서, 호출 횟수가 달라진다.


// 2) 횟수 범위 지정(연속 매칭)
//    AtLeast: 적어도 N번 이상
//    AtMost: 최대 N번 이하
using testing::AtLeast;
using testing::AtMost;
using testing::AnyNumber;

TEST(MockTest, Sample2) {
	MockFoo mock;
	
	// EXPECT_CALL(mock, Add).Times(4);
	// 인자를 지정하지 않고, 사용할 경우 Add 전체 호출 횟수가 검증된다.
	
	// EXPECT_CALL(mock, Add(_, 20)).Times(AtMost(4));
	// EXPECT_CALL(mock, Add(20, 30));
	
	EXPECT_CALL(mock, Add).Times(AnyNumber());

	goo(&mock);
}

using testing::_;    // 모든 것에 매칭된다.
using testing::Lt;   // <
using testing::Gt;   // >
using testing::Le;   // <=
using testing::Ge;   // >=
using testing::Eq;   // ==
using testing::Ne;   // !=
using testing::NotNull; // != null
using testing::AllOf;  // &&
using testing::AnyOf;  // ||
using testing::Not;

void hoo(Foo* p) {
	p->Add(10, 20);
	p->Add(11, 21);
	p->Add(12, 22);
}

using testing::Matcher;

TEST(MockTest, Sample3) {
	MockFoo mock;
	
	// 첫번째 인자는 10보다 크거나 같고, 두번째 인자는 30보다 작은 함수
	// EXPECT_CALL(mock, Add(Ge(10), Lt(30))).Times(3);
	
	// 첫번째 인자는 10 <= x  && x <= 20 - AllOf(Ge(10), Le(20))
	// 두번째 인자는 x >= 20 || x < 0;  - AnyOf(Ge(20), Lt(0));
	// EXPECT_CALL(mock, Add(AllOf(Ge(10), Le(20)), AnyOf(Ge(20), Lt(0)))).Times(3);
	Matcher<int> firstArg = AllOf(Ge(10), Le(20));
	Matcher<int> secondArg = AnyOf(Ge(20), Le(0));

	// auto firstArg = AllOf(Ge(10), Le(20));
	// auto secondArg = AnyOf(Ge(20), Le(0));
	EXPECT_CALL(mock, Add(firstArg, secondArg)).Times(3);

	hoo(&mock);
}

