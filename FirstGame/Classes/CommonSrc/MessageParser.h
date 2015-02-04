/*
 * MessageParser.h
 *
 *  Created on: 2013年10月6日
 *      Author: root
 */

#ifndef MESSAGEPARSER_H_
#define MESSAGEPARSER_H_

#include <map>
#include "message.pb.h"

class MessageParser
{
public:
	MessageParser();
	~MessageParser();

	 ::google::protobuf::Message* FetchMessage(unsigned short protoid);

private:
	 void AddMsg(unsigned short protoid,::google::protobuf::Message* pMsg);

	 private:
	  std::map< unsigned short,::google::protobuf::Message* > m_messages;
};

#endif /* MESSAGEPARSER_H_ */
