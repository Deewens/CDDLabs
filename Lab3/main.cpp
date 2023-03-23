#include "Semaphore.h"
#include <iostream>
#include <thread>
#include <vector>


static const int num_threads = 100;
int sharedVariable=0;


/*! \fn updateTask
    \brief An Implementation of Mutual Exclusion using Semaphores

   Uses C++11 features such as mutex and condition variables to implement an example of a rendezvous for threads

*/
/*! displays a message that is split in to 2 sections to show how a rendezvous works*/
void updateTask(std::shared_ptr<Semaphore> firstSem, int numUpdates)
{
    // Wait only if another thread is already is accessing the resource (in this case, the current thread will be blocked because Semaphore count is 0)
    // It won't wait if count is 1, but will decrement the counter, so other thread will wait
    // So, this line either wait for another thread to signal, and when another thread signaled the current one, it will tell others to wait until done
    firstSem->Wait();
    
    for(int i=0;i<numUpdates;i++){
        //UPDATE SHARED VARIABLE HERE!
        sharedVariable++;
    }

    // Signal to other thread that this thread is done updating the sharedVariable
    firstSem->Signal();
}


int main(void){
  std::vector<std::thread> vt(num_threads);

  // Set the semaphore count to 1 initially
  std::shared_ptr<Semaphore> aSemaphore( new Semaphore(1));
  
  /**< Launch the threads  */
  int i=0;
  for(std::thread& t: vt){
    t=std::thread(updateTask,aSemaphore,1000);
  }
  
  std::cout << "Launched from the main\n";

  /**< Join the threads with the main thread */
  for (auto& v :vt){
      v.join();
  }
  
  std::cout << "Should print 100,000" << std::endl;
  std::cout << sharedVariable << std::endl;
  
  return 0;
}
