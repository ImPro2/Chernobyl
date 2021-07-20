# Official Documentation for Chernobyl Engine!

# Table of Contents

* [Structure of the Engine](#structure-of-the-engine)
  * [General Layout](#general-layout)
  * [SSO Model (System Subsystem Object Model)](#sso-model)
  * [Implementation of SSO Model](#implementation-of-sso-model)
* [How to use the engine](#how-to-use-the-engine)

# Structure of the Engine

## General Layout

You'll see that the engine is seperated into a couple of different folders,
the important ones being: Chernobyl, Sandbox, and Dependencies.
The dependencies are, just some external code used in the engine to make life easier.
The first 2 folders mentioned (Chernobyl and Sandbox) are 2 different 'projects'.
The Chernobyl project (aka the engine) is compiled as a static library and then linked
into Sandbox (executable). The sandbox project is just there to test the engine.

Later there will be a "Test" class which you can override from and perform tests on your own
(you'll just have to switch the configuration from "Dev" to "Test"), though the engine is too early
in development for tests.

## SSO Model

(aka System Subsystem Object Model)

This is a LOOOOONG section to read, you really don't have to read this if you don't want to.

Okay, you're wondering what on EARTH is this weird things. It's actually not that hard to understand (hopefully).
Basically, it's purpose is to design the engine that it isn't spaghetti code.
Let's go through this step by step.

System - think of it like the Renderer, Audio manager, Input system manager, Physics system, etc.
It is the thing responsible to do specific tasks, like the Renderer system is responsible
for rendering a model onto the screen, and the physics system is responsible to make something fall.
You see what I mean?
Now all systems has some things in common:
All systems has a `Init()` function.
All systems has a `Shutdown()` function.
All systems can create an instance of an object (more on that later).
So doesn't it make sense to group them together? Well, this is basically the design.
*NOTE: There is only one instance of a system, because you don't need more than one.
I guess you can create another instance of a system for various reasons, but for now I don't need it.*

Subsystem - This one is a little bit more complicated.
Here is an example: you have a HLSL shader that you want to cross-compile to GLSL.
Is that the renderer's job? Well, sort of, but it would just make it a mess.
SO, subsystems are introduced. They are simialar to systems (usually just one instance), though they
don't have `Init()` and `Shutdown()` methods. They can only do specific tasks.
Back to the example, you want to compile the HLSL shader to GLSL, so you call a function
from the `ShaderCompiler` subsystem, maybe like `CompileHLSLToGLSL(/*params*/)`.
Another example is that you create a shader. Now what? Where do you store it?
The obvious thing to do is to store it in some sort of container, like a shader library.
So then a `ShaderLibrary` subsystem exists.
That is basically it for the subsystem.

Object - This one is very simple.
So you have the renderer system and you want to create a shader, though
you don't want to have the raw shader handle. The SSO Model is designed for multiple implementations,
so giving the raw shader handle isn't a great idea. The obvious approach would be to
have a Shader class, which is essentially a wrapper. It will be implemented somewhere else.
So when you create an instance of the Shader class (, an object), it returns a shader object.
Very simple.
Though an object doesn't neccesarily have to have multiple implementations.
So you have a Mesh class which has everything a Mesh class needs (as you can see i have no idea what it needs).
It doesn't have to have multiple implementations like the Shader class does.

That is a basic overview of the SSO Model.

## Basic implementation of SSO Model

WARNING: THIS IS ABOUT TO GET CONFUSING

If you want to know every single detail how it is implemented, read further (you must be very interested XD).
I will have an `ISystem` class which is going to be an interface which each system will override.
This interface will have 2 virtual methods: `Init()` and `Shutdown()`.
It will have a vector of `ISubsystem` interfaces.
It will have two noraml methods called `CreateObject()` and `GetSubsystem()`, both of them
being templated. The `CreateObject()` method, well, creates and returns an object.
The `GetSubsystem()` method returns the desired subsystem.
Here is a code sample for using these functions:

```cpp
Ref<Shader> shader = Renderer->CreateObject<Shader>(/*params*/);
Renderer->GetSubsystem<ShaderCompiler>()->CompileHLSLToGLSL(shader);
```

The `CreateObject()` method switches statements of a static function of that class and returns the corresponding object like this:
```cpp
switch (T::GetStaticType())
{
	case "VertexBuffer":	return new VertexBuffer(/*params*/);
	case "Shader":			return new Shader(/*params*/);
	...
}
```

Every System, Subsystem and Object class must have this method: (because of the templated methods)
```cpp
static char* GetStaticType() { return "Shader"; /*could be anything else*/ }
```
So to simplify this, I will create a macro for doing this:
```cpp
.#define SSO_CLASS(x) static char* GetStaticType() { return #x; }
```

Now coming back to the `ISubsystem` interface (remember every system has a vector of these?).
This class won't contain anything, all subsystems will just inherit from this class.

Now moving on to where Systems are contained.
I will have a `System` class which will be a static class (only static members and methods)
which will contain an unordered map of `ISystem` and the name of the system (`char*`).
This class will contain 3 methods: `Init()`, `Shutdown()` and `GetSystem()`.
The `Init()` and `Shutdown` methods just initializes and shutdowns all of the systems.
The `GetSystem()` method returns a system. It is simialar to the `GetSubsystem()` method
of the `ISystem` class.
Here is the implementation of this method:
```cpp
template<class T>
ISystem* GetSystem()
{
	return mSystems[T::GetStaticType()];
}
```

I hope this covers the SSO Model pretty well XD

# How to use the Engine

Unfortunately the engine is too early in development to be used :(
Coming soon!