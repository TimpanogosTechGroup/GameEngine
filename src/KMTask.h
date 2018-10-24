/**
File: Threading.h
Purpose: Handles all threading

@author Isaac Draper
@version 1.0

NOTE: FOR NOW THIS IS WINDOWS SPECIFIC - will not work on any other OS

Copyright (c) 2018 All Rights Reserved
*/

#ifndef THREADING
#define THREADING

#include <cstdlib>
#include <Windows.h>
#include <vector>
#include <queue>

namespace utility {
	//Class Interfaces
	class IKMTaskData {
	public:
		IKMTaskData() {}
		IKMTaskData(const IKMTaskData&) {}
		IKMTaskData& operator = (const IKMTaskData&) {}
		virtual ~IKMTaskData() = 0 {};
	};

	//Type Definitions
	typedef void(*KMTaskFunc)(IKMTaskData*);

	class KMTask {
	private:
		KMTaskFunc		m_task;
		IKMTaskData*	m_data;
	public:
		KMTask(KMTaskFunc task, IKMTaskData* data) {
			m_task = task;
			m_data = data;
		}
		~KMTask() {
			if (m_data != NULL)
				delete m_data;
			m_data = NULL;
			m_task = NULL;
		}
		KMTaskFunc		GetTask() { return m_task; }
		IKMTaskData*	GetData() { return m_data; }
	protected:
	};

	class KMLock {
	private:
		CRITICAL_SECTION m_critsec;
	public:
		KMLock()
		{
			::InitializeCriticalSection(&m_critsec);
		}
		~KMLock()
		{
			::DeleteCriticalSection(&m_critsec);
		}
		void Lock()
		{
			::EnterCriticalSection(&m_critsec);
		}
		void Unlock()
		{
			::LeaveCriticalSection(&m_critsec);
		}
	protected:
	};

	class KMThread {
	public:
		KMThreadpool * m_pthreadpool;

		HANDLE			m_hthread;
		KMLock			m_lock;
		KMTask*			m_ptask;

		bool			m_brunning;
		bool			m_bpaused;
		unsigned int		m_uithreadID;
		DWORD			m_dwexit;

		void Begin();
		void End();
		DWORD ThreadProc();
	protected:
		static unsigned __stdcall cThreadProc(LPVOID _pThis)
		{
			return ((KMThread*)_pThis)->ThreadProc();
		}
	};


	class KMThreadpool {
	public:
		void Initialize(unsigned int uiTryMinNumThreads,
			unsigned int uiTryMaxNumThreads);
		void Shutdown();
		void AddTask(KMTaskFunc task, IKMTaskData* data);
		void BeginProcessing();
		void StopProcessing();
	private:
		std::queue<KMTask*>	m_qtaskList;
		std::vector<KMThread*>	m_vthreads;
		unsigned int		m_nactive;
		volatile bool		m_bprocess;
		//Singleton
		static KMThreadpool m_instance;
	};



}

#endif THREADING