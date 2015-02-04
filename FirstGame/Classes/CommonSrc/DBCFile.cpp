#include <map>
#include <errno.h>
#include "DBCFile.h"
#include "cocos2d.h"
#include <iconv.h>
using namespace cocos2d;

#define EMPTY_STRING	""

const int LINE_BUFFER_SIZE = 10240;

const char* FIELD_TYPE_INT_STR = "INT";
const char* FIELD_TYPE_FLOAT_STR = "FLOAT";
const char* FIELD_TYPE_STRING_STR = "STRING";

const int FIELD_TYPE_INT_LEN = 4;
const int FIELD_TYPE_FLOAT_LEN = 4;
const int FIELD_TYPE_STRING_LEN = sizeof(char*);

const char FIELD_TYPE_INT_CHAR = 'i';
const char FIELD_TYPE_FLOAT_CHAR = 'f';
const char FIELD_TYPE_STRING_CHAR = 's';

bool DBCFile::ParseLine(FIELD_DATA_STRING& fields, const char* lineBuffer, char separator, bool emptyFieldIsError /* = false */)
{
	fields.clear();
	std::string line = lineBuffer;
	if (line.empty())
		return false;

	std::string::size_type left = 0;
	std::string::size_type right = line.find_first_of(separator);

	if (right == std::string::npos)
		right = line.length();

	while (true)
	{
		std::string field = line.substr(left, right - left);
		if (field.length() == 0 && emptyFieldIsError)
			return false;

		if (field[0] == '"')
		{
			const unsigned int MAX_BUFFER_SIZE = 8192;
			char buffer[MAX_BUFFER_SIZE];
			if (field.length() >= MAX_BUFFER_SIZE)
				fields.push_back("");
			else
			{
				char* f = buffer;
				for (size_t i=0; i<field.length(); ++i)
				{
					if (i == 0 || i == field.length() - 1)
						continue;
					if (field[i] == '"')
						++i;
					*(f++) = field[i];
				}
				*f = 0;
				fields.push_back(buffer);
			}
		}
		else
			fields.push_back(field);

		if (right == line.length())
			break;

		left = right + 1;
		right = line.substr(left).find_first_of(separator);
		if (right != std::string::npos)
			right += left;
		else
			right = line.length();
	}

	return true;
}

const char* DBCFile::ReadLine(char* lineBuffer, int bufferSize, const char* fileImageBegin, const char* fileImageEnd, char separator)
{
	if (lineBuffer == NULL || fileImageBegin == NULL || fileImageEnd == NULL)
		return NULL;

	const char* currPos = fileImageBegin;
	if (currPos >= fileImageEnd || *currPos == 0)
		return 0;

	bool quote = false;
	while (true)
	{
		if (currPos >= fileImageEnd)
			break;
		if (currPos - fileImageBegin + 1 /* for '\0' */ >= bufferSize)
			break;
		if (*currPos == 0)
			break;
		if (!quote && (*currPos == '\r' || *currPos == '\n'))
			break;

		if (*currPos == '"')
		{
			if (currPos - 1 < fileImageBegin || *(currPos - 1) == separator)
				quote = true;
			else if (currPos + 1 == fileImageEnd
				|| *(currPos + 1) == separator || *(currPos + 1) == '\r'
				|| *(currPos + 1) == '\n'|| *(currPos + 1) == 0)
				quote = false;
		}

		*(lineBuffer++) = *(currPos++);
	}

	if (currPos - fileImageBegin + 1 >= bufferSize)
		return 0;

	*lineBuffer = 0;

	// skip all next \r and \n
	while (currPos < fileImageEnd && *currPos != 0 && (*currPos=='\r' || *currPos=='\n'))
		currPos++;

	return currPos;
}

