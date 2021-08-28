#include "chpch.hpp"
#include "Allocations.hpp"

namespace CH
{

	uint32 Allocations::mTotalAllocations      = 0;
	uint32 Allocations::mTotalFreedAllocations = 0;
	uint32 Allocations::mLiveAllocations       = 0;

	void Allocations::ReportLiveAllocations()
	{
		CH_CORE_LOG(LogSeverity::Warn, "[MEMORY]: LiveAllocations: {}, TotalAllocated: {}, TotalFreed: {}", mTotalAllocations - mTotalFreedAllocations, mTotalAllocations, mTotalFreedAllocations);
	}

}

#include <Windows.h>

void* operator new(size_t size)
{
	CH::Allocations::mTotalAllocations += size;
	CH::Allocations::mLiveAllocations += size;

	return malloc(size);
}

void operator delete(void* block, size_t size)
{
	CH::Allocations::mTotalFreedAllocations += size;
	CH::Allocations::mLiveAllocations -= size;

	free(block);
}