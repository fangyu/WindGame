#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <netinet/in.h>
#include <string.h>
#include "Msg.h"
#include "Encoder.h"
#include "MessageParser.h"

NetMsgHead::NetMsgHead()
{
	m_sMsgID = 0;
}

NetMsgHead::~NetMsgHead()
{
}

int NetMsgHead::EncodeMsg( unsigned char* pOutBuffer, unsigned short& nBufLength )
{
	if ( !pOutBuffer )
	{
		return -1;
	}

	unsigned char* pMsg = pOutBuffer;
	unsigned short nMsgLength = 0;
	nBufLength = 0;
	nMsgLength = (unsigned short)(EncodeShort( &pMsg, ( unsigned short )m_sMsgID ));
	nBufLength +=nMsgLength;

	return 0;
}

int	NetMsgHead::DecodeMsg( const unsigned char* pInBuffer, unsigned short nBufLength )
{
	if ( !pInBuffer || nBufLength <= 0 )
	{
		return -1;
	}

	unsigned short nMsgLength = nBufLength;
	unsigned char* pMsg = const_cast<unsigned char*>(pInBuffer);

	nMsgLength -= (unsigned short)(DecodeShort( &pMsg, (unsigned short *)&m_sMsgID ));

	if( nMsgLength < 0 )
	{
		return -1;
	}

	return nMsgLength;
}

NetMsgBody::NetMsgBody()
{
}

NetMsgBody::~NetMsgBody()
{
}

NetMsg::NetMsg( void* pMsg )
{
	m_pMsgBody = ( google::protobuf::Message* )pMsg;
}

NetMsg::~NetMsg()
{
	m_pMsgBody = 0;
}

void NetMsg::SetMsgID(unsigned short sMsgID)
{
	m_oHead.m_sMsgID = sMsgID;
}

unsigned short NetMsg::GetMsgID() const
{
	return m_oHead.m_sMsgID;
}

::google::protobuf::Message* NetMsg::GetMsgBody()
{
	return m_pMsgBody;
}

void NetMsg::SetMsgBody(::google::protobuf::Message* pMsgBody)
{
	m_pMsgBody = pMsgBody;
}

int NetMsg::EncodeMsg( unsigned char* pOutBuffer, unsigned short& nBufLength )
{
	if ( !pOutBuffer )
	{
		return NetMsgEncodeMsgError - 1;
	}

	unsigned char* pMsgBuffer = pOutBuffer;
	unsigned short nMsgLength;
	nBufLength = 0;

	if ( m_oHead.EncodeMsg( pMsgBuffer, nMsgLength ) )
	{
		return NetMsgEncodeMsgError - 2;
	}

	nBufLength += nMsgLength;
	pMsgBuffer += nMsgLength;

	if( !m_pMsgBody )
	{
		return 0;
	}

	int size = m_pMsgBody->ByteSize();
	if(! m_pMsgBody->SerializeToArray((void*)pMsgBuffer, size ) )
	{
		return NetMsgEncodeMsgError - 3;
	}

	nBufLength += size;
	pMsgBuffer += size;

	return 0;
}

int NetMsg::DecodeMsg( const unsigned char* pInBuffer, unsigned short nBufLength,MessageParser* pMessageParser )
{
	int nBufLeft;

	if ( !pInBuffer )
	{
		return NetMsgDecodeMsgError - 1;
	}

	if ( !pMessageParser )
	{
		return NetMsgDecodeMsgError - 2;
	}

	const unsigned char* pMsgBuffer = pInBuffer;
	if ( (nBufLeft = m_oHead.DecodeMsg( pMsgBuffer, nBufLength )) == -1 )
	{
		return NetMsgDecodeMsgError - 3;
	}

	if ( nBufLeft == 0 )
    {
           return 0;
    }
	
	pMsgBuffer += (nBufLength - nBufLeft);

	//::google::protobuf::Message* pMsgBody = CreateMsgBody( ( void* )m_pMsgBody, m_oHead.m_sMsgID );

	m_pMsgBody = pMessageParser->FetchMessage(m_oHead.m_sMsgID);
	if ( !m_pMsgBody )
	{
		return NetMsgDecodeMsgError - 4;
	}

	if (! m_pMsgBody->ParseFromArray( (const void*)pMsgBuffer, nBufLeft ) )
	{
		return NetMsgDecodeMsgError - 5;
	}

	return 0;
}

