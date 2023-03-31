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

#include "SafeBuffer.h"

template <typename T>
SafeBuffer<T>::SafeBuffer(int t_size) : 
    m_size(t_size),
    m_spaces(t_size),
    m_mutex(1),
    m_items(0)
    
{
}

template <typename T>
void SafeBuffer<T>::put(T item)
{
    // Wait until there is enough place in the Buffer
    m_spaces.Wait();

    // Wait that no one is currently writting to the buffer before continuing
    m_mutex.Wait();
    
    m_buffer.push_back(item);
   
    // Writting in buffer finish, we can free the mutex for other threads
    m_mutex.Signal();
    // This event can be free from the Buffer, thus, freeing for another thread
    m_items.Signal();
}

template <typename T>
T SafeBuffer<T>::get()
{
    m_items.Wait();
    m_mutex.Wait();

    T c = m_buffer.front();
    m_buffer.erase(m_buffer.begin());

    m_mutex.Signal();
    m_spaces.Signal();
    
    return c;
}

template class SafeBuffer<char>;
