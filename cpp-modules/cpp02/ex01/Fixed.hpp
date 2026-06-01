#ifndef FIXED_HPP
#define FIXED_HPP

# include <iostream>
# include <cmath>

class Fixed
{
	private:
		int					_fixed;
		static const int	_bits = 8;
	public:
		Fixed();
		Fixed(const	int num);
		Fixed(const	float num);
		Fixed(Fixed const &object);
		~Fixed();
		Fixed	&operator= (Fixed const &rhs);

		int		getRawBits(void) const;
		void	setRawBits(int const raw);
		float	toFloat(void) const;
		int		toInt(void) const;
};

std::ostream &operator<<(std::ostream &out, Fixed const &rhs);

#endif