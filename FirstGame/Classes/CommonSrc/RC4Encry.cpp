#include "RC4Encry.h"
#include <string.h>

RC4Encry::RC4Encry(void)
{
}

RC4Encry::~RC4Encry(void)
{
}

bool RC4Encry::SetKey(const unsigned char* key, int keyLen)
{
	if (!key)
		return false;

	memset(&m_RC4Key,0,sizeof(m_RC4Key));

	register unsigned int tmp;
	register int id1,id2;
	register unsigned int *d;
	unsigned int i;

	d= &(m_RC4Key.data[0]);
	m_RC4Key.x = 0;
	m_RC4Key.y = 0;
	id1=id2=0;

#define SK_LOOP(d,n) { \
	tmp=d[(n)]; \
	id2 = (key[id1] + tmp + id2) & 0xff; \
	if (++id1 == keyLen) id1=0; \
	d[(n)]=d[id2]; \
	d[id2]=tmp; }

	for (i=0; i < 256; i++) d[i]=i;
	for (i=0; i < 256; i+=4)
	{
		SK_LOOP(d,i+0);
		SK_LOOP(d,i+1);
		SK_LOOP(d,i+2);
		SK_LOOP(d,i+3);
	}

	return true;
}

bool RC4Encry::Encrypt(unsigned char* outdata, const unsigned char* indata, int len)
{
	if (!outdata || !indata)
	{
		return false;
	}

	register unsigned int *d;
	register unsigned int x,y,tx,ty;
	size_t i;

	x=m_RC4Key.x;
	y=m_RC4Key.y;
	d=m_RC4Key.data;

#define LOOP(in,out) \
	x=((x+1)&0xff); \
	tx=d[x]; \
	y=(tx+y)&0xff; \
	d[x]=ty=d[y]; \
	d[y]=tx; \
	(out) = d[(tx+ty)&0xff]^ (in);


#define RC4_LOOP(a,b,i)	LOOP(a[i],b[i])

	i=len>>3;
	if (i)
	{
		for (;;)
		{
			RC4_LOOP(indata,outdata,0);
			RC4_LOOP(indata,outdata,1);
			RC4_LOOP(indata,outdata,2);
			RC4_LOOP(indata,outdata,3);
			RC4_LOOP(indata,outdata,4);
			RC4_LOOP(indata,outdata,5);
			RC4_LOOP(indata,outdata,6);
			RC4_LOOP(indata,outdata,7);

			indata+=8;
			outdata+=8;

			if (--i == 0) break;
		}
	}

	i=len&0x07;
	if (i)
	{
		for (;;)
		{
			RC4_LOOP(indata,outdata,0); if (--i == 0) break;
			RC4_LOOP(indata,outdata,1); if (--i == 0) break;
			RC4_LOOP(indata,outdata,2); if (--i == 0) break;
			RC4_LOOP(indata,outdata,3); if (--i == 0) break;
			RC4_LOOP(indata,outdata,4); if (--i == 0) break;
			RC4_LOOP(indata,outdata,5); if (--i == 0) break;
			RC4_LOOP(indata,outdata,6); if (--i == 0) break;
		}
	}               
	m_RC4Key.x=x;     
	m_RC4Key.y=y;

	return true;
}

