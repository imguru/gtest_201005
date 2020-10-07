
#include <gmock/gmock.h>

struct Foo {
	virtual ~Foo() {}

	virtual int GetValue() = 0;
};

class MockFoo : public Foo {
public:
	MOCK_METHOD(int, GetValue, (), (override));
};

using testing::Return;
using testing::NiceMock;

TEST(FooTest, Sample) {
	NiceMock<MockFoo> mock;
	// 1. Lambda
	ON_CALL(mock, GetValue()).WillByDefault([] {
		return 42;
	});

	// 2. Return / Throw ...
	ON_CALL(mock, GetValue()).WillByDefault(Return(42));

	printf("%d\n", mock.GetValue());
	printf("%d\n", mock.GetValue());
	printf("%d\n", mock.GetValue());
	printf("%d\n", mock.GetValue());
}
