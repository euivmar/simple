#pragma once

#include <string>
#include "SIMPLE.pb.h"
#include <zmq.hpp>
#include <zmq_utils.h>
#include <memory>
#include <vector>
#include "MSGreader.h"

namespace simple
{
template <typename T>
class Client
{
public:
  Client(std::string port, zmq::context_t& context);
  ~Client();
  std::unique_ptr<T> request();
  void readMsg(const SIMPLE::TRANSFORM& msg, SIMPLE::HEADER& header, double& px, double& py, double& pz, double& r11,
	  double& r12, double& r13, double& r21, double& r22, double& r23, double& r31, double& r32, double& r33);
  void readMsg(const SIMPLE::POSITION& msg, SIMPLE::HEADER& header, double& px, double& py, double& pz, double& e1,
	  double& e2, double& e3, double& e4);
  void readMsg(const SIMPLE::STATUS& msg, SIMPLE::HEADER& header, int& code, int& subcode, std::string& errorName,
	  std::string& errorMsg);
  void readMsg(const SIMPLE::CAPABILITY& msg, SIMPLE::HEADER& header, std::vector<std::string>& msgNames);
  void readMsg(const SIMPLE::GENERIC& msg, SIMPLE::HEADER& header, bool& data);
  void readMsg(const SIMPLE::GENERIC& msg, SIMPLE::HEADER& header, int& data);
  void readMsg(const SIMPLE::GENERIC& msg, SIMPLE::HEADER& header, float& data);
  void readMsg(const SIMPLE::GENERIC& msg, SIMPLE::HEADER& header, double& data);
  void readMsg(const SIMPLE::GENERIC& msg, SIMPLE::HEADER& header, std::string& data);
private:
  MSGreader msgReader;
  std::unique_ptr<zmq::socket_t> socket;
};

}  // namespace simple
template <typename T>
simple::Client<T>::Client(std::string port, zmq::context_t& context)
{
  /// Class constructor: opens the socket, of type ZMQ_REQ
  /// Binds socket to port

  socket = std::make_unique<zmq::socket_t>(context, ZMQ_REQ);

  try
  {
    socket->connect(port);
  }
  catch (zmq::error_t& e)
  {
    std::cout << "could not bind socket:" << e.what();
  }
}
template <typename T>
simple::Client<T>::~Client()
{
  /// Class destructor: Closes the socket
  socket->close();
}
template <typename T>
std::unique_ptr<T> simple::Client<T>::request()
{
  // send a request to the server, containing the type of message desired and wait for a reply

  std::unique_ptr<T> SIMPLEreply = std::make_unique<T>();

  std::string msgType = SIMPLEreply->GetTypeName();

  zmq::message_t ZMQmsg(msgType.size());

  memcpy(ZMQmsg.data(), msgType.c_str(), msgType.size());

  try
  {
    socket->send(ZMQmsg);
  }
  catch (zmq::error_t& e)
  {
    std::cout << "Could not send request: " << e.what();
  }

  // get reply
  zmq::message_t MSGreply;

  try
  {
    socket->recv(&MSGreply);
  }
  catch (zmq::error_t& e)
  {
    std::cout << "Could not receive message: " << e.what();
  }

  std::string strMessage(static_cast<char*>(MSGreply.data()),
                         MSGreply.size());  // copy data from ZMQ message into string

  SIMPLEreply->ParseFromString(strMessage);  // copy data from string to protobuf message

  return SIMPLEreply;
}