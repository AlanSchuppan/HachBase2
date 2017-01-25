//------------------------------------------------------------------------------
//! @file       Singleton.hpp
//!
//! @copyright  Copyright(C)2010-2015 Hach Company
//!             ALL RIGHTS RESERVED
//!
//! @author     Alan Schuppan

#ifndef SINGLETON_HPP
#define SINGLETON_HPP

#include <string>
//#include "OsAbstraction/CTask.hpp"

#define CSINGLETON // Define if a singleton base class is used
//#define THREAD     // Define if a singleton thread class is used
//#define TEST

//##############################################################################
// CSingleton
//##############################################################################
//! Implements the base class for all singletons.
//##############################################################################

#ifdef CSINGLETON

class CSingleton {
protected:
    static const uint32_t cMaxNameLength = 13; // Maximum thread name length
    std::string mName;

    static void Truncate(std::string &text, uint32_t maxLength);
public:
    CSingleton(const std::string &name);
    CSingleton(const CSingleton &other) = delete;
    CSingleton(CSingleton &&other) = delete;
    virtual ~CSingleton();
    std::string Name() const;
    void        Name(const std::string &name);
};

//! Gets the singleton name.
inline std::string CSingleton::Name() const {
    return mName;
}

//! Sets the singleton name, limiting it to 13 characters (the maximum for a
//! thread).
inline void CSingleton::Name(const std::string &name) {
    mName = name;
    Truncate(mName, cMaxNameLength);
}

#endif // CSINGLETON

//##############################################################################
// CSingletonHost
//##############################################################################
//! Hosts and provides the pointer to the associated singleton, creating it if
//! necessary by calling the provided creator function as needed.
//##############################################################################

#ifdef CSINGLETON

class CSingletonHost {
protected:
    // Name is intentionally non-const so it can be output:
    typedef CSingleton *(*FCreator)(std::string &name);
    FCreator    mCreate;
    CSingleton *mpSingleton;
    volatile uint8_t mBusy;
public:
    CSingletonHost(FCreator create);
    ~CSingletonHost();
    bool Exists() const;
    CSingleton &Get();
    void Release();
};

//! Returns true if the underlying singleton has already been created.
inline bool CSingletonHost::Exists() const {
    return (mpSingleton != nullptr);
}

template<class T>
class TSingletonHost : public CSingletonHost {
public:
    TSingletonHost(FCreator create) : CSingletonHost(create) {  }
    T &Get() { return static_cast<T &>(CSingletonHost::Get()); }
};

#else // !CSINGLETON

class CSingletonHost {
protected:
    std::string mName;
    void *mpSingleton;
    volatile uint8_t mBusy;

    virtual void *Create() = 0;
public:
    CSingletonHost(const std::string &name);
    virtual ~CSingletonHost();
    bool Exists() const;
    void *Get();
};

template<class T>
class TSingletonHost : public CSingletonHost {
    virtual void *Create() { return new T; }
public:
    TSingletonHost(const std::string &name) : CSingletonHost(name) {  }
    virtual ~TSingletonHost() { delete static_cast<T *>(mpSingleton); }
    T &Get() { return *static_cast<T *>(CSingletonHost::Get()); }
    void Release() { delete static_cast<T *>(mpSingleton); mpSingleton = 0; }
};

#endif // CSINGLETON

//##############################################################################
// CThread
//##############################################################################
//! Provides the base class for threads. The behavior of the thread is defined
//! by overriding the virtual Execute function.
//##############################################################################

#ifdef THREAD

class CThread : public CSingleton {
    static uint32_t Task(void *pdata);
protected:
    CTask *mpTask;

    virtual bool Execute(uint32_t &result) = 0;
public:
    CThread(const std::string &name);
    virtual ~CThread();
    HRESULT Start(CTask::eTaskPri priority = CTask::eTaskPri_Norm);
    void Terminate();
};

#endif // THREAD

//------------------------------------------------------------------------------

#ifdef TEST
bool static SingletonTest();
#endif // TEST

#endif // SINGLETON_HPP
