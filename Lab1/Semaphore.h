#ifndef SEMAPHORE_H
#define SEMAPHORE_H 
#include <mutex>
#include <condition_variable>
#include <chrono>

/*! \class Semaphore
    \brief A Semaphore Implementation

   Uses C++11 features such as mutex and condition variables to implement Semaphore

*/
class Semaphore
{
private:
    unsigned int m_uiCount; /*!< Holds the Semaphore count */
    std::mutex m_mutex;
    std::condition_variable m_condition;

public:
    Semaphore(unsigned int uiCount=0)
          : m_uiCount(uiCount) { };

    /*! 
     * \brief Block the current thread until another thread call Signal 
    */
    void Wait();

    /*! 
     * \brief Block the current thread until another thread call Signal or until timeout
     * \param crRelTime Timeout duration, thread will be unlocked after this time
     * \returns false if it timeout while the Semaphore has not received any Signal, true if thread has been unlocked following a Signal
    */
    template< typename R,typename P >
    bool Wait(const std::chrono::duration<R,P>& crRelTime);

    /*! 
     * \brief Signal a random waiting thread to stop waiting
    */
    void Signal();
};

#endif
