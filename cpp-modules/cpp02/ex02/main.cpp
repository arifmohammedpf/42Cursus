#include "Fixed.hpp"

int main( void )
{
	std::cout << "Given tests" << std::endl;
	Fixed a;
	Fixed const b( Fixed( 5.05f ) * Fixed( 2 ) );
	std::cout << a << std::endl;
	std::cout << ++a << std::endl;
	std::cout << a << std::endl;
	std::cout << a++ << std::endl;
	std::cout << a << std::endl;
	std::cout << b << std::endl;
	std::cout << Fixed::max( a, b ) << std::endl;




	std::cout << std::endl;
	std::cout << "Min - Max Tests" << std::endl;
	Fixed a1( Fixed( 2 ) );
	std::cout << "max("<< a << " & " << b << ")" << " : " << Fixed::max( a, b ) << std::endl;
	std::cout << "min("<< a1 << " & " << a << ")" << " : " << Fixed::min( a1, a ) << std::endl;
	std::cout << std::endl;



	
	std::cout << "Arithmetic operator tests" << std::endl;
	Fixed n1 = 150, n2 = 5.7f, n3 = 2.5f;
	// std::cout << n2 + n3 << std::endl;
	std::cout  << n1 << " + " << n2 << " + " << n3 << " = " << (n1 + n2 + n3) << std::endl
			   << n1 << " - " << n2 << " - " << n3 << " = " << (n1 - n2 - n3) << std::endl
			   << n1 << " * " << n2 << " * " << n3 << " = " << (n1 * n2 * n3) << std::endl
			   << n1 << " / " << n2 << " / " << n3 << " = " << (n1 / n2 / n3) << std::endl;
	std::cout << std::endl;
	
	
	
	
	std::cout << "Comparison operator tests" << std::endl;
	n1 = 5, n2 = 10;
	std::cout << n1 << " > " << n2 << " = " << std::boolalpha << (n1 > n2) << std::endl;
	std::cout << n1 << " < " << n2 << " = " << std::boolalpha << (n1 < n2) << std::endl;
	std::cout << n1 << " >= " << n2 << " = " << std::boolalpha << (n1 >= n2) << std::endl;
	std::cout << n1 << " <= " << n2 << " = " << std::boolalpha << (n1 <= n2) << std::endl;
	std::cout << n1 << " == " << n2 << " = " << std::boolalpha << (n1 == n2) << std::endl;
	std::cout << n1 << " != " << n2 << " = " << std::boolalpha << (n1 != n2) << std::endl;
	std::cout << std::endl;
	
	
	
	
	std::cout << "Increment operator tests" << std::endl;
	Fixed num = 10;
	std::cout << "num = " << num << std::endl
			  << "num++ = " << num++ << std::endl
			  << "num = " << num << std::endl
			  << "++num = " << ++num << std::endl;
	
	
	
	
	std::cout << "\nDecrement Overload Tests" << std::endl
			  << "num = " << num << std::endl
			  << "num-- = " << num-- << std::endl
			  << "num = " << num << std::endl
			  << "--num = " << --num << std::endl;
	
return 0;
}