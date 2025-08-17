/*
    glm documentation at https://glm.g-truc.net/0.9.9/api/index.html
*/


#include <iostream>

#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_bool4.hpp>     // bvec4
#include <glm/ext/matrix_float4x4.hpp>  // mat4
#include <glm/ext/matrix_relational.hpp>// equal, all

#include "../include/Vec4.hpp"


// ANSI color codes
#define GREEN "\033[32m"
#define RED "\033[31m"
#define RESET "\033[0m"


int main() {
	/*
	    matrix1:
	    1, 2, 3, 4
	    5, 6, 7, 8
	    9, 10, 11, 12
	    13, 14, 15, 16
	    access goes like: matrix1[y][x], or [row][col]
	*/
	glm::mat4 matrix1 =
	    glm::mat4(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);

	glm::mat4 matrix2 =
	    glm::mat4(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);

	// std::cout << "matrix1:\n" << glm::to_string(matrix1) << std::endl;

	glm::mat4 matrix3 = glm::identity<glm::mat4>();

	// access of the matrix is [y][x], or [row][col]
	if(matrix1[0][0] == 1.0f && matrix1[1][0] == 5.0f && matrix1[1][1] == 6.0f && matrix1[1][2] == 7.0f)
		std::cout << GREEN << "Matrix1 is initialized correctly." << RESET << std::endl;
	else
		std::cerr << RED << "Matrix1 is not initialized correctly." << RESET << std::endl;

	// matrix1 and matrix2 should be equal within an epsilon
	if(glm::all(glm::equal(matrix1, matrix2, MIRT::Vec4::s_epsilon)))
		std::cout << GREEN << "matrix equality holds" << RESET << std::endl;
	else
		std::cerr << RED << "matrix equality does not hold" << RESET << std::endl;

	// matrix1 and matrix3 should not be equal
	if(!glm::all(glm::equal(matrix1, matrix3, MIRT::Vec4::s_epsilon)))
		std::cout << GREEN << "matrix inequality holds" << RESET << std::endl;
	else
		std::cerr << RED << "matrix inequality does not hold" << RESET << std::endl;

	return 0;
}