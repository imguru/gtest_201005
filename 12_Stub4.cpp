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
#include <gmock/gmock.h>

using testing::Return;
using testing::NiceMock;

class MockTime : public Time {
public:
	MOCK_METHOD(std::string, GetCurrentTime, (), (override));
};

TEST(UserTest, DoTest) {
	NiceMock<MockTime> time;
	User user(&time);
	ON_CALL(time, GetCurrentTime()).WillByDefault(Return("00:00"));

	EXPECT_EQ(user.Do(), 42) << "00:00 일 때";
}