bool DBCFile::CheckType(const FIELD_TYPE_VEC& fieldType, const char* typeFormat)
{
	if (typeFormat == NULL || *typeFormat == 0)
		return true;

	size_t typeFormatLen = strlen(typeFormat);
	if (typeFormatLen != fieldType.size())
	{
		sprintf(m_lastError, "DBC fileType number error, %lu cols in file,%lu cols in type string(FileName=%s)",
						fieldType.size(), typeFormatLen, m_fileName.c_str());
		return false;
	}

	for (unsigned int i=0; i<typeFormatLen; ++i)
	{
		switch (fieldType[i])
		{
		case FIELD_TYPE_INT:
			if (typeFormat[i] != FIELD_TYPE_INT_CHAR)
			{
				sprintf(m_lastError, "DBC file error at col %u ,type is %c, in program the typs is %c(FileName=%s)"
						, i, FIELD_TYPE_INT_CHAR, typeFormat[i], m_fileName.c_str());
				return false;
			}
			break;
		case FIELD_TYPE_FLOAT:
			if (typeFormat[i] != FIELD_TYPE_FLOAT_CHAR)
			{
				sprintf(m_lastError, "DBC file error at col %u ,type is %c, in program the typs is %c(FileName=%s)"
						, i, FIELD_TYPE_FLOAT_CHAR, typeFormat[i], m_fileName.c_str());
				return false;
			}
			break;
		case FIELD_TYPE_STRING:
			if (typeFormat[i] != FIELD_TYPE_STRING_CHAR)
			{
				sprintf(m_lastError, "DBC file error at col %d ,type is %c, in program the typs is %c(FileName=%s)"
						, i, FIELD_TYPE_STRING_CHAR, typeFormat[i], m_fileName.c_str());
				return false;
			}
			break;
		default:
			return false;
		}
	}

	return true;
}

char* DBCFile::SaveString(const char* pSrc)
{
	if (!pSrc)
		return (char*)EMPTY_STRING;

	size_t srclen = strlen(pSrc);
	size_t dwNum = 4 * (srclen + 1);
	char* pDes = new char[dwNum];
	char from_charset[10] = {0};
	char to_charset[10] = {0};
	//sprintf(from_charset,"GBK");
	//sprintf(to_charset,"UTF8");
    //modify by liws
    sprintf(from_charset,"gbk");
	sprintf(to_charset,"utf-8");
    //end modify by liws
    //CCLog("ConvertEncoding  before");
	int ret = ConvertEncoding(from_charset, to_charset, const_cast<char*>(pSrc), srclen, pDes, dwNum);
    //CCLog("ConvertEncoding  end");
	if(ret !=0)
	{
		delete []pDes;
		return (char*)EMPTY_STRING;
	}
	return pDes;
}

DBCFile::DBCFile()
{
	m_recordSize = 0;
	m_recordNum = 0;
	memset((void*)m_lastError, 0, sizeof(m_lastError));
}

DBCFile::~DBCFile()
{
	for (int i=0; i<this->GetRecordNum(); ++i)
		this->ReleaseRecord(this->GetRecordByPos(i));
}

