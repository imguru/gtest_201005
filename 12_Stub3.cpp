
#include <iostream>

class NetworkException : public std::exception {
public:
	const char* what() {
		return "Network exception";
	}
};

struct IConnection {
	virtual ~IConnection() {}

	virtual void Move(int x, int y) = 0;
	virtual void Attack() = 0;
};

class TCPConnection : public IConnection {
public:
	void Move(int x, int y) override {}
	void Attack() override {}
};

class Player {
	IConnection* conn;
public:
	Player(IConnection* p) : conn(p) {}

	void Move(int x, int y) {
		//---
		try {
			conn->Move(x, y);
		} catch (NetworkException& e) {
			printf("NetworkException 처리 로직...\n");
			throw e;
		}
		//---
	}
};

//------------------
#include <gmock/gmock.h>


class MockConnection : public IConnection {
public:
	MOCK_METHOD(void, Move, (int x, int y), (override));
	MOCK_METHOD(void, Attack, (), (override));
};

using testing::NiceMock;
using testing::Throw;

TEST(PlayerTest, MoveTest) {
	NiceMock<MockConnection> conn;
	Player player(&conn);
	ON_CALL(conn, Move(10, 20)).WillByDefault(Throw(NetworkException()));

	EXPECT_THROW(player.Move(10, 20), NetworkException);
}




































