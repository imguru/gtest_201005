
#include <string>

struct Time {
	virtual ~Time() {}

	virtual std::string GetCurrentTime() = 0;
};


class User {
	Time* time;
public:
	User(Time* p) : time(p) {}

	int Do() {
		std::string current = time->GetCurrentTime();
		if (current == "00:00") {
			return 42;
		}

		return 0;
	}
};

//-----------------
#include <gtest/gtest.h>


// Time이 00:00분일 때, User.Do()가 42값을 반환하는지 검증하고 싶다.
class StubTime : public Time {
public:
	std::string GetCurrentTime() override {
		return "00:00";
	}
};

TEST(UserTest, DoTest) {
	StubTime stub;
	User user(&stub);

	EXPECT_EQ(user.Do(), 42) << "00:00 일 때";
}
