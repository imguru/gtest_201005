#include <string>
#include <unistd.h> // sleep

class Database {
public:
	void Connect() { sleep(2); }
	void Disconnect() { sleep(1); }

	void Login(const std::string& id, const std::string& password) {}
	void Logout() {}

	bool IsLogin() { return true; }
};

//-------------------------------
#include <gtest/gtest.h>

// 가정: Connect() / Disconnect()가 느리다.
//  : 픽스쳐를 설치하거나 해체하는 작업이 느리다.
// => 테스트케이스 마다 SetUp / TearDown이 호출되기 때문에, 테스트케이스가 추가될 때마다 느려진다.
// => Slow Test 문제
//   : 테스트를 수행하는 개발자의 생산성을 떨어뜨린다.
//     테스트가 느려서, 아무도 코드를 변경하여도 테스트를 수행하지 않는다.
//   * 픽스쳐의 설치/해체로 인해 느린 테스트의 문제가 발생한다면, Suite Fixture SetUp / TearDown을 통해 해결가능하다.

// Suite Fixture SetUp / TearDown
// : xUnit Test Framework가 제공하는 기능입니다.
//   문제점
//     : 더이상 각각의 테스트 케이스는 독립적이지 않습니다.
//       "신선한 픽스쳐 전략" => "공유 픽스쳐 전략"
//     "공유 픽스쳐 전략"
//      : 성능은 더 빠르게 동작하지만, Test Suite 내부의 모든 Test Case가 픽스쳐를 공유한다.
//        공유되는 픽스쳐가 이전의 테스트 케이스로 인해 망가졌다면,
//        이후의 모든 테스트 케이스는 신뢰성을 잃어버린다.
//          => "변덕스러운 테스트"
//            : 공유 픽스쳐의 상태에 따라 테스트의 결과가 변화한다.
//
//     - 공유 픽스쳐의 전략을 사용할 경우, 하나의 Test Suite 안에 너무 많은 TestCase를 두지 않는 것이 좋다.
//        SampleTest               SampleTest1
//           TestCase 100   =>        TestCase 25
//                                 SampleTest2
//                                    TestCase 25
//                                 ...

#if 0
Suite Fixture SetUp() - static
DatabaseTest::SetUpTestSuite();

DatabaseTest* ts = new DatabaseTest;
ts->SetUp();
ts->LoginTest();
ts->TearDown();
delete ts;

DatabaseTest* ts = new DatabaseTest;
ts->SetUp();
ts->LogoutTest();
ts->TearDown();
delete ts;

DatabaseTest::TearDownTestSuite();
Suite Fixture TearDown(); - static


#endif


class DatabaseTest : public testing::Test {
protected:
	static Database* db;
	
	DatabaseTest() { 
		printf("DatabaseTest()\n");
	}

	~DatabaseTest() {
		printf("~DatabaseTest()\n");
	}

#if 0
	// 1.10 이전
	static void SetUpTestCase() {
		printf("SetUpTestSuite()\n");
		db = new Database;
		db->Connect();
	}

	static void TearDownTestCase() {
		printf("TearDownTestSuite()\n");
		db->Disconnect();
		delete db;
	}
#endif
#if 1
	// 1.10 이후
	static void SetUpTestSuite() {
		printf("SetUpTestSuite()\n");
		db = new Database;
		db->Connect();
	}

	static void TearDownTestSuite() {
		printf("TearDownTestSuite()\n");
		db->Disconnect();
		delete db;
	}
#endif

	void SetUp() override {
		printf("SetUp()\n");
	}

	void TearDown() override {
		printf("TearDown()\n");
	}
};

// C++은 정적 멤버 변수에 대해서 외부 정의가 필요합니다.
Database* DatabaseTest::db = nullptr;



TEST_F(DatabaseTest, LoginTest) {
	db->Login("test_id", "test_password");

	ASSERT_TRUE(db->IsLogin()) << "로그인 하였을 때";
}

TEST_F(DatabaseTest, LogoutTest) {
	db->Login("test_id", "test_password");
	db->Logout();

	ASSERT_FALSE(db->IsLogin()) << "로그아웃 하였을 때";
}

#if 0
TEST(DatabaseTest, LoginTest) {
	Database* db = new Database;
	db->Connect();

	db->Login("test_id", "test_password");

	ASSERT_TRUE(db->IsLogin()) << "로그인 하였을 때";

	db->Disconnect();
	delete db;
}

TEST(DatabaseTest, LogoutTest) {
	Database* db = new Database;
	db->Connect();

	db->Login("test_id", "test_password");
	db->Logout();

	ASSERT_FALSE(db->IsLogin()) << "로그아웃 하였을 때";

	db->Disconnect();
	delete db;
}
#endif
