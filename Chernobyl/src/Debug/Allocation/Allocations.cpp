#include "chpch.hpp"
#include "Allocations.hpp"

namespace CH
{

	uint32 Allocations::mTotalAllocations      = 0;
	uint32 Allocations::mTotalFreedAllocations = 0;

	void Allocations::ReportLiveAllocations()
	{
		CH_CORE_LOG(LogSeverity::Warn, "[MEMORY]: LiveAllocations: {1}, TotalAllocated: {2}, TotalFreed: {3}", mTotalAllocations - mTotalFreedAllocations, mTotalAllocations, mTotalFreedAllocations);
	}

}

void* operator new(size_t size)
{
	CH::Allocations::mTotalAllocations += size;

	return malloc(size);
}

void operator delete(void* block, size_t size)
{
	CH::Allocations::mTotalFreedAllocations += size;

	free(block);
}