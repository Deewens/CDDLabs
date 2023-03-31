#include <iostream>
#include <thread>
#include <vector>
#include <random>
#include <memory>
#include "SafeBuffer.h"


static const int num_threads = 10;
const int size = 20;

int characterCount = 0;


std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<int> dist(0, 25);
std::uniform_real_distribution<double> delay(0, 1);

/*! \fn producer
    \brief Creates chars and adds them to buffer
*/
void producer(std::shared_ptr<SafeBuffer<char>> theBuffer, int numLoops){
    for(int i=0;i<numLoops;++i) 
    {
        // Generate random character from A to Z
        char c = 'a' + dist(gen);
        
        theBuffer->put(c);
        std::cout << "Put " << c << " into buffer." << std::endl;

        std::this_thread::sleep_for(std::chrono::duration<double>(delay(gen))); 
    }

    theBuffer->put('X');
}

/*! \fn consumer
    \brief Takes chars from buffer and consumes them
*/
void consumer(std::shared_ptr<SafeBuffer<char>> theBuffer)
{
    int count = 0;
    while (true)
    {
        char c = theBuffer->get();
        std::cout << "Character taken from buffer: " << c << std::endl;
        count++;

        if (c == 'X')
        {
            std::cout << "X has been reached, exiting thread..." << std::endl;
            characterCount += count;
            break;
        }

        std::this_thread::sleep_for(std::chrono::duration<double>(delay(gen)));
    }
}

int main(void){
    std::vector<std::thread> producerThreads(num_threads);
    std::vector<std::thread> consumerThreads(num_threads);

    std::shared_ptr<SafeBuffer<char>> aBuffer(new SafeBuffer<char>(size));

    /**< Launch the threads  */
    for(std::thread& t : producerThreads)
    {
        t = std::thread(producer, aBuffer, 10);
    }

    for (std::thread& t : consumerThreads)
    {
      t = std::thread(consumer, aBuffer);
    }

    
    /**< Join the threads with the main thread */
    for (auto& v : producerThreads)
    {
          v.join();
    }

    for (auto& v : consumerThreads)
    {
        v.join();
    }

    std::cout << "Character count: " << characterCount << std::endl;
    return 0;
}