CNetHead::CNetHead()
{
	m_iClientIP = 0;
	m_iClientIndex = 0;
	m_tStamp = 0;
	m_iRetCode = 0;
}

CNetHead::~CNetHead()
{

}

int CNetHead::Encode(unsigned char *pcOutBuffer, unsigned short &sOutLength )
{
	unsigned char *pcTemp;
	unsigned short sTempLength;

	if( !pcOutBuffer )
	{
		return -1;
	}

	pcTemp = pcOutBuffer;
	sOutLength = 0;
	sTempLength = EncodeInt( &pcTemp, m_iClientIP );
	sOutLength += sTempLength;

	sTempLength = EncodeInt( &pcTemp, m_iClientIndex );
	sOutLength += sTempLength;

	sTempLength = EncodeInt( &pcTemp, (unsigned int)m_tStamp );
	sOutLength += sTempLength;

	sTempLength = EncodeInt( &pcTemp, m_iRetCode );
	sOutLength += sTempLength;

	return 0;
}

int CNetHead::Decode(const unsigned char *pcInBuffer, const unsigned short sInLength )
{
	unsigned char *pcTemp;
	unsigned short sLeftLength;
	unsigned short sTempLength;

	if( !pcInBuffer || sInLength <= 0 )
	{
		return -1;
	}

	pcTemp = (unsigned char*)pcInBuffer;
	sLeftLength = sInLength;

	sTempLength = DecodeInt( &pcTemp, &m_iClientIP );
	sLeftLength -= sTempLength;

	sTempLength = DecodeInt( &pcTemp, (unsigned int *)&m_iClientIndex );
	sLeftLength -= sTempLength;

	sTempLength = DecodeInt( &pcTemp, (unsigned int *)&m_tStamp );
	sLeftLength -= sTempLength;

	sTempLength = DecodeInt( &pcTemp, (unsigned int *)&m_iRetCode );
	sLeftLength -= sTempLength;

	if( sLeftLength < 0 )
	{
		return -1;
	}

	return sLeftLength;
}



ClientNetHead::ClientNetHead()
{
	memset(m_SessionKey,0,sizeof(m_SessionKey));
	memset(m_AccID,0,sizeof(m_AccID));
}

ClientNetHead::~ClientNetHead()
{

}

void ClientNetHead::SetSessionKey(char* szSessionKey)
{
	if(!szSessionKey)
		return;

	strncpy(m_SessionKey,szSessionKey,SESSIONKEYSIZE);
	m_SessionKey[SESSIONKEYSIZE] = '\0';
}

void ClientNetHead::SetAccID(char* szAccountID)
{
	if(!szAccountID)
		return;

	strncpy(m_AccID, szAccountID, ACCOUNTIDSIZE);
	m_AccID[ACCOUNTIDSIZE] = '\0';
}

int ClientNetHead::Encode(unsigned char *pcOutBuffer, unsigned short &sOutLength )
{
	unsigned char *pcTemp;
	unsigned short sTempLength;

	if( !pcOutBuffer )
	{
		return -1;
	}

	pcTemp = pcOutBuffer;
	sOutLength = 0;
	sTempLength = EncodeString( &pcTemp, m_SessionKey, SESSIONKEYSIZE);
	sOutLength += sTempLength;

	sTempLength = EncodeString( &pcTemp, m_AccID, ACCOUNTIDSIZE);
	sOutLength += sTempLength;

	return 0;
}

int ClientNetHead::Decode(const unsigned char *pcInBuffer, const unsigned short sInLength )
{
	unsigned char *pcTemp;
	unsigned short sLeftLength;
	unsigned short sTempLength;

	if( !pcInBuffer || sInLength <= 0 )
	{
		return -1;
	}

	pcTemp = (unsigned char*)pcInBuffer;
	sLeftLength = sInLength;

	sTempLength = DecodeString( &pcTemp, m_SessionKey,SESSIONKEYSIZE, sInLength);
	sLeftLength -= sTempLength;

	if( sLeftLength < 0 )
	{
		return -1;
	}

	sTempLength = DecodeString( &pcTemp, m_AccID, ACCOUNTIDSIZE, sLeftLength);
	sLeftLength -= sTempLength;

	if( sLeftLength < 0 )
	{
		return -1;
	}

	return sLeftLength;
}


ClientNetMsg::ClientNetMsg( void* pMsg ) : NetMsg(pMsg)
{

}

