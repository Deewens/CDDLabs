/*
Lab 4: Reusable Barrier
Copyright (C) 25/03/2023  Adrien Dudon

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "Semaphore.h"

/*! \class Semaphore
    \brief A Semaphore Implementation

   Uses C++11 features such as mutex and condition variables to implement Semaphore

*/
void Semaphore::Wait()
{
    // Create ownership on a mutex
    std::unique_lock< std::mutex > lock(m_mutex);
    
    // Block the current thread until m_uiCount > 0
    m_condition.wait(lock,[&]()->bool{ return m_uiCount>0; });

    // Decrement m_uiCount after the current thread has been unlocked (m_uiCount > 0)
    --m_uiCount;
}

template< typename R,typename P >
bool Semaphore::Wait(const std::chrono::duration<R,P>& crRelTime)
{
    // Create ownership on a mutex
    std::unique_lock< std::mutex > lock(m_mutex);

    // Block th current thread util m_uiCount > 0 OR after timeout following crRelTime duration
    if (!m_condition.wait_for(lock,crRelTime,[&]()->bool{ return m_uiCount>0; })){
	  return false;
    }

    // Decrement m_uiCount after the current thread has been unlocked (m_uiCount > 0)
    --m_uiCount;

    return true;
}

void Semaphore::Signal()
{
    // Create ownership on a mutex
    std::unique_lock< std::mutex > lock(m_mutex);

    // Imcrement m_uiCount, so, unlock every thread currently being locked (wait operation)
    ++m_uiCount;

    // Notify the waiting thread
    m_condition.notify_one();
}
