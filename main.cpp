#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <string>
using namespace std;
 
class CSharedMemroy
{
 
private :
    
    int m_shmid;   
    key_t m_key;
 
 
public :
 
    void setShmId(int key);
    int getShmId();
    void setKey(key_t key);
 
    void setupSharedMemory(int size);
    void attachSharedMemory();
    void close();

    double *m_shared_memory;
};
 
 
void CSharedMemroy::setShmId( int id )
{
    m_shmid = id;
}
 
 
void CSharedMemroy::setKey( key_t key )
{
    m_key = key;
}
 
 
void CSharedMemroy::setupSharedMemory(int size)
{
   // Setup shared memory, 11 is the size
   if ((m_shmid = shmget(m_key, size , IPC_CREAT | 0666)) < 0)
   {
      printf("Error getting shared memory id");
      exit( 1 );
   }
}
 
 
void CSharedMemroy::attachSharedMemory()
{
   // Attached shared memory
   m_shared_memory = (double*)shmat(m_shmid,NULL,0);
   if ((*m_shared_memory) == -1)
   {
      printf("Error attaching shared memory id");
      exit(1);
   }
}
 
 
void CSharedMemroy::close()
{
   sleep(3);
 
   // Detach and remove shared memory
   shmctl(m_shmid,IPC_RMID,NULL);
 
}
 
 
int main(int argc, const char **argv)
{
    CSharedMemroy m;
 
    m.setKey(1);
    m.setupSharedMemory(sizeof(double) * 2);
    m.attachSharedMemory();
    m.m_shared_memory[0] = 1.0;//[0] = 0.0;
    m.m_shared_memory[1] =20.0;
    sleep(3);
    m.close();
    return 0;
}