bool DBCFile::ProcessFileImage(const char* fileImage, const char* fileImageEnd, const char* typeFormat, const char* fileName)
{
    
	if (!fileImage || !fileImageEnd || !fileName)
    {
        CCLog("load DBCFile failed");
        return false;
    }
		

    
	char lineBuffer[LINE_BUFFER_SIZE];

	const char* currFileImagePos = fileImage;
	currFileImagePos = DBCFile::ReadLine(lineBuffer, LINE_BUFFER_SIZE, currFileImagePos, fileImageEnd, '\t');
	if (!currFileImagePos)
	{
		sprintf(m_lastError, "read DBC file first line error ,record too long(MaxSize=%d bytes;FileName=%s)",
			LINE_BUFFER_SIZE, fileName);
		return false;
	}

    
	FIELD_DATA_STRING strField;
	if (!DBCFile::ParseLine(strField, lineBuffer, '\t', true))
	{
		sprintf(m_lastError, "DBC file first line should not be null FileName=%s", fileName);
		return false;
	}

    
	if (0 >= strField.size())
	{
		sprintf(m_lastError, "DBC index error, index col define error");
		return false;
	}

    
	if (strField[0] != FIELD_TYPE_INT_STR)
	{
		sprintf(m_lastError,"DBC filed type error, index col type should be \"%s\"FileName=%s, should not use Unicode",
			FIELD_TYPE_INT_STR, fileName);
		return false;
	}

    
	m_fieldType.resize(strField.size());
	m_recordSize = 0;
	for (int i=0; i<(int)m_fieldType.size(); ++i) 
	{
		if (strField[i] == FIELD_TYPE_INT_STR)
		{
			m_fieldType[i] = FIELD_TYPE_INT;
			m_recordSize += FIELD_TYPE_INT_LEN;
		}
		else if (strField[i] == FIELD_TYPE_FLOAT_STR)
		{
			m_fieldType[i] = FIELD_TYPE_FLOAT;
			m_recordSize += FIELD_TYPE_FLOAT_LEN;
		}
		else if (strField[i] == FIELD_TYPE_STRING_STR)
		{
			m_fieldType[i] = FIELD_TYPE_STRING;
			m_recordSize += FIELD_TYPE_STRING_LEN;
		}
		else
		{
			sprintf(m_lastError, "undefined field type (%s), supported type:%s %s %s(FileName=%s)"
							, strField[i].c_str(), FIELD_TYPE_INT_STR, FIELD_TYPE_FLOAT_STR
							, FIELD_TYPE_STRING_STR, fileName);
			return false;
		}
	}

    
	if (!DBCFile::CheckType(m_fieldType, typeFormat))
		return false;

	m_fileHeadInfo = lineBuffer;

    
	currFileImagePos = DBCFile::ReadLine(lineBuffer, LINE_BUFFER_SIZE, currFileImagePos, fileImageEnd, '\t');
	if (!currFileImagePos)
	{
       
		sprintf(m_lastError, "description filed null error(FileName=%s))", fileName);
		return false;
	}

    
	m_fileHeadInfo += "\n";
	m_fileHeadInfo += lineBuffer;
	m_fileHeadInfo += "\n";

	m_recordNum = 0;
	int fieldNum = (int)m_fieldType.size();
	do
	{
        
		currFileImagePos = DBCFile::ReadLine(lineBuffer, LINE_BUFFER_SIZE, currFileImagePos, fileImageEnd, '\t');
		if (!currFileImagePos)
			break;

        
		// ���ע����
		if (lineBuffer[0] == '#')
			continue;

		if (!DBCFile::ParseLine(strField, lineBuffer, '\t'))
		{
			continue;
		}

		if ((int)strField.size() < fieldNum) 
		{
			// ���Ͽո�
			int subNum = fieldNum - (int)strField.size();
			for (int i=0; i<subNum; ++i)
				strField.push_back("");
		}

		// �����в���Ϊ��
		if (strField[0].empty())
		{
			continue;
		}

        
		for (int i=0; i<fieldNum; ++i)
		{
            
			size_t len = m_field.size();
			switch (m_fieldType[i])
			{
			case FIELD_TYPE_INT:
				{
                  
					m_field.resize(len + FIELD_TYPE_INT_LEN);
					int intValue = atoi(strField[i].c_str());
					memcpy(&m_field[len], &intValue, FIELD_TYPE_INT_LEN);
				}
				break;
			case FIELD_TYPE_FLOAT:
				{
                   
					m_field.resize(len + FIELD_TYPE_FLOAT_LEN);
					float floatValue = (float)atof(strField[i].c_str());
					memcpy(&m_field[len], &floatValue, FIELD_TYPE_FLOAT_LEN);
				}
				break;
			case FIELD_TYPE_STRING:
				{
                    
					//size_t newFieldLen = strField[i].length() + 1;
					//char* newField = new char[newFieldLen];
					//memcpy(newField, strField[i].c_str(), newFieldLen);
                    if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
                    {
                        //是 iOS  平台
                        char* newField = SaveString(strField[i].c_str());
                        m_field.resize(len + FIELD_TYPE_STRING_LEN);
                        memcpy(&m_field[len], &newField, FIELD_TYPE_STRING_LEN);
                    }
                    else if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
                    {
//                        //android 平台
//                        char* newField = strdup(strField[i].c_str());
//                        m_field.resize(len + FIELD_TYPE_STRING_LEN);
//                        memcpy(&m_field[len], &newField, FIELD_TYPE_STRING_LEN);
                        
                        //是 iOS  平台
                        char* newField = SaveString(strField[i].c_str());
                        m_field.resize(len + FIELD_TYPE_STRING_LEN);
                        memcpy(&m_field[len], &newField, FIELD_TYPE_STRING_LEN);
                    }
	
				}
				break;
			}
		}

		++m_recordNum;

	} while(true);

   
	// ���������
	return this->CreateIndex();
}

