/*
Lab 5: Producer-Consumer
Copyright (C) 31/03/2023  Adrien Dudon

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
#include <vector>

#include "Semaphore.h"

/*! 
 * \brief A thread-safe buffer
 */
template<typename T>
class SafeBuffer
{
    public:
        SafeBuffer(int t_size);

        /*!
         * \brief Put item in the buffer if no other thread is getting item fron it
         */ 
        void put(T item);
        
        /*!
         * \brief Get an item from the buffer if no other thead is putting item in it
         */ 
        T get();

    private:
        int m_size;
        std::vector<char> m_buffer;

        Semaphore m_spaces;
        Semaphore m_mutex;
        Semaphore m_items;
};


/* SafeBuffer.h ends here */
