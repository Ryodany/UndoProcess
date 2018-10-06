#include <iostream>

#include "Process.h"

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