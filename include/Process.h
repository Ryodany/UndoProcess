#pragma once

#include <functional>
#include <algorithm>
#include <vector>
#include <string>

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