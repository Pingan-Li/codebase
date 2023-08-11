/**
 * @file tcp_client.cc
 * @author Li Pingan (lipingan.dev@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-08-07
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <cstdio>
#include <cstring>

#include <iostream>
#include <string>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include "base/command_line.h"

constexpr std::size_t kDefaultBufferSize = 4096u;
constexpr int kDefaultPort = 15672;

int main(int argc, char *argv[]) {
  base::CommandLine::Initialize(argc, argv);
  int socket_fd = 0;
  uint16_t port = 0;
  std::string ip_addres = "127.0.0.1";
  sockaddr_in server_addr;
  char buffer[kDefaultBufferSize];

  auto p = base::CommandLine::Get()->GetVal("port");
  if (!p) {
    port = kDefaultPort;
    std::cerr << "--port=[port] pased failed, using default port: "
              << kDefaultPort << std::endl;
  } else {
    port = std::atoi(p->c_str());
    std::cerr << "Using port: " << port << std::endl;
  }

  socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (-1 == socket_fd) {
    std::cerr << "create socket failed! " << std::strerror(errno) << std::endl;
    return errno;
  }

  auto ip = base::CommandLine::Get()->GetVal("ip");
  if (!ip) {
    std::cerr << "ip parsed failed, using default ip: " << ip_addres
              << std::endl;
  } else {
    ip_addres = ip.value();
    std::cerr << "using ip" << ip_addres << std::endl;
  }

  std::memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(port);

  int inet_pton_result =
      inet_pton(AF_INET, ip_addres.c_str(), &server_addr.sin_addr);
  if (-1 == inet_pton_result) {
    std::cerr << "inet_pton error! " << std::strerror(errno) << std::endl;
    return errno;
  }
  if (0 == inet_pton_result) {
    std::cerr << "ip address: " << ip_addres << " is invalid" << std::endl;
    return -1;
  }

  std::memset(buffer, 0, kDefaultBufferSize);
  if (-1 == connect(socket_fd, reinterpret_cast<sockaddr *>(&server_addr),
                    sizeof(server_addr))) {
    std::cerr << "connect failed! " << std::strerror(errno) << std::endl;
    return errno;
  }

  std::memset(buffer, 0, sizeof(buffer));
  std::string contents = "ping!";
  int result = 0;
  while (true) {
    result = write(socket_fd, contents.c_str(), contents.size());
    if (-1 == result) {
      std::cerr << "write error! " << std::strerror(errno) << std::endl;
      break;
    }
    result = read(socket_fd, buffer, kDefaultBufferSize - 1);
    if (-1 == result) {
      std::cerr << "read error! " << std::strerror(errno) << std::endl;
      break;
    }
    if (0 == result) {
      break;
    }
    buffer[result] = 0;
    std::cout << buffer << std::endl;
  }
  return 0;
}