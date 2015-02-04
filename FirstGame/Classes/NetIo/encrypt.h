//
//  encrypt.h
//  FirstGame
//
//  Created by wuxf on 14-1-15.
//
//

#ifndef __FirstGame__encrypt__
#define __FirstGame__encrypt__

#include <iostream>

class RC4Encry;

class encryptNetData
{
public:
    encryptNetData();
    virtual ~encryptNetData();
    
    void					EnableSecurity(void);
    void					EncryptData(unsigned char* outData, const unsigned char* inData, int len);
    void					DecryptData(unsigned char* outData, const unsigned char* inData, int len);
    
private:
    RC4Encry        *m_pEncryptor;
    RC4Encry		*m_pDecryptor;
};



#endif /* defined(__FirstGame__encrypt__) */
