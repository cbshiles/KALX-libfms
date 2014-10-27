// trnlsp.h - Intel MKL Nonlinear Least Squares Problem with Without Constraints
#pragma once
#include "../include/ensure.h"
#include <functional>
#include <initializer_list>
#include <vector>
#include "mkl_rci.h"
#include "mkl_types.h"
#include "mkl_service.h"

namespace mkl {

	// solve min_x ||F(x)||_2 where F: R^n -> R^m
	class trnlsp {
		_TRNSP_HANDLE_t h_;
		int info_[6];
		std::vector<double> eps_;
		std::vector<double> x_, f_, df_;
		std::function<std::vector<double>(const double*)> F_, dF_;
	public:
		trnlsp(int n, int m, const double* x, const double* eps, int iter1 = 1000, int iter2 = 100, double rs = 1)
			: x_(x, x + n), eps_(eps, eps + 6), f_(m), df_(n*m)
		{
			ensure (TR_SUCCESS == dtrnlsp_init(&h_, &n, &m, const_cast<double*>(x), const_cast<double*>(eps), &iter1, &iter2, &rs));
		}
		trnlsp(const trnlsp&) = delete;
		trnlsp operator=(const trnlsp&) = delete;
		~trnlsp()
		{
			dtrnlsp_delete(&h_);
			mkl_free_buffers();
		}

		trnlsp& function(const std::function<std::vector<double>(const double*)>& F)
		{
			F_  = F;

			return *this;
		}
		const std::function<std::vector<double>(const double*)>& function(void) const
		{
			return F_;
		}

		trnlsp& jacobian(const std::function<std::vector<double>(const double*)>& dF)
		{
			dF_  = dF;

			return *this;
		}
		const std::function<std::vector<double>(const double*)>& jacobian(void) const
		{
			return dF_;
		}

		int step(void)
		{
			int rci;

			ensure (TR_SUCCESS == dtrnlsp_solve(&h_, &f_[0], &df_[0], &rci));

			return rci;
		}

		const double* solve(void)
		{
			while (int rci = step() && rci >= 0) {
				if (rci == 1) {
					f_ = F_(&x_[0]);
				}
				else if (rci == 2) {
					df_ = dF_(&x_[0]);
				}
			}

			return &x_[0];
		}

	};

} // mkl