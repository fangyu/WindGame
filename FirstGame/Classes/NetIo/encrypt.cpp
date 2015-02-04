//
//  encrypt.cpp
//  FirstGame
//
//  Created by wuxf on 14-1-15.
//
//

#include "encrypt.h"
#include "RC4Encry.h"

unsigned char g_RC4Key[8] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef};

encryptNetData::encryptNetData()
{
    m_pEncryptor = new RC4Encry();
    m_pDecryptor = new RC4Encry();
}

encryptNetData::~encryptNetData()
{
    delete m_pEncryptor;
    m_pEncryptor = NULL;
    
    delete m_pDecryptor;
    m_pDecryptor = NULL;
}

void encryptNetData::EnableSecurity(void)
{
    m_pEncryptor->SetKey(g_RC4Key, sizeof(g_RC4Key));
	m_pDecryptor->SetKey(g_RC4Key, sizeof(g_RC4Key));
}

void encryptNetData::EncryptData(unsigned char* outData, const unsigned char* inData, int len)
{
	m_pEncryptor->Encrypt(outData, inData, len);
}

void encryptNetData::DecryptData(unsigned char* outData, const unsigned char* inData, int len)
{
	m_pDecryptor->Encrypt(outData, inData, len);
}
