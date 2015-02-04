#include <stdio.h>
#include <stdarg.h>
#ifdef WIN32
#include <WinSock2.h>
#else
#include <netinet/in.h>
#endif
#include <string.h>
#include "Encoder.h"

#define ntohll(x) (((unsigned long long)ntohl(x)) << 32) + ntohl(x >> 32)
#define htonll(x) (((unsigned long long)htonl(x)) << 32) + htonl(x >> 32)

int EncodeChar( unsigned char** pstrEncode, unsigned char ucSrc )
{
	if( pstrEncode == 0 || *pstrEncode == 0 )
	{
		return 0;
	}

	**pstrEncode = ( unsigned char )ucSrc;
	(*pstrEncode)++;

	return ( int )sizeof( unsigned char );
}

int DecodeChar( unsigned char** pstrDecode, unsigned char *pucDest )
{
	if( pstrDecode == 0 || *pstrDecode == 0 || pucDest == 0 )
	{
		return 0;
	}

	*pucDest = **pstrDecode;
	(*pstrDecode)++;

	return ( int )sizeof( unsigned char );
}

int EncodeShort( unsigned char** pstrEncode, unsigned short usSrc )
{
	unsigned short usTemp;

	if( pstrEncode == 0 || *pstrEncode == 0 )
	{
		return 0;
	}

	usTemp = htons( usSrc );

	memcpy( ( void* )( *pstrEncode ), ( const void* )&usTemp, sizeof( unsigned short ) );
	*pstrEncode += sizeof( unsigned short );

	return ( int )sizeof( unsigned short );
}

int DecodeShort( unsigned char** pstrDecode, unsigned short *pusDest )
{
	unsigned short usTemp;

	if( pstrDecode == 0 || *pstrDecode == 0 || pusDest == 0 )
	{
		return 0;
	}

	memcpy( ( void* )&usTemp, ( const void* )( *pstrDecode ), sizeof( unsigned short ) );
	*pstrDecode += sizeof(unsigned short);

	*pusDest = ntohs( usTemp );

	return ( int )sizeof( unsigned short );
}

int EncodeLong( unsigned char** pstrEncode, unsigned long ulSrc )
{
	unsigned long ulTemp;

	if( pstrEncode == 0 || *pstrEncode == 0 )
	{
		return 0;
	}

	ulTemp = htonl( ulSrc );

	memcpy( ( void* )( *pstrEncode ), ( const void* )&ulTemp, sizeof( unsigned long ) );
	*pstrEncode += sizeof( unsigned long );

	return ( int )sizeof( unsigned long );
}

int DecodeLong( unsigned char** pstrDecode, unsigned long *pulDest )
{
	unsigned long ulTemp;

	if( pstrDecode == NULL || *pstrDecode == NULL || pulDest == NULL)
	{
		return 0;
	}

	memcpy( ( void* )&ulTemp, ( const void* )( *pstrDecode ), sizeof( unsigned long ) );
	*pstrDecode += sizeof( unsigned long );

	*pulDest = ntohl( ulTemp );

	return ( int )sizeof( unsigned long );
}

int EncodeLongLong( unsigned char** pstrEncode, unsigned long long ulSrc )
{
	unsigned long long ulTemp;

	if( pstrEncode == 0 || *pstrEncode == 0 )
	{
		return 0;
	}

	ulTemp = htonll( ulSrc );

	memcpy( ( void* )( *pstrEncode ), ( const void* )&ulTemp, sizeof( unsigned long long ) );
	*pstrEncode += sizeof( unsigned long long );

	return ( int )sizeof( unsigned long long );
}

int DecodeLongLong( unsigned char** pstrDecode, unsigned long long *pulDest )
{
	unsigned long long ulTemp;

	if( pstrDecode == NULL || *pstrDecode == NULL || pulDest == NULL)
	{
		return 0;
	}

	memcpy( ( void* )&ulTemp, ( const void* )( *pstrDecode ), sizeof( unsigned long long ) );
	*pstrDecode += sizeof( unsigned long long );

	*pulDest = ntohll( ulTemp );

	return ( int )sizeof( unsigned long long );
}