bool DBCFile::Load(const char* fileName, const char* typeFormat /* = NULL */)
{
	if (!m_fileName.empty())
		return false;
	if (!fileName)
		return false;
	m_fileName = fileName;
	if (typeFormat != NULL)
		m_typeFormat = typeFormat;

	FILE* file = fopen(fileName, "rb");
	if (!file)
	{
		sprintf(m_lastError, "open DBC file %s failed ", fileName);
		return false;
	}

	fseek(file, 0, SEEK_END);
	const int FILE_SIZE = ftell(file);
	fseek(file, 0, SEEK_SET);

	char* fileImage = new char[FILE_SIZE + 1];
	fread(fileImage, 1, FILE_SIZE, file);
	fileImage[FILE_SIZE] = 0;

	bool success = ProcessFileImage(fileImage, fileImage + FILE_SIZE + 1, typeFormat, fileName);

	delete[] fileImage;
	fileImage = 0;

	fclose(file);

	return success;
}

bool DBCFile::LoadFromBuffer(const char* buf, unsigned long size)
{
    char* pfileImage = new char[size+1];
    if (!pfileImage) {
        return false;
    }
    
    memcpy(pfileImage,buf, size);
    pfileImage[size] = 0;
	bool success = ProcessFileImage(pfileImage, pfileImage + size + 1, NULL, "buffer");
    
    delete [] pfileImage;
    
    return success;
}

bool DBCFile::Save()
{
	FILE* newFile = fopen(m_fileName.c_str(), "wb");
	if (!newFile)
	{
		sprintf(m_lastError,"save file error %s (FileName=%s)",
			strerror(errno), m_fileName.c_str());
		return false;
	}

	fprintf(newFile, "%s", m_fileHeadInfo.c_str());

	for (int i=0; i<m_recordNum; ++i)
	{
		char* record = this->GetRecordByPos(i);
		if (!record)
			continue;

		// �����б��в����ڵļ�¼��д�ļ�
		int index;
		if (!this->GetIndex(record, index))
			continue;
		if (m_fieldIndex.find(index) == m_fieldIndex.end())
			continue;

		// ��ʼд�ļ�
		int fieldPos = 0;
		for (int j=0; j<(int)m_fieldType.size(); ++j)
		{
			char* curField = record + fieldPos;
			switch (m_fieldType[j])
			{
			case FIELD_TYPE_INT:
				fprintf(newFile, "%d", *(int*)curField);
				fieldPos += FIELD_TYPE_INT_LEN;
				break;
			case FIELD_TYPE_FLOAT:
				fprintf(newFile, "%f", *(float*)curField);
				fieldPos += FIELD_TYPE_FLOAT_LEN;
				break;
			case FIELD_TYPE_STRING:
				if (*(char**)curField == NULL)
					fprintf(newFile, " ");
				else
				{
					bool quote = false;
					for (char* i=*(char**)curField; *i!='\0'; ++i)
					{
						if (*i == '\t' || *i == '\r' || *i == '\n' || *i == '"')
						{
							quote = true;
							break;
						}
					}

					for (char* i=*(char**)curField; *i!='\0'; ++i)
					{
						if (i == *(char**)curField && quote)
							fprintf(newFile, "\"");
						if (*i == '"')
							fprintf(newFile, "\"");
						fprintf(newFile, "%c", *i);
					}
					if (quote)
						fprintf(newFile, "\"");
				}
				fieldPos += FIELD_TYPE_STRING_LEN;
				break;
			default:
				break;
			}

			if (j != (int)m_fieldType.size() - 1)
				fprintf(newFile, "\t");
			else
				fprintf(newFile, "\r\n");
		}
	}

	fclose(newFile);

	return true;
}

