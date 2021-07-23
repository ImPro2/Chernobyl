#include "sandboxpch.hpp"
#include "Test.hpp"

namespace CH::Sandbox
{

	Vector<ITest*> Tests::mTests;
	ITest* Tests::mCurrentTest = nullptr;

}