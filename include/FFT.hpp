#pragma once

#include <complex>
#include <iostream>
#include <valarray>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <iterator>

#ifdef _MSC_VER
constexpr double M_PI = 3.141592653589793238460;
#endif

//* Implementation from “Jeganathan Swaminathan, Maya Posch, Jacek Galowicz -- Expert C++ Programming.”.

using cmplx = std::complex<double>;
using csignal = std::vector<cmplx>;

class num_iterator
{
	size_t i;
public:
	using difference_type = ptrdiff_t;
	using value_type = size_t;
	using pointer = size_t*;
	using reference = size_t&;
	using iterator_category = std::input_iterator_tag;

	explicit num_iterator(size_t position) : i(position){}
	
	size_t operator*() const {return i;}
	
	num_iterator& operator++() 
	{
		++i;
		return *this;
	}


	bool operator!=(const num_iterator& other) const
	{
		return i != other.i;
	}
};

csignal fourier_transform(const csignal& s, bool back = false)
{
	csignal t(s.size());
	
	const double pol{2.0 * M_PI * (back ? -1.0 : 1.0)};
	const double div{back ? 1.0 : double(s.size())};

	auto sum_up([=, &s] (size_t j)
	{
		return [=,&s] (cmplx c, size_t k)
		{
			return c + s[k] * std::polar(1.0, pol*k*j/double(s.size()));
		};
	});

	auto to_ft([=,&s](size_t j)
	{
		return std::accumulate(num_iterator{0}, num_iterator{s.size()}, cmplx{}, sum_up(j))/div;
	});

	std::transform(num_iterator{0}, num_iterator{s.size()}, std::begin(t), to_ft);

	return t;
}

// template<typename T>
static auto gen_cosine(size_t period_len)
{
	return [period_len, n{0}] () mutable {
		return std::cos(double(n++)*2.0*M_PI/period_len);
	};
}

// template<typename T>
static auto gen_square_wave(size_t period_len)
{
	return [period_len, n{period_len*7/4}]() mutable {
		return ((n++ * 2/period_len) % 2) * 2 - 1.0;
	};
}

template<typename F>
static csignal signal_from_generator(size_t len, F gen)
{
	csignal r(len);
	std::generate(std::begin(r), std::end(r), gen);
	return r;
}



static void print_signal(const csignal& s)
{
	auto real_val([](cmplx c){ return c.real(); });
	std::transform(std::begin(s), std::end(s), std::ostream_iterator<double>{std::cout, " "}, real_val);
	std::cout << "\n";
}

static void printf_signal(const csignal& s, std::ofstream& oflile)
{
	auto real_val([](cmplx c){ return c.real(); });
	std::transform(std::begin(s), std::end(s), std::ostream_iterator<double>{std::cout, " "}, real_val);
	oflile << "\n";
}

std::ostream& operator<<(std::ostream& out, csignal const& outsig)
{
	auto real_val([](cmplx c){ return c.real(); });
	out << real_val;
	return out;
}