ClientNetMsg::~ClientNetMsg()
{

}

void ClientNetMsg::SetSessionKey(char* szSessionKey)
{
	m_ClientHead.SetSessionKey(szSessionKey);
}

void ClientNetMsg::SetAccID(char* szAccID)
{
	m_ClientHead.SetAccID(szAccID);
}

int ClientNetMsg::EncodeMsg( unsigned char* pOutBuffer, unsigned short& nBufLength )
{
	if ( !pOutBuffer )
	{
		return NetMsgEncodeMsgError - 1;
	}

	unsigned char* pMsgBuffer = pOutBuffer;
	unsigned short nMsgLength;
	nBufLength = 0;

	if(m_ClientHead.Encode(pMsgBuffer,nMsgLength))
	{
		return NetMsgEncodeMsgError - 6;
	}

	nBufLength += nMsgLength;
	pMsgBuffer += nMsgLength;

	if ( m_oHead.EncodeMsg( pMsgBuffer, nMsgLength ) )
	{
		return NetMsgEncodeMsgError - 2;
	}

	nBufLength += nMsgLength;
	pMsgBuffer += nMsgLength;

	if( !m_pMsgBody )
	{
		return 0;
	}

	int size = m_pMsgBody->ByteSize();
    
	if(! m_pMsgBody->SerializeToArray((void*)pMsgBuffer, size ) )
	{
		return NetMsgEncodeMsgError - 3;
	}

	nBufLength += size;
	pMsgBuffer += size;

	return 0;
}

int ClientNetMsg::DecodeMsg( const unsigned char* pInBuffer, unsigned short nBufLength, MessageParser* pMessageParser)
{
	unsigned short nBufLeft;

	if ( !pInBuffer )
	{
		return NetMsgDecodeMsgError - 1;
	}

	if ( !pMessageParser )
	{
		return NetMsgDecodeMsgError - 2;
	}

	const unsigned char* pMsgBuffer = pInBuffer;

	if( (nBufLeft = m_ClientHead.Decode(pMsgBuffer,nBufLength)) == -1 )
	{
		return NetMsgDecodeMsgError - 6;
	}

	pMsgBuffer += (nBufLength - nBufLeft);
	nBufLength = nBufLeft;

	if ( (nBufLeft = m_oHead.DecodeMsg( pMsgBuffer, nBufLength )) == -1 )
	{
		return NetMsgDecodeMsgError - 3;
	}

	if ( nBufLeft == 0 )
    {
           return 0;
    }

	pMsgBuffer += (nBufLength - nBufLeft);
	nBufLength = nBufLeft;

	//::google::protobuf::Message* pMsgBody = CreateMsgBody( ( void* )m_pMsgBody, m_oHead.m_sMsgID );

	m_pMsgBody = pMessageParser->FetchMessage(m_oHead.m_sMsgID);
	if ( !m_pMsgBody )
	{
		return NetMsgDecodeMsgError - 4;
	}

	if (! m_pMsgBody->ParseFromArray( (const void*)pMsgBuffer, nBufLength ) )
	{
		return NetMsgDecodeMsgError - 5;
	}

	return 0;
}




DBNetHead::DBNetHead()
{
	memset(m_AccID,0,sizeof(m_AccID));
}

DBNetHead::~DBNetHead()
{

}

void DBNetHead::SetAccID(const char* szAccID)
{
	if(!szAccID)
		return;

	strncpy(m_AccID,szAccID,SESSIONKEYSIZE);
	m_AccID[SESSIONKEYSIZE] = '\0';
}

int DBNetHead::Encode(unsigned char *pcOutBuffer, unsigned short &sOutLength )
{
	unsigned char *pcTemp;
	unsigned short sTempLength;

	if( !pcOutBuffer )
	{
		return -1;
	}

	pcTemp = pcOutBuffer;
	sOutLength = 0;
	sTempLength = EncodeString( &pcTemp, m_AccID, SESSIONKEYSIZE);
	sOutLength += sTempLength;

	return 0;
}

int DBNetHead::Decode(const unsigned char *pcInBuffer, const unsigned short sInLength )
{
	unsigned char *pcTemp;
	unsigned short sLeftLength;
	unsigned short sTempLength;

	if( !pcInBuffer || sInLength <= 0 )
	{
		return -1;
	}

	pcTemp = (unsigned char*)pcInBuffer;
	sLeftLength = sInLength;


	sTempLength = DecodeString( &pcTemp, m_AccID,SESSIONKEYSIZE, sInLength);
	sLeftLength -= sTempLength;

	if( sLeftLength < 0 )
	{
		return -1;
	}

	return sLeftLength;
}


