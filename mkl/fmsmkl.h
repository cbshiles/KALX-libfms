// fmsmkl.h - MKL header
#pragma once
#include <functional>
#include <vector>

namespace fms {

	// function from R^M to R^N
	template<size_t M, size_t M, class X = double>
	struct function {
		typedef M domain_dim;
		typedef N range_dim;
		std::function<std::vector<X>(const std::vector<X>&)> f;

	};

} // fms
