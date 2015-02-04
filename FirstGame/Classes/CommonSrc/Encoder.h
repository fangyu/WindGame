#ifndef _ENCODER_H_
#define _ENCODER_H_

int EncodeChar( unsigned char** pstrEncode, unsigned char ucSrc );
int DecodeChar( unsigned char** pstrDecode, unsigned char *pucDest );

int EncodeShort( unsigned char** pstrEncode, unsigned short usSrc );
int DecodeShort( unsigned char** pstrDecode, unsigned short *pusDest );

int EncodeLong( unsigned char** pstrEncode, unsigned long ulSrc );
int DecodeLong( unsigned char** pstrDecode, unsigned long *pulDest );

int EncodeLongLong( unsigned char** pstrEncode, unsigned long long ulSrc );
int DecodeLongLong( unsigned char** pstrDecode, unsigned long long *pulDest );

int EncodeInt( unsigned char** pstrEncode, unsigned int uiSrc );
int DecodeInt( unsigned char** pstrDecode, unsigned int *puiDest );

int EncodeString( unsigned char** pstrEncode, const char* strSrc, short sMaxStrLength);
int DecodeString( unsigned char** pstrDecode, char* strDest, short sMaxStrLength, int buffer_length );

int EncodeMemory( unsigned char** pstrEncode, const char *pcSrc, short sMemSize);
int DecodeMemory( unsigned char** pstrDecode, char *pcDest, short sMemSize, int buffer_length);

#endif
