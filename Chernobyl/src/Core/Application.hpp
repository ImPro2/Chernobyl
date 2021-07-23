#pragma once

#include "ExitCode.hpp"
#include "Core.hpp"
#include "SSO/System.hpp"
#include "StartupArgs.hpp"

namespace CH
{

	class Application
	{
	public:
		Application(ApplicationStartupArguments args);
		~Application();

		void Run();
		void Close();

	private:
		void OnEvent(Event& e);
		void Event_OnWindowResize(WindowResizeEvent& e);
		void Event_OnWindowClose(WindowCloseEvent& e);
		void Event_OnAppDestroy(AppDestroyEvent& e);

	protected:
		virtual void Init()   {}
		virtual void Update() {}
		virtual void Shutdown() {}

	public:
		// getters

		static Application* Get() { return sInstance; }

		ApplicationStartupArguments GetStartupArguments() const { return mStartupArgs; }
		bool IsRunning()		const { return mRunning;  }
		ExitCode GetExitCode()	const { return mExitCode; }

	private:
		static Application* sInstance;
		ApplicationStartupArguments mStartupArgs;
		Ref<IWindow> mWindow;
		bool mRunning = true;
		ExitCode mExitCode = ExitCode::Success;
	};

	// Defined in Client

	extern Application* CreateApplication(ApplicationStartupArguments args);

}