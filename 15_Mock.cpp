#include <string>
#include <vector>

enum Level {
	INFO, WARN, ERROR,
};

struct DLoggerTarget {
	virtual ~DLoggerTarget() {}

	virtual void Write(Level level, const std::string& message) = 0;
};

class DLogger {
	std::vector<DLoggerTarget*> targets;
public:
	void Write(Level level, const std::string& message) {
		for (DLoggerTarget* e : targets) {
			e->Write(level, message);
		}
	}
	
	void AddTarget(DLoggerTarget* p) {
		targets.push_back(p);
	}
};

//------------------
#include <gtest/gtest.h>

// Mock Object Pattern
//  의도: 함수를 호출하였을 때, 발생하는 부수효과를 관찰할 수 없어서, 테스트 안된 요구사항이 존재한다.
//     1) Test Spy Pattern
//     2) Mock Object Pattern
//       방법: 행위 기반 검증을 수행한다.
//          상태 검증: 객체에 작용을 가한 후, 단언문을 이용해서 내부의 상태값의 변화를 검증의 방법을 사용한다.
//          동작 검증: 객체에 작용을 가한 후, 내부적으로 발생하는 함수의 호출 여부, 호출 순서, 호출 횟수 등을 통해 검증한다.


// 행위 기반 검증
//    - 모의 객체(Mock Object)
//         : 내부적으로 발생한 메소드의 호출 여부, 횟수, 순서 등의 정보를 가지고 있다.
//         => 목 프레임워크: 모의객체의 생성을 돕는 프레임워크
//               : Mock Framework을 사용해야 합니다.
//               Java: jMock, EasyMock, Mockito, Spock Framework
//               C++: Google Mock
//                 => 설치가 필요합니다.
//                 => Google Test에 의존성이 존재합니다.
//                  : Google Mock 설정만 하시면, Google Test는 기본적으로 사용할 수 있습니다.










