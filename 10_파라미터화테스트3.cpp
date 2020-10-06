
// Combine
//  : 데이터 셋을 정의할 때, 두 개 이상의 데이터를 조합해서 검증 가능하다.
//  1) TestWithParam<std::tuple<T1, T2>>
//  2) Tuple - std::get<0>(GetParam());

enum Color {
	BLACK, GRAY, WHITE
};

const char* animals[] = { "Cat", "Dog" };

#include <gtest/gtest.h>

using testing::Combine;
using testing::ValuesIn;
using testing::Values;

class AnimalTest : public testing::TestWithParam<std::tuple<const char*, Color>> {
};

INSTANTIATE_TEST_SUITE_P(animalVariations, AnimalTest, 
	Combine(ValuesIn(animals), Values(BLACK, GRAY, WHITE)));

TEST_P(AnimalTest, AnimalLook) {
	const char* animal = std::get<0>(GetParam());
	Color color = std::get<1>(GetParam());

	printf("%s - %d\n", animal, color);
}
