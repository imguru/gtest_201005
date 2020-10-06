
#include <string>

// DAO: Database Access Object
class User {
	std::string name;
	int age;
public:
	User(const std::string& s, int n) : name(s), age(n) {}

	std::string GetName() const {
		return name;
	}

	int GetAge() const {
		return age;
	}
};

struct IDatabase {
	virtual ~IDatabase() {}

	virtual void SaveUser(const std::string& name, User* user) = 0;
	virtual User* LoadUser(const std::string& name) = 0;
};

class UserManager {
	IDatabase* db;
public:
	UserManager(IDatabase* p) : db(p) {}

	void Save(User* user) {
		std::string name = user->GetName();
		int age = user->GetAge();

		if (name.size() > 0 && age > 0) {
			db->SaveUser(name, user);
		}
	}

	User* Load(const std::string& name) {
		return db->LoadUser(name);
	}
};

#include <gtest/gtest.h>

// UserManager의 Save / Load의 기능을 검증하고자 한다.
// 아직 UserManager가 의존하는 Database의 구현이 준비되지 않았다.
//  => Fake Object Pattern
//
//  Fake Object Pattern
//  의도: 아직 준비되지 않은 의존 객체로 인해, 테스트 되지 않은 요구사항이 존재한다.
//  방법: 동일한 기능을 제공하는 가벼운 테스트 대역을 만들어서, 문제를 해결한다.
//      사용하는 경우
//      1. 준비되지 않았을 때
//      2. 의존하는 객체를 사용하기 어려울 때
//      3. 의존하는 객체가 너무 느려서, 느린 테스트의 문제가 발생할 때

#include <map>

class FakeDatabase : public IDatabase {
	std::map<std::string, User*> data;
public:
	void SaveUser(const std::string& name, User* user) override {
		data[name] = user;
	}

	User* LoadUser(const std::string& name) override {
		return data[name];
	}
};

// !!
bool operator==(const User& lhs, const User& rhs) {
	return lhs.GetName() == rhs.GetName() && lhs.GetAge() == rhs.GetAge();
}

TEST(UserManagerTest, SaveTest) {
	FakeDatabase fake;
	UserManager manager(&fake);
	std::string testName = "test_name";
	int testAge = 42;
	User user(testName, testAge);

	manager.Save(&user);
	User* actual = manager.Load(testName);

	EXPECT_EQ(user, *actual) << "저장한 User를 로드하였을 때";
	// 사용자 정의 객체에 대해서 단언문을 사용하고 있다.
	//  => EQ: user == *actual
	//     NE: user != *actual
	//
	//  : 사용자 정의 객체에 대해서 단언 매크로를 사용하기 위해서는 연산자 재정의 함수가 필요합니다.
}









