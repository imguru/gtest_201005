
// SUT

#include <stdio.h>

struct Packet {};

struct PacketStream {
	virtual ~PacketStream() {}

	virtual void AppendPacket(Packet* new_packet) = 0;
	virtual const Packet* GetPacket(size_t packet_number) const = 0;
};

class ConcreatePacketStream : public PacketStream {
public:
	void AppendPacket(Packet* new_packet) override {
		printf("ConcreatePacketStream - AppendPacket\n");
	}

	const Packet* GetPacket(size_t packet_number) const override {}
};

class PacketReader {
public:
	void ReadPacket(PacketStream* stream, size_t packet_num) {
		printf("PacketReader - ReadPacket\n");
		stream->AppendPacket(nullptr);
		stream->GetPacket(packet_num);
	}
};

#include <gmock/gmock.h>

class MockPacketStream : public PacketStream {
public:
	MOCK_METHOD(void, AppendPacket, (Packet* new_packet), (override));
	MOCK_METHOD(const Packet*, GetPacket, (size_t packet_number), (const, override));
};

// PacketReader의 ReadPacket이 수행되면, stream에 대해서, AppendPacket(nullptr) / GetPacket(packet_number)가 제대로 호출되는지 여부를
// 검증하고 싶다.
TEST(PacketReaderTest, ReadPacket) {
	MockPacketStream stream;
	PacketReader reader;

	EXPECT_CALL(stream, AppendPacket(nullptr));
	EXPECT_CALL(stream, GetPacket(42));

	reader.ReadPacket(&stream, 42);

	// ConcreatePacketStream stream;
	// PacketReader reader;

	// reader.ReadPacket(&stream, 42);
}





// 구체적인 타입을 이용한 강한 결합

// 인터페이스 또는 추상 클래스를 이용한 약한 결합
//  => 인터페이스를 기반으로 가상 함수로 구현되어 있어야 한다.
//     장점
//       교체가 가능하다.(테스트 대역을 통해 검증할 수 있다.)
//     단점
//       가상함수는 일반 함수에 비해 오버헤드가 있다.


// 아래 코드: 강한 결합 형성되어 있습니다.
#if 0
struct Packet {};

class ConcreatePacketStream {
public:
	void AppendPacket(Packet* new_packet) {
		printf("ConcreatePacketStream - AppendPacket\n");
	}

	const Packet* GetPacket(size_t packet_number) const {}
};

class PacketReader {
public:
	void ReadPacket(ConcreatePacketStream* stream, size_t packet_num) {
		printf("PacketReader - ReadPacket\n");
		stream->AppendPacket(nullptr);
		stream->GetPacket(packet_num);
	}
};
#endif