DBNetMsg::DBNetMsg( void* pMsg ) : NetMsg(pMsg)
{

}

DBNetMsg::~DBNetMsg()
{

}

int DBNetMsg::EncodeMsg( unsigned char* pOutBuffer, unsigned short& nBufLength )
{
	if ( !pOutBuffer )
	{
		return NetMsgEncodeMsgError - 1;
	}

	unsigned char* pMsgBuffer = pOutBuffer;
	unsigned short nMsgLength;
	nBufLength = 0;

	if(m_DBHead.Encode(pMsgBuffer,nMsgLength))
	{
		return NetMsgEncodeMsgError - 6;
	}

	nBufLength += nMsgLength;
	pMsgBuffer += nMsgLength;

	if ( m_oHead.EncodeMsg( pMsgBuffer, nMsgLength ) )
	{
		return NetMsgEncodeMsgError - 2;
	}

	nBufLength += nMsgLength;
	pMsgBuffer += nMsgLength;

	if( !m_pMsgBody )
	{
		return 0;
	}

	int size = m_pMsgBody->ByteSize();
	if(! m_pMsgBody->SerializeToArray((void*)pMsgBuffer, size ) )
	{
		return NetMsgEncodeMsgError - 3;
	}

	nBufLength += size;
	pMsgBuffer += size;

	return 0;
}

int DBNetMsg::DecodeMsg( const unsigned char* pInBuffer, unsigned short nBufLength, MessageParser* pMessageParser)
{
	unsigned short nBufLeft;

	if ( !pInBuffer )
	{
		return NetMsgDecodeMsgError - 1;
	}

	if ( !pMessageParser )
	{
		return NetMsgDecodeMsgError - 2;
	}

	const unsigned char* pMsgBuffer = pInBuffer;

	if( (nBufLeft = m_DBHead.Decode(pMsgBuffer,nBufLength)) == -1 )
	{
		return NetMsgDecodeMsgError - 6;
	}

	pMsgBuffer += (nBufLength - nBufLeft);
	nBufLength = nBufLeft;

	if ( (nBufLeft = m_oHead.DecodeMsg( pMsgBuffer, nBufLength )) == -1 )
	{
		return NetMsgDecodeMsgError - 3;
	}

	if ( nBufLeft == 0 )
    {
           return 0;
    }

	pMsgBuffer += (nBufLength - nBufLeft);
	nBufLength = nBufLeft;

	//::google::protobuf::Message* pMsgBody = CreateMsgBody( ( void* )m_pMsgBody, m_oHead.m_sMsgID );

	m_pMsgBody = pMessageParser->FetchMessage(m_oHead.m_sMsgID);

	if ( !m_pMsgBody )
	{
		return NetMsgDecodeMsgError - 4;
	}

	if (! m_pMsgBody->ParseFromArray( (const void*)pMsgBuffer, nBufLength ) )
	{
		return NetMsgDecodeMsgError - 5;
	}

	return 0;
}

//PbMsgBody::PbMsgBody()
//{
//	m_message = NULL;
//	m_ID = -1;
//}
//
//PbMsgBody::~PbMsgBody()
//{
//}
//
//void PbMsgBody::SetMessage(unsigned short id, google::protobuf::Message* pMsg)
//{
//	m_message = pMsg;
//	m_ID = id;
//}
//
//int PbMsgBody::EncodeMsg( unsigned char* pOutBuffer, unsigned short& nBufLength )
//{
//	if(!m_message ){
//		return -1;
//	}
//
//	int size = m_message->ByteSize();
//
//	bool ret = m_message->SerializeToArray(pOutBuffer, size);
//	if(ret)
//	{
//		nBufLength = size;
//		return 0;
//	}
//
//	return -1;
//}
//
//int PbMsgBody::DecodeMsg( const unsigned char* pInBuffer, unsigned short nBufLength )
//{
//	if(!m_message || !pInBuffer){
//		return -1;
//	}
//
//	bool ret = m_message->ParseFromArray(pInBuffer, nBufLength);
//
//	if(ret)
//	{
//		return 0;
//	}
//
//	return -1;
//}
//
//int PbMsgBody::GetType()
//{
//	return m_ID;
//}