bool DBCFile::CreateIndex()
{
	m_fieldIndex.clear();

	for (int i=0; i<(int)m_recordNum; ++i)
	{
		char* record = &(m_field[i * m_recordSize]);
		int index;
		if (!this->GetIndex(record, index))
		{
			sprintf(m_lastError,"DBC create index error FileName=%s",
				m_fileName.c_str());
			return false;
		}

		FILED_INDEX::iterator it = m_fieldIndex.find(index);
		if (it != m_fieldIndex.end())
		{
			sprintf(m_lastError,"DBC index conflict, the index is %d (FileName=%s)",
				index, m_fileName.c_str());
			return false;
		}
		m_fieldIndex.insert(std::make_pair(index, record));
	}

	return true;
}

bool DBCFile::GetIndex(const char* record, int& index) const
{
	if (!record)
		return false;
	index = *(int*)record;
	return true;
}

const char* DBCFile::GetRecord(int index) const
{
	FILED_INDEX::const_iterator it = m_fieldIndex.find(index);
	if (it == m_fieldIndex.end())
		return NULL;
	return it->second;
}

char* DBCFile::GetModifiableRecord(int index)
{
	FILED_INDEX::iterator it = m_fieldIndex.find(index);
	if (it == m_fieldIndex.end())
		return NULL;
	return it->second;
}

const char* DBCFile::IterateRecord(int pos) const
{
	return this->GetRecordByPos(pos);
}

bool DBCFile::SetRecord(const char* record)
{
	if (!record)
		return false;
	int index;
	if (!this->GetIndex(record, index))
		return false;

	char* oldRecord = this->GetModifiableRecord(index);
	if (oldRecord)
		return this->ModifyRecord(record);
	else
		return this->InsertRecord(record);
}

bool DBCFile::ModifyRecord(const char* record)
{
	if (!record)
		return false;
	int index;
	if (!this->GetIndex(record, index))
		return false;
	char* oldRecord = this->GetModifiableRecord(index);
	if (!oldRecord)
		return false;

	int fieldPos = 0;
	for (int i=0; i<(int)m_fieldType.size(); ++i)
	{
		switch (m_fieldType[i])
		{
		case FIELD_TYPE_INT:
			memcpy(oldRecord + fieldPos, record + fieldPos, FIELD_TYPE_INT_LEN);
			fieldPos += FIELD_TYPE_INT_LEN;
			break;
		case FIELD_TYPE_FLOAT:
			memcpy(oldRecord + fieldPos, record + fieldPos, FIELD_TYPE_FLOAT_LEN);
			fieldPos += FIELD_TYPE_FLOAT_LEN;
			break;
		case FIELD_TYPE_STRING:
			{
				size_t len = 1;
				const char* str = *((char**)(record + fieldPos));
				if (str != NULL)
					len = strlen(str) + 1;
				char* newStr = new char[len];

				if (str != NULL)
					memcpy(newStr, str, len);
				else
					newStr[0] = 0;
				delete[] *((char**)(oldRecord + fieldPos));
				memcpy(oldRecord + fieldPos, &newStr, FIELD_TYPE_STRING_LEN);

				fieldPos += FIELD_TYPE_STRING_LEN;
			}
			break;
		default:
			break;
		}
	}
	
	return true;
}

bool DBCFile::InsertRecord(const char* record)
{
	if (!record)
		return false;
	int index;
	if (!this->GetIndex(record, index))
		return false;
	if (this->GetRecord(index))
		return false;

	int fieldPos = 0;
	for (int i=0; i<(int)m_fieldType.size(); ++i)
	{
		size_t len = m_field.size();
		switch (m_fieldType[i])
		{
		case FIELD_TYPE_INT:
			m_field.resize(len + FIELD_TYPE_INT_LEN);
			memcpy(&m_field[len], record + fieldPos, FIELD_TYPE_INT_LEN);
			fieldPos += FIELD_TYPE_INT_LEN;
			break;
		case FIELD_TYPE_FLOAT:
			m_field.resize(len + FIELD_TYPE_FLOAT_LEN);
			memcpy(&m_field[len], record + fieldPos, FIELD_TYPE_FLOAT_LEN);
			fieldPos += FIELD_TYPE_FLOAT_LEN;
			break;
		case FIELD_TYPE_STRING:
			{
				m_field.resize(len + FIELD_TYPE_STRING_LEN);

				size_t strLen = 1;
				const char* str = *((char**)(record + fieldPos));
				if (str != NULL)
					strLen = strlen(str) + 1;
				char* newStr = new char[strLen];

				if (str != NULL)
					memcpy(newStr, str, strLen);
				else
					newStr[0] = 0;
				memcpy(&m_field[len], &newStr, FIELD_TYPE_STRING_LEN);

				fieldPos += FIELD_TYPE_STRING_LEN;
			}
			break;
		default:
			break;
		}
	}

	++m_recordNum;
	return this->CreateIndex();
}