int EncodeInt( unsigned char** pstrEncode, unsigned int uiSrc )
{
	unsigned int uiTemp;

	if( pstrEncode == 0 || *pstrEncode == 0 )
	{
		return 0;
	}

	uiTemp = htonl( uiSrc );

	memcpy( ( void* )( *pstrEncode ), ( const void* )&uiTemp, sizeof( unsigned int ) );
	*pstrEncode += sizeof( unsigned int );

	return ( int )sizeof( unsigned int );
}

int DecodeInt( unsigned char** pstrDecode, unsigned int *puiDest )
{
	unsigned int uiTemp;

	if( pstrDecode == 0 || *pstrDecode == 0 || puiDest == 0 )
	{
		return 0;
	}

	memcpy( ( void* )&uiTemp, ( const void* )( *pstrDecode ), sizeof( unsigned int ) );
	*pstrDecode += sizeof( unsigned int );

	*puiDest = ntohl( uiTemp );

	return ( int )sizeof( unsigned int );
}

int EncodeString( unsigned char** pstrEncode, const char* strSrc, short sMaxStrLength)
{
	unsigned short usTemp;
	unsigned short usTempLength;

	if( pstrEncode == 0 || *pstrEncode == 0 || strSrc == 0 || sMaxStrLength <= 0 )
	{
		return 0;
	}

	usTempLength = ( unsigned short )strlen( strSrc );
	if( usTempLength > sMaxStrLength )
	{
		usTempLength = sMaxStrLength;
	}

	usTemp = htons( usTempLength );

	memcpy( ( void* )( *pstrEncode ), ( const void* )&usTemp, sizeof( unsigned short ) );
	*pstrEncode += sizeof( unsigned short );

	memcpy( ( void* )( *pstrEncode ), ( const void* )strSrc, usTempLength );
	*pstrEncode += usTempLength;

	return ( int )( usTempLength + sizeof( unsigned short ) );
}

int DecodeString( unsigned char** pstrDecode, char* strDest, short sMaxStrLength, int buffer_length )
{
	unsigned short usTemp;
	unsigned short usTempLength;
	unsigned short usRealLength;

	if(pstrDecode == 0 || *pstrDecode == 0 || strDest == 0 || sMaxStrLength <= 0 )
	{
		return 0;
	}

	memcpy( ( void* )&usTemp, ( const void* )( *pstrDecode ), sizeof( unsigned short ) );

	usTempLength = ntohs( usTemp );

	if (int(usTempLength + sizeof( unsigned short )) <= buffer_length)
	{
		if( usTempLength > sMaxStrLength )
		{
			usRealLength = sMaxStrLength;
		}
		else
		{
			usRealLength = usTempLength;
		}

		*pstrDecode += sizeof( unsigned short );
		memcpy( ( void* )strDest, ( const void* )( *pstrDecode ), usRealLength );
		*pstrDecode += usTempLength;

		strDest[usRealLength] = '\0';

		return ( int )( usTempLength + sizeof( unsigned short ) );
	}
	return 0;
}

int EncodeMemory( unsigned char** pstrEncode, const char *pcSrc, short sMemSize)
{
	if(pstrEncode == 0 || *pstrEncode == 0 || pcSrc == 0 || sMemSize <= 0 )
	{
		return 0;
	}
	memcpy( ( void* )( *pstrEncode ), ( const void* )pcSrc, sMemSize );
	*pstrEncode += sMemSize;
	return sMemSize;
}

int DecodeMemory( unsigned char** pstrDecode, char *pcDest, short sMemSize, int buffer_length)
{
	if(pstrDecode == 0 || *pstrDecode == 0 || pcDest == 0 || sMemSize <= 0 )
	{
		return 0;
	}

	if (sMemSize <= buffer_length)
	{
		memcpy( ( void* )pcDest, ( const void* )( *pstrDecode ), sMemSize );
		*pstrDecode += sMemSize;
		return sMemSize;
	}
	return 0;
}
