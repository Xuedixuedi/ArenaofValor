#define _CRT_SECURE_NO_WARNINGS

#include <cstdlib>
#include <deque>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
//#include "unistd.h"
#include "message.h"
#include "cocos2d.h"
using boost::asio::ip::tcp;

typedef std::deque<chat_message> chat_message_queue;

//class Client;

//static Client*              this_client = nullptr;      ///指向client对象的指针


class chat_client 
{
public:
	static chat_client* Create(boost::asio::io_context& io_service, const tcp::resolver::results_type& endpoints)
	{
		chat_client* c = new chat_client(io_service, endpoints);
		return c;
	}


	//需要一个iocontext和endpoints进行初始化
	chat_client(boost::asio::io_context& io_service, const tcp::resolver::results_type& endpoints) : io_service_(io_service), socket_(io_service)
	{

		boost::asio::async_connect(socket_, endpoints, boost::bind(&chat_client::handle_connect, this, boost::asio::placeholders::error));
	}
	//接受一个chat_message对象，异步回调do_write;
	void write(const chat_message& msg)
	{
		io_service_.post(boost::bind(&chat_client::do_write, this, msg));
	}
	//关闭，异步回调do_close
	void close()
	{
		io_service_.post(boost::bind(&chat_client::do_close, this));
	}
public:
	//连接回调函数，进行异步调用handle_read_header
	void handle_connect(const boost::system::error_code& error)
	{
		if (!error)
		{
			boost::asio::async_read(socket_, boost::asio::buffer(read_msg_.data(), chat_message::header_length), boost::bind(&chat_client::handle_read_header, this, boost::asio::placeholders::error));
		}
	}
	//读取文件头，进行异步调用handle_read_body
	void handle_read_header(const boost::system::error_code& error)
	{
		if (!error && read_msg_.decode_header())
		{
			boost::asio::async_read(socket_, boost::asio::buffer(read_msg_.body(), read_msg_.body_length()), boost::bind(&chat_client::handle_read_body, this, boost::asio::placeholders::error));
		}
		else
		{
			do_close();
		}
	}

	void handle_read_body(const boost::system::error_code& error)
	{
		if (!error)
		{
			t_lock.lock();
			chat_message* newMsg = new chat_message();
			std::strcpy(newMsg->body(), read_msg_.body());
			newMsg->body_length(read_msg_.body_length());
			read_msg_list_.push_back(newMsg);
			t_lock.unlock();
			boost::asio::async_read(socket_, boost::asio::buffer(read_msg_.data(), chat_message::header_length), boost::bind(&chat_client::handle_read_header, this, boost::asio::placeholders::error));
		}
		else
		{
			do_close();
		}
	}

	void do_write(chat_message msg)
	{
		//检查私有数据成员
		bool write_in_progress = !write_msgs_.empty();
		write_msgs_.push_back(msg);
		
		//
		if (!write_in_progress)
		{
			boost::asio::async_write(socket_, boost::asio::buffer(write_msgs_.front().data(), write_msgs_.front().length()), boost::bind(&chat_client::handle_write, this, boost::asio::placeholders::error));
		}
	}
	//异步操作do_write完成后的回调函数
	void handle_write(const boost::system::error_code& error)
	{
		if (!error)
		{
			write_msgs_.pop_front();
			if (!write_msgs_.empty())
			{
				boost::asio::async_write(socket_, boost::asio::buffer(write_msgs_.front().data(), write_msgs_.front().length()), boost::bind(&chat_client::handle_write, this, boost::asio::placeholders::error));
			}
		}
		else
		{
			do_close();
		}
	}

	void do_close()
	{
		socket_.close();
	}

public:
	boost::mutex                t_lock;
	boost::asio::io_service&    io_service_;    ///asio的核心类, 用于创建socket
	tcp::socket                 socket_;        ///tcp类套接字
	std::deque<chat_message*>   read_msg_list_;
	chat_message                read_msg_;      ///每次循环所读取的数据对象
	chat_message_queue          write_msgs_;    ///等待被发送的数据对象
};













//
//
//
//
//
//
//
//class Client :public cocos2d::Node
//{
//public:
//	chat_client*                _clientInstance;        ///用于处理数据的接受和发送
//	std::mutex                  t_lock;                 ///线程锁，避免多个线程下对数据进行同时操作
//	std::deque<std::string>     _orderList;             ///读取到的正确指令
//
//	//工厂实例
//	static Client* create()
//	{
//		Client *sprite = new Client();
//		if (sprite)
//		{
//			sprite->autorelease();
//			sprite->runClient();
//
//			return sprite;
//		}
//		CC_SAFE_DELETE(sprite);
//		return nullptr;
//	}
//	void runClient()
//	{
//		std::thread t(&Client::client, this);
//
//		t.detach();
//	}
//	std::string acceptMessage()
//	{
//		t_lock.lock();
//
//		for (auto it : _orderList)
//		{
//			auto tmp = it;
//		}
//		std::string temp;
//
//		if (_orderList.size() != 0)
//		{
//			temp = _orderList.front();
//			_orderList.pop_front();
//		}
//		else
//		{
//			temp = "no";
//		}
//		t_lock.unlock();
//		return temp;
//	}
//
//	void sendMessage(const std::string & message)
//	{
//		chat_message msg;
//		std::string temp;
//
//		temp.append(message);
//		msg.body_length(temp.size());
//		memcpy(msg.body(), temp.c_str(), msg.body_length());
//		msg.encode_header();
//		_clientInstance->write(msg);
//	}
//
//	int client()
//	{
//		try
//		{
//			//初始化
//			boost::asio::io_context io_context;
//			tcp::resolver resolver(io_context);
//			std::string ip = "47.101.214.65";
//			std::string port = "32345";
//			tcp::resolver::results_type endpoints = resolver.resolve(ip, port);
//			//初始化client
//			chat_client c(io_context, endpoints);
//			_clientInstance = &c;
//			this_client = this;
//			//在线程t上面进行
//			boost::thread t(boost::bind(&boost::asio::io_context::run, &io_context));
//			//定义一个长度为包中长度max的字符数组
//			char line[chat_message::max_body_length + 1];
//			while (1)
//			{
//				;
//			}
//			c.close();
//			t.join();
//		}
//		catch (std::exception& e)
//		{
//			std::cerr << "Exception: " << e.what() << "\n";
//		}
//
//		return 0;
//	}
//
//private:
//
//};