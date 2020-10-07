
#include <gmock/gmock.h>

// ON_CALL(...).WillByDefault(...) : Delegate -> Stub / Fake


struct Foo {
	virtual ~Foo() {}
	
	virtual int GetValue() const = 0;
};

class MockFoo : public Foo {
public:
	MOCK_METHOD(int, GetValue, (), (override, const));
};

// EXPECT_CALL(동작 검증)도 Delegate 기능을 제공하고 있습니다.
//   .WillOnce
//   .WillRepeatedly

// 동작 검증과 위임에 대한 기능을 한번에 구현 가능하다.
TEST(MockTest, Sample) {
	MockFoo mock;

	// EXPECT_CALL 단독 사용 - 1번
	// EXPECT_CALL / WillOnce N번 - N번
	// (EXPECT_CALL / WillOnce) => N번  WillRepeatedly - atLeast N번

	EXPECT_CALL(mock, GetValue)
		.WillOnce([] {
			return 10;
		})
		.WillOnce([] {
			return 20;
		})
		.WillOnce([] {
			return 30;
		})
		.WillOnce([] {
			return 40;
		})
		.WillRepeatedly([] {
			return 50;
		});

	printf("%d\n", mock.GetValue()); // 10
	printf("%d\n", mock.GetValue()); // 20
	printf("%d\n", mock.GetValue()); // 30
	printf("%d\n", mock.GetValue()); // 40
	printf("%d\n", mock.GetValue()); // 50
	printf("%d\n", mock.GetValue()); // 50
	printf("%d\n", mock.GetValue()); // 50
	printf("%d\n", mock.GetValue()); // 50
	printf("%d\n", mock.GetValue()); // 50
}
