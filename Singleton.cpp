//------------------------------------------------------------------------------
//! @file       Singleton.cpp
//!
//! @copyright  Copyright(C)2010-2015 Hach Company
//!             ALL RIGHTS RESERVED
//!
//! @author     Alan Schuppan

#include <new>
#include <iostream>
#include <unistd.h>

#include "Singleton.hpp"

#define LOG_INFO // Enable LogInfo()

//##############################################################################
// CSingleton
//##############################################################################
//! Implements the base class for all singletons.
//##############################################################################

#ifdef CSINGLETON

//------------------------------------------------------------------------------
// void CSingleton::Truncate(std::string &text, uint32_t maxLength)
//
//! Static function limits the specified text to the specified maximum length by
//! truncating the extra characters if any.
//
void CSingleton::Truncate(std::string &text, uint32_t maxLength) {
    uint32_t Length = text.size();
    if (Length > maxLength) {
        text.erase(maxLength, Length - maxLength);
    }
}

//------------------------------------------------------------------------------
// CSingleton::CSingleton(const std::string &name)
//
//! Constructor names the singleton.
//
CSingleton::CSingleton(const std::string &name) : mName(name) {
    Truncate(mName, cMaxNameLength);
    #ifdef LOG_INFO
        std::cerr << "CSingleton::CSingleton(): Creating singleton: \""
                  << mName << "\"..." << std::endl;
    #endif // LOG_INFO
}

//------------------------------------------------------------------------------
// CSingleton::CSingleton(const std::string &name)
//
//! Virtual destructor does nothing.
//
CSingleton::~CSingleton() {
}

#endif // CSINGLETON

//##############################################################################
// CSingletonHost
//##############################################################################
//! Hosts and provides the pointer to the associated singleton, creating it if
//! necessary by calling the provided creator function as needed.
//##############################################################################

#ifdef CSINGLETON

//------------------------------------------------------------------------------
// CSingletonHost::CSingletonHost(FCreator create)
//
//! Constructor saves the pointer to the function that can create the
//! singleton.
//
CSingletonHost::CSingletonHost(FCreator create) : mCreate(create),
                               mpSingleton(0), mBusy(0) {
}

//------------------------------------------------------------------------------
// CSingletonHost::~CSingletonHost()
//
//! Destructor deletes the singleton.
//
CSingletonHost::~CSingletonHost() {
    delete mpSingleton;
}

//------------------------------------------------------------------------------
// CSingleton &CSingletonHost::Get()
//
//! Function returns a reference to the singleton, creating it if necessary. A
//! simple mechanism is provided to reduce that chance that two competing
//! threads will create two singletons.
//
CSingleton &CSingletonHost::Get() {
    while (mBusy != 0) { // Wait for previous thread to finish
        usleep(10000);
    }
    mBusy = 1; // Block other threads from creating a singleton.
    if (mpSingleton == nullptr) {
        std::string Name;
        mpSingleton  = mCreate(Name);
        if (mpSingleton == nullptr) {
            std::cerr << "CSingletonHost::Get(): Could not create singleton \""
                      << Name << "\"." << std::endl;
        }
    }
    mBusy = 0; // After the singleton has been created, allow other threads in.
    return *mpSingleton;
}

//------------------------------------------------------------------------------
// void CSingletonHost::Release()
//
//! Function destroys the singleton. The next access will recreate it, however.
//
void CSingletonHost::Release() {
    while (mBusy != 0) { // Wait for previous thread to finish
        //CTask::Sleep(10);
        usleep(10000);
    }
    mBusy = 1; // Block other threads from creating a singleton.
    delete mpSingleton;
    mpSingleton = 0;
    mBusy = 0; // Singleton has been created, so allow other threads in.
}

#else // !CSINGLETON

//------------------------------------------------------------------------------
// CSingletonHost::CSingletonHost(const std::string &name)
//
//! Constructor saves the singleton name and a pointer to the function that can
//! create the singleton.
//
CSingletonHost::CSingletonHost(const std::string &name) : mName(name),
                                                          mpSingleton(0),
                                                          mBusy(0) {
}

//------------------------------------------------------------------------------
// CSingletonHost::~CSingletonHost()
//
//! Base class destructor does nothing, but will be overriden by the template.
//
CSingletonHost::~CSingletonHost() {
}

//------------------------------------------------------------------------------
// bool CSingletonHost::Exists() const
//
//! Function returns true if the underlying singleton has already been created.
//
bool CSingletonHost::Exists() const {
    return (mpSingleton != 0);
}

