#pragma once

#include "Chernobyl.hpp"

namespace CH::Sandbox
{

	class ITest
	{
	public:
		ITest(const String& name)
			: mName(name)
		{
		}

		~ITest() = default;

	public:
		virtual void OnInit()    {}
		virtual void OnDestroy() {}
		virtual void OnUpdate()  {}

	public:
		const String& GetName() const { return mName; }

	private:
		String mName;
	};

	class Tests
	{
	public:
		static void AddTest(ITest* test)
		{
			mTests.push_back(test);
		}

		static void SetCurrentTest(const String& name)
		{
			ITest* test = GetTest(name);

			test->OnInit();
			mCurrentTest = test;
		}

	public:
		static void Update()
		{
			mCurrentTest->OnUpdate();
		}

		static void Destroy()
		{
			mCurrentTest->OnDestroy();
		}

	public:
		static bool Exists(const String& name)
		{
			for (ITest* test : mTests)
			{
				if (test->GetName() == name)
					return true;
			}

			return false;
		}

		static ITest* GetTest(const String& name)
		{
			CH_CLIENT_ASSERT(Exists(name), "Invalid test name");

			for (ITest* test : mTests)
			{
				if (test->GetName() == name)
					return test;
			}

			CH_CLIENT_BREAK_S("How did this end up here??");
			return nullptr;
		}

	private:
		static Vector<ITest*> mTests;
		static ITest* mCurrentTest;
	};

}