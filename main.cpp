#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/event.h>
#include <cerrno>
#include <cstring>
#include <vector>

typedef struct sockaddr_in	SOCKADDR_IN; 		// sockaddr_in 구조체 타입명 설정

// void	client(int connectSockfd, SOCKADDR_IN clientAddr, std::vector<SOCKADDR_IN> clientList)
// {
// 	(void) clientList;
// 	std::cout << "Client connected IP address = " \
// 		<< inet_ntoa(clientAddr.sin_addr) << ":" << ntohs(clientAddr.sin_port) << std::endl;
// }

int	main(int ac, char **av)
{
	int							serverSockfd;    	// Server Socket fd
	int							connectSockfd;    	// Connect Socket fd
	std::string					errMsg = ""; 		// 에러메시지
	SOCKADDR_IN					serverAddr;  		// 서버의 소켓 주소 저장
	SOCKADDR_IN					clientAddr;  		// 클라이언트의 소켓 주소 저장
	// std::vector<SOCKADDR_IN>	*clientList;		// 클라이언트 소켓 주소들
	int							portNum;   			// 포트번호 저장
	socklen_t 					clientSize;			// 클라이언트 소켓 크기 저장
	socklen_t 					compareSize;
	ssize_t 					valread;
	char						buffer[1024];

	try
	{
		if (ac >= 2)
		{
			try
			{
				//1. socket 생성
				if ((serverSockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0) //TODO - 왜 AF_INET가 아님?
				{
					errMsg = "Socket failed";
					throw std::runtime_error(errMsg);
				}
				
				//2. 서버의 소켓 주소 설정
				std::memset(&serverAddr, 0, sizeof(serverAddr));
				serverAddr.sin_family = AF_INET;
				serverAddr.sin_addr.s_addr = htonl(INADDR_ANY); //TODO - s_addr?, INADDR_ANY는 netpractice의 default와 같은 의미?
				portNum = std::atoi(av[1]);
				serverAddr.sin_port = portNum;

				//3. Bind
				if (bind(serverSockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) //TODO - sockaddr. sockaddr_in 차이 정리
				{
					throw std::runtime_error(strerror(errno));
				}

				//4. Listen
				if (listen(serverSockfd, SOMAXCONN) < 0)
				{
					throw std::runtime_error(strerror(errno));
				}

				//5. 클라이언트 소켓 요청 받기(Accept)
				while (1)
				{
					clientSize = sizeof(SOCKADDR_IN);
					compareSize = sizeof(SOCKADDR_IN);
					std::cout << "clientSize: " << clientSize << std::endl;
					std::cout << "compareSize: " << compareSize << std::endl;
					if ((connectSockfd = accept(serverSockfd, (struct sockaddr*)&clientAddr, &clientSize)) < 0) //accept()가 이미 nonblocking이고 요청이 없으면 반복문 종료
					{
						std::cout << "strerror(errno)" << std::endl;
						// throw std::runtime_error(strerror(errno));
					}
					//스레드 관리 kqueue에서 처리하기
					//read, send()
					if ((valread = recv(connectSockfd, buffer, sizeof(buffer), 0)) < 0)
					{
						std::cout << buffer << std::endl;
					}
					else
						std::cout << "valread : " << valread << std::endl;
						// throw std::runtime_error(strerror(errno));
				}
			}
			catch(const std::exception& e)
			{
				std::cerr << e.what() << std::endl;
			}
		}
		else
		{
			errMsg = "Usage: " + std::string(av[0]) + "port";
			throw std::runtime_error(errMsg);
		}
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return (0);
}