#include "Channel.hpp"

//#include <iostream>

 namespace portal
 {
     
     
     
     
 Channel::Channel(int port_, int conn_) {
     port = port_;
     conn = conn_;
     
     printf("%s: Init\n", __func__);

//     protocol =
     
//     auto wptr = std::shared_ptr<Channel>( this, [](Channel*){} );

//     protocol.setDelegate(shared_from_this());
//     std::weak_ptr<SimpleDataPacketProtocolDelegate> weakPointer = *this;
//     protocol.setDelegate(shared_from_this());
     
//     SimpleDataPacketProtocol *p = new SimpleDataPacketProtocol();
//     protocol = std::unique_ptr<SimpleDataPacketProtocol>(p);
//     std::unique_ptr<Child>(new Child(2));
     protocol.setDelegate(this);
     
     running = StartInternalThread();
 }
 
 Channel::~Channel() {
     // Disconnect?
     // End thread?
     running = false;
     WaitForInternalThreadToExit();
//     fprintf("WE PROCESSED VIA DELEGATE!");
     printf("%s: Deallocating\n", __func__);
 }
 
 /** Returns true if the thread was successfully started, false if there was an error starting the thread */
 bool Channel::StartInternalThread()
 {
     _thread = std::thread(InternalThreadEntryFunc, this);
     //     return (pthread_create(&_thread, NULL, InternalThreadEntryFunc, this) == 0);
     return true;
 }
 
 /** Will not return until the internal thread has exited. */
 void Channel::WaitForInternalThreadToExit()
 {
     _thread.join();
 }
 
 void Channel::StopInternalThread() {
     running = false;
 }
     
 void Channel::InternalThreadEntry() {
     
     while(running) {
		 const uint32_t numberOfBytesToAskFor = 65536;// (1 << 16); // This is the value in DarkLighting
         uint32_t numberOfBytesReceived = 0;
         
         char buffer[numberOfBytesToAskFor];
         
         int ret = usbmuxd_recv(conn, (char*)&buffer, numberOfBytesToAskFor, &numberOfBytesReceived);
         
         if (ret == 0) {
             if (numberOfBytesReceived > 0) {
                 protocol.processData((char*)buffer, numberOfBytesReceived);
             }
         } else {
             printf("There was an error receiving data");
             running = false;
         }
     }
 }
     
 void Channel::simpleDataPacketProtocolDelegateDidProcessPacket(std::vector<char> packet) {
     printf("WE PROCESSED VIA DELEGATE!\n");
     
//     std::shared_ptr<ChannelDelegate> delegateReference = this->delegate.lock();
//     if (delegateReference) {
//         delegateReference->channelDidReceivePacket(packet);
//     }
     
     if (this->delegate) {
         this->delegate->channelDidReceivePacket(packet);
     }
     
 }
     
}