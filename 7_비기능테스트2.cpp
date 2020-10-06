
#include <gtest/gtest.h>

// C++의 객체의 누수를 확인하는 기능
//  => 제품 코드에 해당 기능이 미리 구현되어야 합니다.
//  => C++의 객체의 new / delete 연산자를 재정의할 수 있습니다.
//
//  제품 코드에서는 객체의 메모리를 할당하는 라이브러리를 사용하는 경우가 있습니다.
//   => Google: tcmalloc
//      Facebook: jemalloc
//      : 조건부 컴파일을 활용해서, 테스트 코드에서만 사용하도록 하는 것이 좋습니다.

// new
// 1. 동적 메모리 할당  - operator new
// 2. 생성자 호출
//
// delete
// 1. 소멸자 호출
// 2. 동적 메모리 해지 - operator delete


// SUT
class Image {
public:
#ifdef GTEST_LEAK_TEST
	static int allocCount;

	void* operator new(size_t size) {
		++allocCount;
		return malloc(size);
	}

	void operator delete(void* p, size_t) {
		--allocCount;
	}
#endif
};

#ifdef GTEST_LEAK_TEST
int Image::allocCount = 0;
#endif

void foo() {
	Image* p1 = new Image;
	Image* p2 = new Image;
	Image* p3 = new Image;

	delete p1;
	delete p2;
	delete p3;
}

class ImageTest : public testing::Test {
protected:
	int allocCount;
	void SetUp() override {
#ifdef GTEST_LEAK_TEST
		allocCount = Image::allocCount;
#endif
	}

	void TearDown() override {
#ifdef GTEST_LEAK_TEST
		int diff = Image::allocCount - allocCount;
		EXPECT_EQ(diff, 0)  << diff << " Objects(s) leaks...";
#endif
	}
};

TEST_F(ImageTest, Foo) {
	foo();
}
