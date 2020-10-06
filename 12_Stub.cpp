
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
		try {
			conn->Move(x, y);
		} catch (NetworkException& e) {
			printf("NetworkException 처리 로직...\n");
			throw e;
		}
	}
};

//------------------
#include <gtest/gtest.h>

// Test Stub Pattern
//   의도: '다른 컴포넌트로부터의 간접 입력'에 의존하는 로직을 독립적으로 검증하고 싶다.
//   방법: 실제 의존하는 객체를 테스트용 객체로 교체해서, SUT가 테스트하는데 필요한 결과를 보내도록 제어한다.
//   => 특수한 상황을 시뮬레이션 하고 싶다.
//     : 네트워크, 시간 같이 제어가 일반적으로 불가능한(어려운) 환경을 제어하기 위해 사용한다.

// * 테스트 대역을 만들때 협력 객체의 인터페이스를 구현하는 형태로 만듭니다.
//  => 협력 객체의 인터페이스가 복잡하면, 테스트 대역을 만드는 비용이 증가합니다.
//     : 범용 인터페이스 보다는 세분화된 인터페이스가 더 좋다.
//       ISP(Interface Segregation Principle): 인터페이스 분리 원칙
//  => 협력 객체를 구체적인 타입이 아니라, 인터페이스를 통해 의존한다.
//     : DIP(Dependency Inversion Principle): 의존 관계 역전 원칙
//      1) 테스트 대역을 적용할 수 있습니다.
//      2) 제품 코드를 사용하는 방식으로, 테스트 대역을 적용할 수 있다.

class StubConnection : public IConnection {
public:
	void Move(int x, int y) override {
		throw NetworkException();
	}

	void Attack() override {}
};


// NetworkException이 IConnection 객체에서 발생하였을 때, NetworkException이 밖으로 제대로 던져지는지 검증하고 싶다.
TEST(PlayerTest, MoveTest) {
	// TCPConnection conn;
	StubConnection conn;
	Player player(&conn);

	EXPECT_THROW(player.Move(10, 20), NetworkException);
}




































