#include <gtest/gtest.h>

// 1. Assertions
// ASSERT_XX
//        EQ / NE / LT / LE / GT / GE / TRUE / FALSE
//   - 단언문이 실패할 경우, 이후의 코드는 수행되지 않는다.
//   => 하나의 테스트 케이스 안에서 하나의 단언문 사용하는 것이 좋다.
//   => 문제점: 하나의 기능에 대해서, 많은 테스트 케이스를 작성해야 한다.

// EXPECT_XX
//        EQ / NE / LT / LE / GT / GE / TRUE / FALSE
//   - 단언문이 실패하더라도, 이후의 코드는 수행된다.
//   - 하나의 단언문이 실패한다면, 테스트의 결과는 실패이다.
//   => 죽은 단언문의 문제가 발생하지 않는다.
//   => 하나의 테스트 케이스 안에서 여러 값을 검증하는 용도로 사용할 수 있다.
TEST(GoogleTest, Sample1) {
	int expected = 42;

	int actual = 42;

	// ASSERT_EQ(expected, actual) << "Reason 1";
	// ASSERT_EQ(expected, actual) << "Reason 2";   // 죽은 단언문
	EXPECT_EQ(expected, actual) << "Reason 1";
	EXPECT_EQ(expected, actual) << "Reason 2";   // 죽은 단언문 X
}

#include <string>

// 2. 문자열
//   C-Style: const char* / char*
//   C++    : std::string
// 핵심: C 스타일의 문자열을 사용할 경우, 문자열 비교를 위해 다른 단언문을 사용해야 합니다.
//       EXPECT_STREQ/NE
//       EXPECT_STRCASEEQ/NE 
TEST(GoogleTest, Sample2) {
	std::string s1 = "hello";
	std::string s2 = "hello";

	EXPECT_EQ(s1, s2);

	const char* s3 = "Hello";
	const char* s4 = s2.c_str();

	// EXPECT_STREQ(s3, s4);  // !!
	EXPECT_STRCASEEQ(s3, s4);  // !!
}

// 3. 부동 소수점 - float / double
//   => 부동 소수점 비교를 위한 전용 단언 매크로가 존재합니다.
//   EXPECT_FLOAT_EQ / EXPECT_DOUBLE_EQ
//   EXPECT_FLOAT_NE / EXPECT_DOUBLE_NE
//
//   * 오차 범위를 직접 설정하고 싶다.
//   EXPECT_NEAR
TEST(GoogleTest, Sample3) {
	double a = 0.7;
	double b = 0.1 * 7;

	// EXPECT_EQ(a, b);
	EXPECT_DOUBLE_EQ(a, b);  // 4ULP's(오차)
	EXPECT_NEAR(a, b, 0.000000001);
}

// 4. 예외 테스트
//   : 비정상적인 상태에 도달했을 때, 기대했던 예외가 발생하는지 여부를 검증한다.
void IsValidFilename(const std::string& filename) {
	if (filename.empty()) {
		throw std::invalid_argument("filename should not empty!");
	}

	// ...
}

// 중요: 테스트케이스를 작성할 때, 잘못된 형태에서 테스트가 온전히 실패하는지 확인해야 합니다.

// 초기의 예외 검증을 지원하지 않는 단위 테스트 프레임워크에서 사용하는 방법입니다.
// => Google Test는 아래의 검증을 단언 매크로를 통해 제공하고 있습니다.
//    EXPECT_THROW: 기대한 예외가 발생하면 성공
//    EXPECT_ANY_THROW: 예외가 발생하면 성공
TEST(GoogleTest, Sample4) {
	// 테스트케이스의 변수명을 작성할 때, 의도가 나타나도록 작성하는 것은 테스트 케이스의 가독성에 좋습니다.
	std::string emptyFilename = "";
	
	EXPECT_THROW(IsValidFilename(emptyFilename), std::invalid_argument) << "빈 파일명을 전달하였을 때";
	EXPECT_ANY_THROW(IsValidFilename(emptyFilename)) << "빈 파일명을 전달하였을 때";
}

TEST(GoogleTest, Sample4_Bad) {
	std::string filename = "";

	try {
		IsValidFilename(filename);
		FAIL() << "기대한 예외가 발생하지 않았음.";
	} catch (std::invalid_argument& e) {
		SUCCEED();
	} catch (...) {
		FAIL() << "기대한 예외가 아닌 다른 예외가 발생하였음.";
	}
}

