#include <iostream>
#include <complex>

int main() {
	std::complex<long double> c(1, 2);
	std::complex<long double> z(1, 1);
	z = z * z + c;
	long double norm = std::norm(z); //z.real()*z.real() + z.imag()*z.imag();
	std::cout << "c=" << c.real() << "+" << c.imag() << "i" << std::endl;
	std::cout << "z=" << z.real() << "+" << z.imag() << "i" << std::endl;
	std::cout << "norm=" << norm << std::endl;

	c = std::complex<long double>(2, 1);
	z = std::complex<long double>(3, -2);
	z = z * z + c;
	norm = std::norm(z);
	std::cout << "c=" << c.real() << "+" << c.imag() << "i" << std::endl;
	std::cout << "z=" << z.real() << "+" << z.imag() << "i" << std::endl;
	std::cout << "norm=" << norm << std::endl;

	return 0;
}
