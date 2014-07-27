// chrono_duration_cast.h - workaround for VC++ 2012 bug
// http://connect.microsoft.com/VisualStudio/feedback/details/752794

// duration_cast
template<class _To,
	class _Rep,
	class _Period> inline
	_To	duration_cast(const std::chrono::duration<_Rep, _Period>& _Dur)
	{	// convert duration to another duration
	typedef typename std::ratio_divide<_Period, typename _To::period>::type _CF;
	typedef typename std::common_type<
		typename std::common_type<typename _To::rep, _Rep>::type,
			intmax_t>::type _CR;
	if (_CF::num == 1 && _CF::den == 1)
		return (_To(static_cast<typename _To::rep>(_Dur.count())));
	else if (_CF::num != 1 && _CF::den == 1)
		return (_To(static_cast<typename _To::rep>(
			static_cast<_CR>(_Dur.count()) * static_cast<_CR>(_CF::num))));
	else if (_CF::num == 1 && _CF::den != 1)
		return (_To(static_cast<typename _To::rep>(
			static_cast<_CR>(_Dur.count()) / static_cast<_CR>(_CF::den))));
	else
		return (_To(static_cast<typename _To::rep>(
			static_cast<_CR>(_Dur.count()) * static_cast<_CR>(_CF::num)
			/ static_cast<_CR>(_CF::den))));
	}