// 테스트 커버리지: 테스트 코드에 의해서 실행된 제품 코드의 비율
//  => 테스트 커버리지는 테스트 코드의 품질의 척도로 사용하면 안됩니다.
//    이유: 단언문을 사용하지 않는 테스트 코드가 발생할 수 있습니다.
//          단언문이 존재하지 않으면, 절대 실패하지 않는 단위 테스트..


// 2-3개 테스트 케이스가 이상적이다.
int foo(int a, int b, int c) {
	if (a < 0) {
		return -1;
	}

	if (b < 0) {
		return -1;
	}

	if (c < 0) {
		// return -1;
		return 0;
	}

	return a + b + c + 10;
}

// 5. 테스트 비활성화
//  => 특정한 테스트 케이스 또는 테스트 스위트가 테스트의 결과에 포함되지 않고, 수행되길 원한다.
//  => 테스트를 주석 처리 등을 통해 제외하는 것은, '잊혀진 테스트'가 된다.
//  => xUnit Test Framework은 테스트를 비활성화는 기능을 제공하고 있습니다.
//     Google Test: 테스트 케이스 또는 테스트 스위트의 이름이 DISABLED_ 접두를 가진다면, 비활성화 됩니다.

//  테스트를 수행할 때, 비활성화된 테스트도 수행하고 싶다면
//    $ ./a.out --gtest_also_run_disabled_tests

#if 1
// 2개 - 부정케이스 / 긍정케이스
//     EXPECT_ : 하나의 테스트 케이스 안에서 여러 검증을 수행할 수 있다.
TEST(DISABLED_GoogleTest, P_FooTest) {
	int a = 10;
	int b = 10;
	int c = 10;

	EXPECT_EQ(foo(a, b, c), a + b + c) << "foo를 호출하였을 때";
}

TEST(GoogleTest, DISABLED_N_FooTest) {
	EXPECT_EQ(foo(-1, 0, 0), -1) << "a가 0보다 작을 때";
	EXPECT_EQ(foo(0, -1, 0), -1) << "b가 0보다 작을 때";
	EXPECT_EQ(foo(0, 0, -1), -1) << "c가 0보다 작을 때";
}
#endif

TEST(SampleTest1, foo) {}
TEST(SampleTest1, goo) {}
TEST(SampleTest1, hoo) {}

int n = 0;
TEST(SampleTest2, foo) {
	ASSERT_LT(++n, 300);
	
	// 테스트의 결과 말고 추가적인 정보도 로깅하고 싶다.
	//  - RecordProperty
	//  => gtest_output=xml|json 
	//     위의 xml 또는 json 파일에 기록되는 정보입니다.
	RecordProperty("cpu", "1.5");
	RecordProperty("mem", "30%");
}

TEST(SampleTest2, goo) {
	RecordProperty("cpu", "1.5");
	RecordProperty("mem", "30%");
}

TEST(SampleTest2, hoo) {
	RecordProperty("cpu", "1.5");
	RecordProperty("mem", "30%");
}

// 6. Test Filter 기능을 제공합니다.
// $ ./a.out --gtest_filter=SampleTest*.foo
// $ ./a.out --gtest_filter=SampleTest1.*
//  핵심: 테스트케이스의 종류에 따라서, 명확한 이름 규칙을 세우는 것은 독립적인 테스트 실행에 도움이 됩니다.

// 7. Test Result Formatter => XML/JSON
//   - xUnit Test Framework의 공통된 포맷입니다.
//    CI와 연계해서, 테스트 결과를 표시할 때 사용할 수 있습니다.
//    (Jenkins, Travis CI, Circle CI)
// $ ./a.out --gtest_output=[xml|json]
//     => test_detail.xml / test_detail.json
//
// 8. 반복된 테스트(Repeat Test)
//   => "변덕스러운 테스트"를 체크할 때 사용할 수 있습니다.
//	$ ./a.out --gtest_repeat=N
//	$ ./a.out --gtest_repeat=1000 --gtest_shuffle --gtest_break_on_failure
//	   --gtest_shuffle: 테스트케이스의 실행 순서를 랜덤으로 섞는다.
//	   --gtest_break_on_failure: 테스트 실행 중 실패가 발생하면, 이후 테스트를 중지한다.































