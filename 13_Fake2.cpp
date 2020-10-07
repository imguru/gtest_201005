#include <string>

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

//-------------------
#include <gmock/gmock.h>
#include <map>


class MockDatabase : public IDatabase {
	std::map<std::string, User*> data;
public:
	MOCK_METHOD(void, SaveUser, (const std::string& name, User* user), (override));
	MOCK_METHOD(User*, LoadUser, (const std::string& name), (override));

	void DelegateToFake() {
		ON_CALL(*this, SaveUser).WillByDefault([this](const std::string& name, User* user) {
			SaveUserImpl(name, user);
		});
		ON_CALL(*this, LoadUser).WillByDefault([this](const std::string& name) {
			return LoadUserImpl(name);
		});
	}

	void SaveUserImpl(const std::string& name, User* user) {
		data[name] = user;
	}

	User* LoadUserImpl(const std::string& name) {
		return data[name];
	}
};


bool operator==(const User& lhs, const User& rhs) {
	return lhs.GetName() == rhs.GetName() && lhs.GetAge() == rhs.GetAge();
}

using testing::NiceMock;

TEST(UserManagerTest, SaveTest) {
	NiceMock<MockDatabase> mock;
	UserManager manager(&mock);
	std::string testName = "test_name";
	int testAge = 42;
	User user(testName, testAge);
	mock.DelegateToFake();

	manager.Save(&user);
	User* actual = manager.Load(testName);

	EXPECT_EQ(user, *actual) << "저장한 User를 로드하였을 때";
}









