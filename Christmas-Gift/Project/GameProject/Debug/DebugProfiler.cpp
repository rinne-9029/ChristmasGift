#include "DebugProfiler.h"
#include "DebugPrint.h"

// DebugProfilerΜCX^X
DebugProfiler* DebugProfiler::ms_instance = nullptr;

// RXgN^
DebugProfiler::DebugProfiler()
	: Task(ETaskTag::eDebug,true)
{
	//m_remove = false;
}

// fXgN^
DebugProfiler::~DebugProfiler()
{
}

// CX^XζΎ
DebugProfiler* DebugProfiler::Instance()
{
	if (ms_instance == nullptr)
	{
		ms_instance = new DebugProfiler();
	}
	return ms_instance;
}

// ΤvͺJn
void DebugProfiler::StartTimer(std::string name)
{
	DebugProfiler* inst = Instance();
	auto& timers = inst->m_timers;

	DebugTimer* timer = timers[name];
	if (timer == nullptr)
	{
		timer = new DebugTimer();
		timers[name] = timer;
	}

	timer->Start();
}

// ΤvͺIΉ
void DebugProfiler::EndTimer(std::string name)
{
	DebugProfiler* inst = Instance();
	auto& timers = inst->m_timers;

	DebugTimer* timer = timers[name];
	if (timer == nullptr)
	{
		timer = new DebugTimer();
		timers[name] = timer;
	}

	timer->End();
}

// vͺΚπ`ζ
void DebugProfiler::Print()
{
	DebugProfiler* inst = Instance();
	auto& timers = inst->m_timers;

	if (timers.size() > 0)
	{
		DebugPrint::Print("‘‘‘‘‘‘‘ Profiler ‘‘‘‘‘‘‘");
		DebugPrint::Print("Delta:%f", CFPS::GetDeltaTime());
		for (auto& timer : timers)
		{
			DebugTimer* dt = timer.second;
			if (dt->IsEnd())
			{
				DebugPrint::Print
				(
					"%s:oίΤ[%f]:[%f]",
					timer.first.c_str(),
					dt->Get(),
					(dt->Get() / CFPS::GetDeltaTime()) * 100.0f
				);
			}
			else
			{
				DebugPrint::Print
				(
					"%s:E[%f]",
					timer.first.c_str(),
					dt->Get()
				);
			}
		}
		DebugPrint::Print("‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘");
	}
}

DebugTimer::DebugTimer()
	: freq({ 0 })
	, startCount({ 0 })
	, endCount({ 0 })
	, isEnd(false)
{
}

void DebugTimer::Start()
{
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&startCount);
	isEnd = false;
}

void DebugTimer::End()
{
	QueryPerformanceCounter(&endCount);
	isEnd = true;
}

float DebugTimer::Get() const
{
	if (isEnd)
	{
		return (float)(endCount.QuadPart - startCount.QuadPart) / freq.QuadPart;
	}
	else
	{
		LARGE_INTEGER tempCount;
		QueryPerformanceCounter(&tempCount);
		return (float)(tempCount.QuadPart - startCount.QuadPart) / freq.QuadPart;
	}
}

bool DebugTimer::IsEnd() const
{
	return isEnd;
}