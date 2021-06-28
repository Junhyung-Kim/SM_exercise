#!/usr/bin/env python3
import sysv_ipc
import numpy as np
 
 
class CShmReader :
 
    def __init__(self) :
 
        pass
 
    def doReadShm(self , key) :
 
        memory = sysv_ipc.SharedMemory(key)
 
        memory_value = memory.read()
        c = np.ndarray((2,), dtype=np.double, buffer=memory_value)

        print (c[1])
        print ("memory_value")
 
if __name__ == '__main__':
 
    s = CShmReader()
    s.doReadShm(1)



