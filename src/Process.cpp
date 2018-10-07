#include <iostream>

#include "Process.h"

// these two functions unpack parameters into a function (like *args in Python)
template<typename F, typename Tuple>
decltype(auto) Process::apply_from_tuple(F&& fn, Tuple&& t)
{
	std::size_t constexpr tSize
		= std::tuple_size<typename std::remove_reference<Tuple>::type>::value;
	return apply_tuple_impl(std::forward<F>(fn),
		std::forward<Tuple>(t),
		std::make_index_sequence<tSize>());
}

template<typename F, typename Tuple, size_t ...S >
decltype(auto) Process::apply_tuple_impl(F&& fn, Tuple&& t, std::index_sequence<S...>)
{
	return std::forward<F>(fn)(std::get<S>(std::forward<Tuple>(t))...);
}

void Process::process1(std::string &&installationDir)
{
	ProcessData processData = { installationDir };
	m_functors.push_back(std::bind(&Process::undoProcess1, this, processData));
	m_params.push_back(processData);

	std::cout << installationDir << std::endl;
}

void Process::process2(std::string &&temporalDir, std::string &&installationDir)
{
	ProcessData processData = { installationDir, temporalDir };
	m_functors.push_back(std::bind(&Process::undoProcess2, this, processData));
	m_params.push_back(processData);

	std::cout << temporalDir << " " << installationDir << std::endl;
}

void Process::undoProcess1(ProcessData &processData)
{
	std::cout << processData.installationDir << std::endl;
}

void Process::undoProcess2(ProcessData &processData)
{
	std::cout << processData.temporalDir << " " << processData.installationDir << std::endl;
}

void Process::undoProcess()
{
	reverseFunctors();

	Params::iterator itParams;
	Functors::iterator itFunctor;
	for (itFunctor = m_functors.begin(), itParams = m_params.begin();
		itFunctor != m_functors.end() && itParams != m_params.end();
		itFunctor++, itParams++)
	{
		(*itFunctor)(*itParams);
	}
}

void Process::reverseFunctors()
{
	std::reverse(m_functors.begin(), m_functors.end());
	std::reverse(m_params.begin(), m_params.end());
}