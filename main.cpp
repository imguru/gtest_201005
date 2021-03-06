
// 1. 헤더파일 포함
// #include <gtest/gtest.h>
#include <gmock/gmock.h>


// 2. main
//  : main을 일반적으로 작성할 필요가 없는 경우,
//    main을 라이브러리에 포함해서 사용하면 편리합니다.

// Google Mock
int main(int argc, char** argv) {
	testing::InitGoogleMock(&argc, argv);
	// InitGoogleMock에서 InitGoogleTest를 수행합니다.
	return RUN_ALL_TESTS();
}

// Google Test
#if 0
int main(int argc, char** argv) {
	printf("main\n");
	testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
#endif
