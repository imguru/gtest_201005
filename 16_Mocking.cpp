
#include <gmock/gmock.h>

struct MP3 {
	virtual ~MP3() {}

	virtual void Play() = 0;
	virtual void Stop(int n) = 0;

	virtual std::string GetName() const = 0;
	virtual void Foo() noexcept = 0;

	virtual std::pair<bool, int> GetPair() const = 0;
	virtual std::vector<int> GetVector() const = 0;

	virtual bool CheckMap(std::map<int, double> a, bool b) = 0;
};

// 1. Mocking: 모의 객체를 만들기 위해서, 인터페이스가 제공하는 메소드를 구글 목 프레임워크의
//             매크로를 이용해서 코드를 생성하는 작업.
//    MOCK_METHOD(반환타입, 메소드이름, (인자, ...), (한정자, ...));
//    "한정자"
//    1. override: 선택
//    2. const: 필수
//    3. noexcept: 필수

// - 이름: Mock 접두를 붙이는 것이 일반적입니다.
// - public의 접근 지정자로 수행해야 합니다.
// - 모의객체가 제대로 생성되었는지 확인하기 위해서는 생성을 해봐야 합니다.
// - 템플릿의 인자가 2개 이상인 경우, 쉼표(,)로 인해서, 매크로 함수의 인자가 1개 더 전달되는 문제가 있습니다.
//   => 괄호로 한번 더 묶어주어야 합니다.
//   => 템플릿 인자가 2개인 타입에 대한 엘리어싱(별명)을 지정하면 편리하게 사용할 수 있습니다.

class MockMP3 : public MP3 {
public:
	using MapIntDouble = std::map<int, double>;
	using BoolAndInt = std::pair<bool, int>;
	MOCK_METHOD(bool, CheckMap, (MapIntDouble a, bool b), (override));
	MOCK_METHOD(BoolAndInt, GetPair, (), (override, const));

	// MOCK_METHOD(bool, CheckMap, ((std::map<int, double>) a, bool b), (override));
	// MOCK_METHOD((std::pair<bool, int>), GetPair, (), (override, const));

	MOCK_METHOD(std::vector<int>, GetVector, (), (override, const));

	MOCK_METHOD(void, Play, (), (override));
	MOCK_METHOD(void, Stop, (int n), (override));

	MOCK_METHOD(std::string, GetName, (), (override, const));
	MOCK_METHOD(void, Foo, (), (override, noexcept));
};

TEST(MockTest, Sample) {
	MockMP3 mock;  // !!
}








