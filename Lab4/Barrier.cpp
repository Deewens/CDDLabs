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
#include "Barrier.h"

#include <iostream>

Barrier::Barrier(int numThreads) : 
    numThreads(numThreads),
    count(0),
    mutex(1),
    turnstile1(0),
    turnstile2(1)
{
}

Barrier::~Barrier()
{
}

void Barrier::wait()
{
    // Wait for other thread to finish
    mutex.Wait();
    // So, this thread can run, we increment the count telling us how many thread finished their action
    count++;


    // If all the threads finished "they are all arrived to the barrier"
    if (count == numThreads)
    {
        
        turnstile2.Wait();
        std::cout << "They are all here!" << std::endl;
        // We signal to the thread that it can continue
        turnstile1.Signal();
    }

    mutex.Signal();
    turnstile1.Wait();
    turnstile1.Signal();

    mutex.Wait();

    count--;
    if (count == 0)
    {
        turnstile1.Wait();
        turnstile2.Signal();
    }

    mutex.Signal();
    turnstile2.Wait();
    turnstile2.Signal();
}
// Barrier.cpp ends here
