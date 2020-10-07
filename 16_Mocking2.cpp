
#include <gmock/gmock.h>

// 추상 클래스
class User {
public:
	virtual ~User() {}

	virtual void foo() = 0;
protected:
	virtual void goo() { printf("goo\n"); }
private:
	virtual void hoo() { printf("hoo\n"); }
};

// 1. Google Mock은 인터페이스 뿐 아니라 추상 클래스를 기반으로
//    모의 객체를 생성하는 것이 가능합니다.
// 2. Mocking을 수행하고자 하는 메소드의 접근 지정자에 상관없이,
//    무조건 public으로 만들어야 합니다.
// 3. Mocking 하고자 하는 메소드가 구현을 제공하지 않을 경우, 반드시 매크로를 작성해야 한다.
//    구현을 제공하고 있고, 행위기반검증을 수행할 필요가 없다면, 매크로를 작성할 필요가 없다.
// 4. 모의 객체를 통해 메소드를 호출할 경우, 실제 동작이 이루어지지 않는다.

class MockUser : public User {
public:
	MOCK_METHOD(void, foo, (), (override));
	MOCK_METHOD(void, goo, (), (override));
	MOCK_METHOD(void, hoo, (), (override));
};

TEST(MockTest, Sample) {
	MockUser mock;

	mock.goo();
	mock.hoo();
}






