
#include <iostream>
#include <string>

struct Time {
	virtual ~Time() {}

	virtual std::string GetCurrentTime() = 0;
};

class RealTime : public Time {
public:
	std::string GetCurrentTime() {
		time_t rawtime;
		struct tm* timeinfo;
		char buff[80];

		time(&rawtime);
		timeinfo = localtime(&rawtime);
		
		strftime(buff, sizeof(buff), "%H:%M", timeinfo);
		std::string str(buff);

		return str;
	}
};

class User {
	Time* time;
public:
	User(Time* p) : time(p) {}

	int Do() {
		//----
		std::string current = time->GetCurrentTime();
		std::cout << current << std::endl;
		if (current == "00:00") {
			return 42;
		}
		//----

		return 0;
	}
};

//-----------------
#include <gtest/gtest.h>

// 단위 테스트는 언제 어디서 어떻게 동작을 하든 동일한 결과가 나와야 한다.

class StubTime : public Time {
public:
	std::string GetCurrentTime() override {
		return "00:00";
	}
};

TEST(UserTest, DoTest) {
	// RealTime time;
	StubTime time;
	User user(&time);

	EXPECT_EQ(user.Do(), 42) << "00:00 일 때";
}

#if 0
// Time이 00:00분일 때, User.Do()가 42값을 반환하는지 검증하고 싶다.
class StubTime : public Time {
public:
	std::string GetCurrentTime() override {
		return "00:00";
	}
};

TEST(UserTest, DoTest) {
	RealTime stub;
	User user(&stub);

	EXPECT_EQ(user.Do(), 42) << "00:00 일 때";
}
#endif
