#pragma once

#include <functional>
#include <algorithm>
#include <vector>
#include <tuple>
#include <string>
#include <type_traits>
#include <utility>

class Process
{

private:
	struct ProcessData
	{
		std::string installationDir;
		std::string temporalDir;
	};

	using UndoProcessPtr = std::function<void(ProcessData &)>;

	using Functors = std::vector<UndoProcessPtr>;
	using Params = std::vector<ProcessData>;

	Functors m_functors;
	Params m_params;

	// these two functions unpack parameters into a function (like *args in Python)
	template<typename F, typename Tuple, size_t ...S >
	decltype(auto) apply_tuple_impl(F&& fn, Tuple&& t, std::index_sequence<S...>);
	template<typename F, typename Tuple>
	decltype(auto) apply_from_tuple(F&& fn, Tuple&& t);
public:

	Process() {};
	~Process() {};

	void process1(std::string &&installationDir);
	void process2(std::string &&temporalDir, std::string &&installationDir);

	void undoProcess1(ProcessData &processData);
	void undoProcess2(ProcessData &processData);

	void undoProcess();

	void reverseFunctors();
};