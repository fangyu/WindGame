#ifndef _MSG_HPP_
#define _MSG_HPP_

#include <google/protobuf/message.h>

#define SESSIONKEYSIZE		128
#define ACCOUNTIDSIZE 		128


#define MAXPACKAGESIZE		((short)0x7000)

const int NetMsgEncodeMsgError = -300;
const int NetMsgDecodeMsgError = -400;

class MessageParser;

class NetMsgHead
{
public:
	NetMsgHead();
	~NetMsgHead();

	int	EncodeMsg( unsigned char* pOutBuffer, unsigned short& nBufLength );
	int	DecodeMsg( const unsigned char* pInBuffer, unsigned short nBufLength );

	unsigned short		m_sMsgID;
};

class NetMsgBody
{
public:
	NetMsgBody();

	virtual ~NetMsgBody();
	virtual int EncodeMsg( unsigned char* pOutBuffer, unsigned short& nBufLength ) = 0;
	virtual int DecodeMsg( const unsigned char* pInBuffer, unsigned short nBufLength ) = 0;
	virtual int GetType() = 0;
};

class NetMsg
{
public:
	NetMsg( void* pMsg );
	virtual ~NetMsg();

	void SetMsgID(unsigned short sMsgID);
	unsigned short GetMsgID() const ;
	::google::protobuf::Message* GetMsgBody();
	void SetMsgBody(::google::protobuf::Message* pMsgBody);

	virtual int EncodeMsg( unsigned char* pOutBuffer, unsigned short& nBufLength );
	virtual int DecodeMsg( const unsigned char* pInBuffer, unsigned short nBufLength,MessageParser* pMessageParser );
	//virtual ::google::protobuf::Message* CreateMsgBody( void* pBuf, unsigned short sMsgID );

	NetMsgHead	m_oHead;
	::google::protobuf::Message*	m_pMsgBody;
};

class CNetHead
{
public:
	CNetHead();
	~CNetHead();

	int  Encode( unsigned char *pcOutBuffer, unsigned short &sOutLength );
	int  Decode( const unsigned char *pcInBuffer, const unsigned short sInLength );

	unsigned int 	m_iClientIP;
	int 		 	m_iClientIndex;
	time_t 		 	m_tStamp;
	int			 	m_iRetCode;
};

class ClientNetHead
{
public:
	ClientNetHead();
	~ClientNetHead();

	void 	SetSessionKey(char* szSessionKey);
	char*	GetSessionKey() { return m_SessionKey; }

	void 	SetAccID(char* szAccountID);
	char*   GetAccID() { return m_AccID; }

	int  	Encode( unsigned char *pcOutBuffer, unsigned short &sOutLength );
	int  	Decode( const unsigned char *pcInBuffer, const unsigned short sInLength );

	char 	m_SessionKey[SESSIONKEYSIZE+1];
	char    m_AccID[ACCOUNTIDSIZE + 1];
};

class ClientNetMsg : public NetMsg
{
public:
	ClientNetMsg(void* pMsg);
	virtual ~ClientNetMsg();

	void 	SetSessionKey(char* szSessionKey);

	char*	GetSessionKey() { return m_ClientHead.GetSessionKey(); }

	void    SetAccID(char* szAccID);

	char*   GetAccID() { return m_ClientHead.GetAccID();}

	virtual int EncodeMsg( unsigned char* pOutBuffer, unsigned short& nBufLength );
	virtual int DecodeMsg( const unsigned char* pInBuffer, unsigned short nBufLength,MessageParser* pMessageParser );

	ClientNetHead	m_ClientHead;
};

class DBNetHead
{
public:
	DBNetHead();
	~DBNetHead();

	void 			SetAccID(const char* szAccID);
	char*			GetAccID() { return m_AccID; }

	int  	Encode( unsigned char *pcOutBuffer, unsigned short &sOutLength );
	int  	Decode( const unsigned char *pcInBuffer, const unsigned short sInLength );

	char 	m_AccID[SESSIONKEYSIZE+1];
};

class DBNetMsg : public NetMsg
{
public:
	DBNetMsg(void* pMsg);
	virtual ~DBNetMsg();

	void 			SetAccID(const char* szAccID) { m_DBHead.SetAccID(szAccID); }
	char*			GetAccID() { return m_DBHead.GetAccID(); }

	virtual int EncodeMsg( unsigned char* pOutBuffer, unsigned short& nBufLength );
	virtual int DecodeMsg( const unsigned char* pInBuffer, unsigned short nBufLength,MessageParser* pMessageParser );

	DBNetHead	m_DBHead;
};

//class PbMsgBody : public NetMsgBody
//{
//public:
//	PbMsgBody();
//	~PbMsgBody();
//	void 	    SetMessage(unsigned short id, google::protobuf::Message* pMsg);
//	virtual int EncodeMsg( unsigned char* pOutBuffer, unsigned short& nBufLength );
//	virtual int DecodeMsg( const unsigned char* pInBuffer, unsigned short nBufLength );
//	virtual int GetType();
//private:
//
//	::google::protobuf::Message* m_message;
//	unsigned short 			     m_ID;
//};

#endif
