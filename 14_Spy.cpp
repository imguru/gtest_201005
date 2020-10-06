#include <string>
#include <vector>

enum Level {
	INFO, WARN, ERROR,
};

struct DLoggerTarget {
	virtual ~DLoggerTarget() {}

	virtual void Write(Level level, const std::string& message) = 0;
};

// 분산 로거 - Observer Pattern
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
#include <algorithm>

// DLogger에 Target을 등록하고, Write를 호출하였을 때, DLoggerTarget의 Write가 제대로 수행되는가?

// Test Spy Pattern
//  의도: 함수를 호출하였을 때, 발생하는 부수효과를 관찰할 수 없어서, 테스트 안된 요구사항이 존재한다.
//  방법: 목격한 일을 기록해두었다가, 나중에 테스트에서 확인할 수 있도록 만들어진 테스트 대역
//        다른 컴포넌트로부터의 간접 출력을 저장해두었다가, 검증에 이용한다.

class SpyTarget : public DLoggerTarget {
	std::vector<std::string> history;

	std::string concat(Level level, const std::string& message) {
		static std::string levelStr[] = {
			"INFO", "WARN", "ERROR",
		};
		return levelStr[level] + "@" + message;
	}

public:
	void Write(Level level, const std::string& message) override {
		history.push_back(concat(level, message));
	}

	// 테스트케이스에서 검증을 목적으로 사용하는 함수
	bool IsReceived(Level level, const std::string& message) {
		return std::find(history.begin(), history.end(), concat(level, message)) != history.end();
	}
};

TEST(DLoggerTest, WriteTest) {
	DLogger logger;
	SpyTarget spy1, spy2;
	logger.AddTarget(&spy1);
	logger.AddTarget(&spy2);
	Level testLevel = INFO;
	std::string testMessage = "log_test_message";
	
	logger.Write(testLevel, testMessage);

	EXPECT_TRUE(spy1.IsReceived(testLevel, testMessage));
	EXPECT_TRUE(spy2.IsReceived(testLevel, testMessage));
}

























