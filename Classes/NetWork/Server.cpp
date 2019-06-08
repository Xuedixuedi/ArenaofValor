#define _CRT_SECURE_NO_WARNINGS

#include <algorithm>
#include <cstdlib>
#include <deque>
#include <iostream>
#include <list>
#include <set>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include "Message.h"

using boost::asio::ip::tcp;

//----------------------------------------------------------------------

typedef std::deque<chat_message> chat_message_queue;

//----------------------------------------------------------------------
//抽象类
class chat_participant
{
public:
	virtual ~chat_participant() {}
	virtual void deliver(const chat_message& msg) = 0;
};

typedef boost::shared_ptr<chat_participant> chat_participant_ptr;

//----------------------------------------------------------------------

//聊天室
//私有存储了participant的容器，接受message的双向队列
class chat_room
{
public:
	//加入一个participant，并且回调这个participant的deliver函数，循环容器长度次数
	void join(chat_participant_ptr participant)
	{
		participants_.insert(participant);
		std::for_each(recent_msgs_.begin(), recent_msgs_.end(),boost::bind(&chat_participant::deliver, participant, _1));
	}
	//一个participant离开
	void leave(chat_participant_ptr participant)
	{
		participants_.erase(participant);
	}
	//最近消息容器接收一个message，并将超出存储范围的消息弹出，遍历所有参与者的deliver，传入消息
	void deliver(const chat_message& msg)
	{
		recent_msgs_.push_back(msg);
		while (recent_msgs_.size() > max_recent_msgs)
			recent_msgs_.pop_front();

		std::for_each(participants_.begin(), participants_.end(),boost::bind(&chat_participant::deliver, _1, boost::ref(msg)));
	}

private:
	std::set<chat_participant_ptr> participants_;
	enum { max_recent_msgs = 0 };
	chat_message_queue recent_msgs_;
};

//----------------------------------------------------------------------

class chat_session: public chat_participant,public boost::enable_shared_from_this<chat_session>
{
public:
	chat_session(boost::asio::io_context& io_context, chat_room& room) : socket_(io_context), room_(room)
	{
	}
	//获取私有socket的接口
	tcp::socket& socket()
	{
		return socket_;
	}
	//
	void start() 
	{
		room_.join(shared_from_this());
		boost::asio::async_read(socket_,boost::asio::buffer(read_msg_.data(), chat_message::header_length),boost::bind(&chat_session::handle_read_header, shared_from_this(),boost::asio::placeholders::error));
	}

	void deliver(const chat_message& msg)
	{
		bool write_in_progress = !write_msgs_.empty();
		write_msgs_.push_back(msg);
		if (!write_in_progress)
		{
			boost::asio::async_write(socket_,
				boost::asio::buffer(write_msgs_.front().data(),
					write_msgs_.front().length()),
				boost::bind(&chat_session::handle_write, shared_from_this(),
					boost::asio::placeholders::error));
		}
	}

	void handle_read_header(const boost::system::error_code& error)
	{
		if (!error && read_msg_.decode_header())
		{
			boost::asio::async_read(socket_,
				boost::asio::buffer(read_msg_.body(), read_msg_.body_length()),
				boost::bind(&chat_session::handle_read_body, shared_from_this(),
					boost::asio::placeholders::error));
		}
		else
		{
			room_.leave(shared_from_this());
		}
	}

	void handle_read_body(const boost::system::error_code& error)
	{
		if (!error)
		{
			room_.deliver(read_msg_);
			boost::asio::async_read(socket_,
				boost::asio::buffer(read_msg_.data(), chat_message::header_length),
				boost::bind(&chat_session::handle_read_header, shared_from_this(),
					boost::asio::placeholders::error));
		}
		else
		{
			room_.leave(shared_from_this());
		}
	}

	void handle_write(const boost::system::error_code& error)
	{
		if (!error)
		{
			write_msgs_.pop_front();
			if (!write_msgs_.empty())
			{
				boost::asio::async_write(socket_,
					boost::asio::buffer(write_msgs_.front().data(),
						write_msgs_.front().length()),
					boost::bind(&chat_session::handle_write, shared_from_this(),
						boost::asio::placeholders::error));
			}
		}
		else
		{
			room_.leave(shared_from_this());
		}
	}

private:
	tcp::socket socket_;
	chat_room& room_;
	chat_message read_msg_;
	chat_message_queue write_msgs_;
};

typedef boost::shared_ptr<chat_session> chat_session_ptr;

//----------------------------------------------------------------------

class chat_server
{
public:
	//接受一个io_context和endpoint，初始化数据成员io_context和acceptor
	chat_server(boost::asio::io_context& io_context,const tcp::endpoint& endpoint): io_context_(io_context),acceptor_(io_context, endpoint)
	{
		//启动检测
		start_accept();
	}

	void start_accept()
	{
		//创建一个会话
		chat_session_ptr new_session(new chat_session(io_context_, room_));
		//先建立一个socket的新连接,再异步调用handle_accept
		acceptor_.async_accept(new_session->socket(), boost::bind(&chat_server::handle_accept, this, new_session, boost::asio::placeholders::error));
	}
	//accept回调函数，没有错误情况下启动会话，然后循环调用start_accept
	void handle_accept(chat_session_ptr session,const boost::system::error_code& error)
	{
		if (!error)
		{
			session->start();
		}
		start_accept();
	}
private:
	boost::asio::io_context& io_context_;
	tcp::acceptor acceptor_;
	chat_room room_;
};

typedef boost::shared_ptr<chat_server> chat_server_ptr;
typedef std::list<chat_server_ptr> chat_server_list;

//----------------------------------------------------------------------

int main(int argc, char* argv[])
{
	try
	{
		if (argc < 2)
		{
			std::cerr << "Usage: chat_server <port> [<port> ...]\n";
			return 1;
		}

		boost::asio::io_context io_context;

		chat_server_list servers;
		for (int i = 1; i < argc; ++i)
		{
			using namespace std; // For atoi.
			tcp::endpoint endpoint(tcp::v4(), atoi(argv[i]));
			chat_server_ptr server(new chat_server(io_context, endpoint));
			servers.push_back(server);
		}
		io_context.run();
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}