//------------------------------------------------------------------------------
// CSingleton &CSingletonHost::Get()
//
//! Function returns a pointer to the singleton, creating it if necessary. A
//! simple mechanism is provided to reduce that chance that two competing
//! threads will create two singletons.
//
void *CSingletonHost::Get() {
    while (mBusy != 0) { // Wait for previous thread to finish
        usleep(10000);
    }
    mBusy = 1; // Block other threads from creating a singleton.
    if (mpSingleton == nullptr) {
        mpSingleton  = Create();
        if (mpSingleton == nullptr) {
            std::cerr << "CSingletonHost::Get(): Could not create singleton \""
                      << mName << "\"." << std::endl;
        }
    }
    mBusy = 0; // Singleton has been created, so allow other threads in.
    return mpSingleton;
}

#endif // !CSINGLETON

//##############################################################################
// CThread
//##############################################################################
//! Privides the base class for singleton threads. The behavior of the thread is
//! defined by overriding the virtual Execute function.
//##############################################################################

#ifdef THREAD

//------------------------------------------------------------------------------
// CThread::CThread(const std::string &name)
//
//! Constructor creates the named thread class.
//
CThread::CThread(const std::string &name) : CSingleton(name), mpTask(0) {
}

//------------------------------------------------------------------------------
// CThread::CThread(const std::string &name)
//
//! Destructor terminates the thread.
//
CThread::~CThread() {
    Terminate();
}

//------------------------------------------------------------------------------
// uint32_t CThread::Task(void *pdata)
//
//! Static function is the thread task. It repeatedly calls the overridden
//! Execute function until it returns false, at which time the Result is
//! returned.
//
uint32_t CThread::Task(void *pdata) {
    CThread *pThread = static_cast<CThread *>(pdata);
    uint32_t Result = 0;
    while (pThread->Execute(Result));
    return Result;
}

//------------------------------------------------------------------------------
// HRESULT CThread::Start(CTask::eTaskPri priority)
//
//! Function starts the thread at the specified priority after passing a pointer
//! to this class, so the Execute function can be called.
//
HRESULT CThread::Start(CTask::eTaskPri priority) {
    HRESULT hResult;
    mpTask = new(std::nothrow) CTask(mName.c_str(), Task, true, hResult, this,
                                     priority);
    if (hResult == ERR_HR_SUCCESS) {
        LogInfo("CThread::Start(): Started task \"%s\" (0x%02X / %u).",
                mName.c_str(), mpTask->GetId(), mpTask->GetId());
    }
    else {
        delete mpTask;
        mpTask = 0;
        LogError("CThread::Start(): Failed to start task \"%s\".", mName.c_str());
    }
    return hResult;
}

//------------------------------------------------------------------------------
// void CThread::Terminate()
//
//! Function terminates the thread and deletes the task.
//
void CThread::Terminate() {
    if (mpTask != nullptr) {
        mpTask->Terminate();
        delete mpTask;
        mpTask = nullptr;
    }
}

#endif // THREAD

//##############################################################################
// CTest
//##############################################################################
//! Creates a simple singleton and tests it.
//##############################################################################

#ifdef TEST
#ifdef CSINGLETON
class CTest : public CSingleton {
#else // !CSINGLETON
class CTest {
#endif // !CSINGLETON
    int mValue;
public:
    CTest();
    virtual ~CTest();
    int  Value() const;
    void Value(int value);
#ifdef CSINGLETON
    static CSingleton *Create();
#endif // CSINGLETON
};

CTest::CTest() : mValue(0) {
}

CTest::~CTest() {
}

int  CTest::Value() const {
    return mValue;
}

void CTest::Value(int value) {
    mValue = value;
}

#ifdef CSINGLETON
CSingleton *CTest::Create() {
    return new(std::nothrow) CTest;
}
#endif // CSINGLETON

#ifdef CSINGLETON
    TSingletonHost<CTest> MyTest("MyTest", CTest::Create);
#else // !CSINGLETON
    TSingletonHost<CTest> MyTest("MyTest");
#endif // !CSINGLETON

bool SingletonTest() {
    TSingletonHost<CTest> Test("Test", CTest::Create);
    int Value = Test.Get().Value();
    if (Value != 0) {
        return false;
    }
    Test.Get().Value(3);
    Value = Test.Get().Value();
    if (Value != 3) {
        return false;
    }
    return true;
}
#endif // TEST

//------------------------------------------------------------------------------
