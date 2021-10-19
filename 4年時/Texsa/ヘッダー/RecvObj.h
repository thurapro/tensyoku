/**************************************************************************//**
 * @file		RecvObj.h
 * @brief		
 * @author 		Watanabe Yositaka
 *****************************************************************************/
#ifndef RECVOBJ_H
#define RECVOBJ_H

#include <mutex>
#include "Socket.h"
#include "NetworkMessage.h"

class RecvObject{
public:

	void CreateRecv(MeekL::Socket *socket){

		m_socket = socket;

		socket->SetThreadCallBack([this](void* sender) ->DWORD{
			auto recvSocket = (MeekL::Socket*)sender;
			NetworkMessage msg;
			sockaddr_in fromAddr;
			for (; !m_destroy;){
				recvSocket->RecvFrom((char*)&msg, sizeof(msg), &fromAddr, sizeof(fromAddr));
				//m_funcLock.lock();
				if (!m_callback._Empty()){
					m_callback(msg, fromAddr, recvSocket);
				}
				//m_funcLock.unlock();
			}
			return 0;

		});

		socket->CreateThread();
	}
	void SetCallBack(std::function<void(NetworkMessage &msg, sockaddr_in &from, MeekL::Socket *socket)> func){
		//m_funcLock.lock();
		m_callback = func;
		//m_funcLock.unlock();
	}

	void Destroy(){
		m_destroy = true;
		m_socket->SetThreadCallBack(nullptr);
		m_callback = nullptr;
		m_socket->CloseThread();
	}

private:
	std::function<void(NetworkMessage &msg, sockaddr_in &from,MeekL::Socket *socket)> m_callback;
	MeekL::Socket *m_socket;
	bool m_destroy;
	std::mutex m_funcLock;
};
#endif //RECVOBJ_H