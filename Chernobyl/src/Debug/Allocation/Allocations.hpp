#pragma once

#include "Core/Core.hpp"

void* operator new(size_t size);
void operator delete(void* block, size_t size);

namespace CH
{

	class Allocations
	{
	public:
		static void ReportLiveAllocations();

		static uint32 GetTotalAllocations()      { return mTotalAllocations;      }
		static uint32 GetTotalFreedAllocations() { return mTotalFreedAllocations; }

	private:
		static uint32 mTotalAllocations;
		static uint32 mTotalFreedAllocations;
		static uint32 mLiveAllocations;

	private:
		// let these functions access class members
		friend void* ::operator new(size_t size);
		friend void ::operator delete(void* block, size_t size);
	};

}