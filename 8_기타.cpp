#include <gtest/gtest.h>
// 테스트케이스는 SUT의 protected / private에 접근하는 것이 불가능합니다.

#if 1
class User {
private:
	int age;
public:

	FRIEND_TEST(UserTest, AgeTest);
};
#endif

// Google Test 에서는 테스트 목적으로 제품 코드의 private에 접근할 수 있는 기능을 제공합니다.
//  => FRIEND_TEST
//    문제점: 제품 코드에 Google Test에 의존성이 생긴다.

// 의문: SUT의 기능이 private으로 되어 있어서, 단위 테스트를 작성할 수 없다.
//   => 제품 코드의 설계가 잘못된 것이다.
//   => 단위 테스트를 통해 검증하고자 하는 기능은 사용자가 외부에서 접근할 수 있는 함수를 기준으로 검증을 수행한다.
//   => private 메소드
//     : 로버트 C 마틴(클린코드) - private 메소드는 public 메소드의 가독성을 높이기 위해 사용해야 한다.
//                               friend- public 메소드를 검증할 때, 자연스럽게 검증이 수행될 수 있어야 한다.


// 2. private
TEST(UserTest, AgeTest) {
	User user;

	ASSERT_EQ(user.age, 42);
}


#if 0
// 1. protected
//  => '테스트 전용 하위 클래스'를 통해 접근 가능하다.
//    테스트 코드에서만 사용할 목적으로 만드는 SUT의 하위 클래스
//    자식 클래스에서 부모의 protected 필드에 접근하는 것이 가능하고, protected를 public으로 접근 변경하는 것도 가능합니다.
class TestUser : public User {
public:
	using User::age;    // 부모의 protected를 public으로 변경한다.
};


TEST(UserTest, AgeTest) {
	TestUser user;

	ASSERT_EQ(user.age, 42);
}
#endif
