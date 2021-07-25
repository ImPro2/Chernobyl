# Tests

A test is a way to test the engine and see if things works.

# Creating Tests

After the engine is [setup](/Setup.md), go to the `Sandbox` project and go into the `Tests/Tests/` folder.
Firstly, create 2 new files, called like this: `SampleTest.hpp`, and `SampleTest.cpp`. (You can call it whatever you like,
though the file must end in `Test`)
In the header file, write this code:
```cpp
#pragma once

#include "../Test.hpp"

namespace CH::Sandbox::Test
{

	class SampleTest : public ITest
	{
	public:
		SampleTest();
		~SampleTest();

		void OnInit() override;
		void OnDestroy() override;
		void OnUpdate() override;

		// ...
	};

}
```
The name of the class is the same as the name of the file.
You can now go ahead and implement that in the cpp file :D

*NOTE: in the constructor you need to give a string to the `ITest` constructor, 
which will basically be the name of the test. The string should be the name of the class.*

Now that you have written your test, you need to go to the `src/` directory and go to `SandboxApp.cpp`.
In the `Sandbox::Init()` method, you can add another line like so:
```cpp
Tests::AddTest("");	// you can ignore these lines
// ...

Tests::AddTests(new Test::SampleTest() /*Should be the class name*/);	// you should add this line

Tests::SetCurrentTest(/*name of the class in string form*/);	// you should change this line
```

Now you can run the test by pressing `F5` or the `Local Windows Debugger` button on top!