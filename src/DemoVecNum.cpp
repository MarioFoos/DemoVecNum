//============================================================================
// Autor: Diardon
// Blog : https://diardon.wordpress.com/
//============================================================================

#include <iostream>
#include "vecnum.h"

int main()
{
	vecnum<int> vec1(5, 1);
	vecnum<int> vec2(5, 2);
	vecnum<int> vec3(5, 3);

	std::cout << "vec1: " << vec1 << std::endl;
	std::cout << "vec2: " << vec1 << std::endl;
	std::cout << "vec3: " << vec1 << std::endl;

	vec1 *= 7;
	std::cout << "vec1*=7: " << vec1 << std::endl;

	vec2 /= 2;
	std::cout << "vec2/=2: " << vec2 << std::endl;

	vec1.fillrnd();
	vec2.fillrnd();

	std::cout << "vec1: " << vec1 << std::endl;
	std::cout << "vec2: " << vec1 << std::endl;

	vec1.fill(1);
	vec2.fill(2);

	std::cout << "vec1: " << vec1 << std::endl;
	std::cout << "vec2: " << vec1 << std::endl;

	vec1 -= vec2;
	std::cout << "vec1 -= vec2: " << vec1 << std::endl;
	vec1.fill(1);

	vec1 += vec2;
	std::cout << "vec1 += vec2: " << vec1 << std::endl;

	vec3 = vec1 + vec2;
	std::cout << "Suma: " << vec3 << std::endl;

	vec3 = vec1 - vec2;
	std::cout << "Resta: " << vec3 << std::endl;

	int prod = vec1*vec2;
	std::cout << "Prod: " << prod << std::endl;

	vec3 = vec1*5;
	std::cout << "vec1*5: " << vec3 << std::endl;

	vec3 = vec2/2;
	std::cout << "vec2/2: " << vec3 << std::endl;

	return 0;
}
