#include <gmock/gmock.h>

template <typename T>
struct StackInterface {
	virtual ~StackInterface() {}

	virtual int GetSize() const = 0;
	virtual void Push(const T& x) = 0;
};

// GoogleMock은 Template에 대한 Mocking도 가능합니다.
template <typename T>
class MockStack : public StackInterface<T> {
public:
	MOCK_METHOD(int, GetSize, (), (override, const));
	MOCK_METHOD(void, Push, (const T& x), (override));
};

TEST(MockTest, Sample) {
	MockStack<int> mock;

	mock.GetSize();  // !
	mock.Push(10);   // !!
}

