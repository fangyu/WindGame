#ifndef DBCFILE_H_
#define DBCFILE_H_
#include <vector>
#include <map>
#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
class DBCFile	
{
	// Data type
protected:
	enum FIELD_TYPE
	{
		FIELD_TYPE_INT,		// ����
		FIELD_TYPE_FLOAT,	// ������
		FIELD_TYPE_STRING	// �ַ�
	};

	typedef std::map<int, char*> FILED_INDEX;
	typedef std::vector<char> FIELD_DATA;
	typedef std::vector<FIELD_TYPE>	FIELD_TYPE_VEC;
	typedef std::vector<std::string> FIELD_DATA_STRING;

	// Interface
public:
	DBCFile();
	virtual ~DBCFile();
	bool Load(const char* fileName, const char* typeFormat = NULL);
	bool LoadFromBuffer(const char* buf, unsigned long size);
	bool Save();

	const char* IterateRecord(int pos) const;

	const char* GetRecord(int index) const;
	
	bool SetRecord(const char* record);
	bool DeleteRecord(int index);
	int GetRecordNum() const { return m_recordNum; }
	const char* GetLastError() const { return m_lastError; }
	const char* GetFileName() const { return m_fileName.c_str(); }
	const char* GetTypeFormat() const { return m_typeFormat.c_str(); }

protected:
	static const char* ReadLine(char* lineBuffer, int bufferSize, const char* fileImageBegin, const char* fileImageEnd, char separator);
	static bool ParseLine(FIELD_DATA_STRING& fields, const char* lineBuffer, char separator, bool emptyFieldIsError = false);

	bool ProcessFileImage(const char* fileImage, const char* fileImageEnd, const char* typeFormat, const char* fileName);
	bool CreateIndex();
	bool GetIndex(const char* record, int& index) const;
	bool ModifyRecord(const char* record);
	bool InsertRecord(const char* record);
	char* GetModifiableRecord(int index);
	const char* GetRecordByPos(int recordPos) const;
	char* GetRecordByPos(int recordPos);
	void ReleaseRecord(char* record);
	bool CheckType(const FIELD_TYPE_VEC& fieldType, const char* typeFormat);

private:
	char* SaveString(const char* pSrc);
	int   ConvertEncoding(char* from_charset, char* to_charset, 
							 char* inbuf, size_t inlen,
							 char* outbuf, size_t outlen);
protected:
	FIELD_TYPE_VEC m_fieldType;
	int m_recordSize;

	FIELD_DATA m_field;
	int m_recordNum;
	FILED_INDEX m_fieldIndex;
	std::string m_fileHeadInfo;
	std::string m_fileName;
	std::string m_typeFormat;

	//std::string m_lastError;
	char m_lastError[1024];

private:
	DBCFile(const DBCFile&);
	void operator=(const DBCFile&);
};
#endif
