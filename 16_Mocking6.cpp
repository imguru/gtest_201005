
// SUT

#include <stdio.h>

// 구체적인 타입을 이용한 강한 결합
//     단점 - 교체가 불가능하다.
//         => 실행 시간에 교체할 필요가 없다면, 컴파일 타임에 교체하도록 만들면 된다.
//         => 템플릿을 이용해서, 의존성 주입의 모델을 구현하면 됩니다.


struct Packet {};

class ConcreatePacketStream {
public:
	void AppendPacket(Packet* new_packet) {
		printf("ConcreatePacketStream - AppendPacket\n");
	}

	const Packet* GetPacket(size_t packet_number) const {}
};

// 컴파일 타임에 의존하는 객체를 교체할 수 있다.
//  => Template을 이용한다.
//  => C++ Policy Based Design
//     단위 전략 vs  인터페이스
//    => 교체가 가능하다.
//     컴파일 타임 : 런타임 
//       : 테스트 대역을 사용할 수 있다.
//     - 단위 전략은 인터페이스를 암묵적으로 약속 한다.
//       : 템플릿 인자로 전달되는 클래스는 반드시 AppendPacket / GetPacket을 가지고 있다고 약속한다.
//     - 인터페이스를 사용한 교체 방법은, 인터페이스 타입을 통해 명시적으로 약속한다.  

template <typename PacketStream>
class PacketReader {
public:
	void ReadPacket(PacketStream* stream, size_t packet_num) {
		printf("PacketReader - ReadPacket\n");
		stream->AppendPacket(nullptr);
		stream->GetPacket(packet_num);
	}
};

//-------------------
#include <gmock/gmock.h>

// 단위전략의 모의 객체는 암묵적으로 약속된 인터페이스 함수를 구현한다.
class MockPacketStream {
public:
	MOCK_METHOD(void, AppendPacket, (Packet* new_packet));
	MOCK_METHOD(const Packet*, GetPacket, (size_t packet_number), (const));
};

TEST(MockTest, Sample) {
	MockPacketStream stream;
	PacketReader<MockPacketStream> reader;

	EXPECT_CALL(stream, AppendPacket(nullptr));
	EXPECT_CALL(stream, GetPacket(42));
	reader.ReadPacket(&stream, 42);
}
#if 0
TEST(MockTest, Sample) {
	ConcreatePacketStream stream;
	PacketReader<ConcreatePacketStream> reader;

	reader.ReadPacket(&stream, 42);
}
#endif
















