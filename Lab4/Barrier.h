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
#pragma once
#include "Semaphore.h"

/*!
 * \brief Reusable Barrier class, thread used in this class will all wait to each other before continuing
 */
class Barrier{
    private:
    int numThreads;
    int count;

    Semaphore mutex;
    Semaphore turnstile1;
    Semaphore turnstile2;

    public:
    Barrier(int numThreads);
    
    virtual ~Barrier();
    /*!
     * \brief Wait for all the threads to have reach the "Barrier" before continuing current thread execution
     */
    void wait();  
};


/* Barrier.h ends here */
