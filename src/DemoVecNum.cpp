//============================================================================
// Autor: Diardon
// Blog : https://diardon.wordpress.com/
//============================================================================

#include <iostream>
#include "vecnum.h"

void test1();
void test0();

int main()
{
	test0();
	//test1();
}

void test0()
{
	int arr1[5] = { 1, 3, 5, 7, 9 };
	int *arr2 = new int[]{ 2, 4, 6, 8, 10 };

	vecnum<int> vec1(5);
	vecnum<int> vec2(arr1, 5);
	vecnum<int> vec3(arr2, 5);

	vec1.fill(1);

	vecnum<int> vec4(vec1);

	std::cout << "vec1: " << vec1 << std::endl;
	std::cout << "vec2: " << vec2 << std::endl;
	std::cout << "vec3: " << vec3 << std::endl;
	std::cout << "vec4: " << vec4 << std::endl;
}

void test1()
{
	vecnum<int> vec1(5);
	vecnum<int> vec2(5);
	vecnum<int> vec3(5);

	vec1.fillrnd();
	vec2.fillrnd();
	vec3.fill(1);

	std::cout << "vec1: " << vec1 << std::endl;
	std::cout << "vec2: " << vec2 << std::endl;
	std::cout << "vec3: " << vec3 << std::endl;

	std::cout << "vec1 + vec2: " << vec1 + vec2 << std::endl;
	std::cout << "vec1 - vec3: " << vec1 - vec3 << std::endl;
	std::cout << "vec3*5: " << vec3*5 << std::endl;
	std::cout << "7*vec3: " << 7*vec3 << std::endl;

	vec1.fill(1);
	vec2.fill(2);
	vec3.fill(3);

	std::cout << "vec1: " << vec1 << std::endl;
	std::cout << "vec2: " << vec1 << std::endl;
	std::cout << "vec3: " << vec1 << std::endl;

	vec1 -= vec2;
	std::cout << "vec1 -= vec2: " << vec1 << std::endl;
	vec1.fill(1);

	vec1 += vec2;
	std::cout << "vec1 += vec2: " << vec1 << std::endl;
	vec1.fill(1);
}
