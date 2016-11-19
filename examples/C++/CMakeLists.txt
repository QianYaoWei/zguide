CMAKE_MINIMUM_REQUIRED(VERSION 2.8)                                                                                                                                                                                                     

# 编译选项                                                                                                       
IF( CMAKE_BUILD_TYPE STREQUAL "Debug" )                                                                          
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wall -Wno-unused-variable -pthread")                  
ELSE( CMAKE_BUILD_TYPE STREQUAL "Debug" )                                                                        
    SET(CMAKE_BUILD_TYPE "Release")                                                                              
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O2 -pthread")                                            
ENDIF( CMAKE_BUILD_TYPE STREQUAL "Debug" )                                                                       

SET(INCLUDE_DIR_List
${CMAKE_CURRENT_SOURCE_DIR}
)

INCLUDE_DIRECTORIES(${INCLUDE_DIR_List})

SET(COMMONLIB
zmq
)

#=========================================
# ZMQ_REP
ADD_EXECUTABLE(hwserver hwserver.cpp)
TARGET_LINK_LIBRARIES(hwserver
${COMMONLIB}
)

# ZMQ_REQ
ADD_EXECUTABLE(hwclient hwclient.cpp)
TARGET_LINK_LIBRARIES(hwclient
${COMMONLIB}
)
#>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


#=========================================
# ZMQ_PUB
ADD_EXECUTABLE(wuserver wuserver.cpp)
TARGET_LINK_LIBRARIES(wuserver
${COMMONLIB}
)

# ZMQ_SUB
ADD_EXECUTABLE(wuclient wuclient.cpp)
TARGET_LINK_LIBRARIES(wuclient
${COMMONLIB}
)
#>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

#=========================================
# ZMQ_PUSH generate and send msg to worker
ADD_EXECUTABLE(taskvent taskvent.cpp)
TARGET_LINK_LIBRARIES(taskvent
${COMMONLIB}
)

# ZMQ_PULL: dealing msg from generator. ZMQ_PUSH: send dealing results to sink
ADD_EXECUTABLE(taskwork taskwork.cpp)
TARGET_LINK_LIBRARIES(taskwork
${COMMONLIB}
)

# ZMQ_PULL: recieve msg dealing results from workers
ADD_EXECUTABLE(tasksink tasksink.cpp)
TARGET_LINK_LIBRARIES(tasksink
${COMMONLIB}
)
#>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


#=========================================
# Can execute the commands sent by tasksink2
ADD_EXECUTABLE(taskwork2 taskwork2.cpp)
TARGET_LINK_LIBRARIES(taskwork2
${COMMONLIB}
)

# Can send commands to workers
ADD_EXECUTABLE(tasksink2 tasksink2.cpp)
TARGET_LINK_LIBRARIES(tasksink2
${COMMONLIB}
)
#>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


#=========================================
# REQ and REP with broker process between them
# ZMQ_REQ
ADD_EXECUTABLE(rrclient rrclient.cpp)
TARGET_LINK_LIBRARIES(rrclient
${COMMONLIB}
)

# ZMQ_ROUTER
# ZMQ_DEALER
ADD_EXECUTABLE(rrbroker rrbroker.cpp)
TARGET_LINK_LIBRARIES(rrbroker
${COMMONLIB}
)

# ZMQ_REP
ADD_EXECUTABLE(rrworker rrworker.cpp)
TARGET_LINK_LIBRARIES(rrworker
${COMMONLIB}
)
#>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

#=========================================
# REQ and REP
# broker and workers are all in the same process
# different worker different thread
ADD_EXECUTABLE(mtserver mtserver.cpp)
TARGET_LINK_LIBRARIES(mtserver
${COMMONLIB}
)
#>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


#=========================================
# ZMQ_ROUTER
# ZMQ_DEALER
# the optimization of broker
ADD_EXECUTABLE(msgqueue msgqueue.cpp)
TARGET_LINK_LIBRARIES(msgqueue
${COMMONLIB}
)
#>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


#=========================================
# pair socket
# Signaling Between Threads
ADD_EXECUTABLE(mtrelay mtrelay.cpp)
TARGET_LINK_LIBRARIES(mtrelay
${COMMONLIB}
)
#>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


#=========================================
# Node Coordination, avoid msg lost when use the PUB-SUB pattern
# synsub counts the connection number from syncsubs
ADD_EXECUTABLE(syncpub syncpub.cpp)
TARGET_LINK_LIBRARIES(syncpub
${COMMONLIB}
)

ADD_EXECUTABLE(syncsub syncsub.cpp)
TARGET_LINK_LIBRARIES(syncsub
${COMMONLIB}
)
#>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


#=========================================
# PUB-SUB subscribe specific content
ADD_EXECUTABLE(psenvpub psenvpub.cpp)
TARGET_LINK_LIBRARIES(psenvpub
${COMMONLIB}
)

ADD_EXECUTABLE(psenvsub psenvsub.cpp)
TARGET_LINK_LIBRARIES(psenvsub
${COMMONLIB}
)
#>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

#=========================================
# lazy pirate pattern
#
# REQ->REP
#
ADD_EXECUTABLE(lpclient lpclient.cpp)
TARGET_LINK_LIBRARIES(lpclient
${COMMONLIB}
)

ADD_EXECUTABLE(lpserver lpserver.cpp)
TARGET_LINK_LIBRARIES(lpserver
${COMMONLIB}
)
#>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

#=========================================
# simple pirate pattern
# combine lazy pirate pattern and LRU queue
# lpclient can connect spqueue directly
#
# REQ->ROUTER+ROUTER+REQ
#
ADD_EXECUTABLE(spqueue spqueue.cpp)
TARGET_LINK_LIBRARIES(spqueue
${COMMONLIB}
)

ADD_EXECUTABLE(spworker spworker.cpp)
TARGET_LINK_LIBRARIES(spworker
${COMMONLIB}
)
#>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


#=========================================
#
#
# REQ->ROUTER+ROUTER->DEALER
#
ADD_EXECUTABLE(ppqueue ppqueue.cpp)
TARGET_LINK_LIBRARIES(ppqueue
${COMMONLIB}
)

ADD_EXECUTABLE(ppworker ppworker.cpp)
TARGET_LINK_LIBRARIES(ppworker
${COMMONLIB}
)
#>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


# identity.cpp
# interrupt.cpp
# lbbroker.cpp
# lbbroker2.cpp
# mdbroker.cpp
# mdcliapi.hpp
# mdcliapi2.hpp
# mdclient.cpp
# mdclient2.cpp

#cmake  -D CMAKE_BUILD_TYPE=Debug ..
#cmake  -D CMAKE_BUILD_TYPE=Release ..