bool DBCFile::DeleteRecord(int index)
{
	FILED_INDEX::iterator it = m_fieldIndex.find(index);
	if (it == m_fieldIndex.end())
		return false;

	char* memoryBegin = it->second;
	char* memoryEnd = memoryBegin + m_recordSize - 1;
	FIELD_DATA::iterator itDataBegin = m_field.begin();
	FIELD_DATA::iterator itDataEnd = itDataBegin;
	FIELD_DATA::iterator itData = itDataBegin;
	for (; itData != m_field.end(); ++itData)
	{
		char* dataAddr = &(*itData);
		if (dataAddr == memoryBegin)
			itDataBegin = itData;
		else if (dataAddr == memoryEnd)
			itDataEnd = itData;
	}

	if (itDataEnd != m_field.begin() && itDataEnd != m_field.end())
	{
		this->ReleaseRecord(memoryBegin);
		m_field.erase(itDataBegin, itDataEnd + 1);
		m_fieldIndex.erase(it);
		--m_recordNum;
		return this->CreateIndex();
	}

	return false;
}

const char* DBCFile::GetRecordByPos(int recordPos) const
{
	int pos = recordPos * m_recordSize;

	if (pos < 0 || pos >= (int)m_field.size()) 
	{
		return NULL;
	}

	return &(m_field[pos]);
}

char* DBCFile::GetRecordByPos(int recordPos)
{
	int pos = recordPos * m_recordSize;

	if (pos < 0 || pos >= (int)m_field.size()) 
	{
		return NULL;
	}

	return &(m_field[pos]);
}

void DBCFile::ReleaseRecord(char* record)
{
	if (!record)
		return;

	int fieldPos = 0;
	for (int i=0; i<(int)m_fieldType.size(); ++i)
	{
		if (m_fieldType[i] == FIELD_TYPE_INT)
			fieldPos += FIELD_TYPE_INT_LEN;
		else if (m_fieldType[i] == FIELD_TYPE_FLOAT)
			fieldPos += FIELD_TYPE_FLOAT_LEN;
		else if (m_fieldType[i] == FIELD_TYPE_STRING)
		{
			delete[] *((char**)(record + fieldPos));
			fieldPos += FIELD_TYPE_STRING_LEN;
		}
	}
}
int DBCFile::ConvertEncoding(char* from_charset, char* to_charset, 
							 char* inbuf, size_t inlen,
							 char* outbuf, size_t outlen)
{
	if(!from_charset || !to_charset)
	{
		return -1;
	}

	iconv_t cd ;
//	char **pin = &inbuf;
//	char **pout = &outbuf;
    char **pin = &inbuf;
    char **pout = &outbuf;
    //CCLog("ConvertEncoding  iconv_open");
	cd = iconv_open(to_charset, from_charset);
   // CCLog("ConvertEncoding  iconv_open end");
	if(cd <= 0)
	{
		sprintf(m_lastError, "iconv_open error:%s", strerror(errno));
		return -1;
	}
	memset((void*)outbuf, 0, outlen);
    //CCLog("ConvertEncoding  iconv");
    
    if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    {
        if(iconv(cd, pin, &inlen, pout, &outlen) == (size_t)-1)
        {
            sprintf(m_lastError,"convert encoding error:%s", strerror(errno));
           // CCLog("convert encoding error:%s",strerror(errno));
            return -1;
        }
    }
    else
    {
        if(iconv(cd, &inbuf, &inlen, &outbuf, &outlen) == (size_t)-1)
        {
            sprintf(m_lastError,"convert encoding error:%s", strerror(errno));
            //CCLog("convert encoding error:%s",strerror(errno));
            return -1;
        }
    }
	
    
    //CCLog("ConvertEncoding  iconv  end");
	iconv_close(cd);

	return 0;
}
