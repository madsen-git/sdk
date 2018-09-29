#pragma once
#include "AC/basetype.h"
#include "AC/sysupport.h"
//#import "D:/NTools/db/msado15.dll" rename("EOF", "ADOEOF")
//using namespace ADODB;


namespace db{

class database;

//////////////////////////////////////////////////////////////////////////
// ��������
typedef enum BEParameterDirection{
	BEParameterDirectionUnknown			= 0,	//adParamUnknown,// = 0,
	BEParameterDirectionInput			= 1,	//adParamInput,// = 1,
	BEParameterDirectionOutput			= 2,	//adParamOutput,// = 2,
	BEParameterDirectionInputOUtput		= 3,	//adParamInputOutput,// = 3,
	BEParameterDirectionReturnValue		= 4		//adParamReturnValue// = 4
}BEParameterDirection;
//////////////////////////////////////////////////////////////////////////
// parameter�� 2014-10-07
// parameter������
//////////////////////////////////////////////////////////////////////////
class parameter
{
public:
	typedef std::vector<parameter *> ArrayType;
protected:
	parameter();
	parameter(const parameter &param);
	const parameter& operator=(const parameter &param);
public:
	parameter(const parameter *ppar);
	parameter(std::wstring wsName, const gtc::variant &var, BEParameterDirection dir = BEParameterDirectionInput);

	parameter(std::wstring wsName, BEParameterDirection dir = BEParameterDirectionInput);
	parameter(std::wstring wsName, bool val, BEParameterDirection dir = BEParameterDirectionInput);
	parameter(std::wstring wsName, std::wstring &val, BEParameterDirection dir = BEParameterDirectionInput);
	parameter(std::wstring wsName, const std::wstring &val, BEParameterDirection dir = BEParameterDirectionInput);
	parameter(std::wstring wsName, PCWSTR val, BEParameterDirection dir = BEParameterDirectionInput);
	parameter(std::wstring wsName, uint8_t val, BEParameterDirection dir = BEParameterDirectionInput);
	parameter(std::wstring wsName, int16_t val, BEParameterDirection dir = BEParameterDirectionInput);
	parameter(std::wstring wsName, int32_t val, BEParameterDirection dir = BEParameterDirectionInput);
	parameter(std::wstring wsName, int64_t val, BEParameterDirection dir = BEParameterDirectionInput);
	parameter(std::wstring wsName, float val, BEParameterDirection dir = BEParameterDirectionInput);
	parameter(std::wstring wsName, double val, BEParameterDirection dir = BEParameterDirectionInput);
	parameter(std::wstring wsName, const std::tm &val, BEParameterDirection dir = BEParameterDirectionInput);
	parameter(std::wstring wsName, const gtc::datetime &val, BEParameterDirection dir = BEParameterDirectionInput);
	parameter(std::wstring wsName, SBDataType &val, BEParameterDirection dir = BEParameterDirectionInput);
	parameter(std::wstring wsName, SWDataType &val, BEParameterDirection dir = BEParameterDirectionInput);
	parameter(std::wstring wsName, const SBDataType &val, BEParameterDirection dir = BEParameterDirectionInput);
	parameter(std::wstring wsName, const SWDataType &val, BEParameterDirection dir = BEParameterDirectionInput);


public:
	// ��vecParams�в�����û����ΪwsName�Ĳ���
	static parameter* find(const std::wstring &wsName, const ArrayType &vecParams);
	static void free(ArrayType &vecParams);
public:
	std::wstring getName() const;
	void setName(PCWSTR pname);
	const gtc::variant& getValue() const;
	void setValue(const gtc::variant &val);
	void setValue(int val);
	void setValue(int64_t val);
	void setValue(double val);
	void setValue(std::wstring &val);
	void setValue(const std::wstring &val);
	void setValue(const gtc::datetime &val);
	void setValue(SBDataType &val);
	void setValue(const SBDataType &val);

	BEParameterDirection getDirection() const;
	void setDirection(BEParameterDirection direction);
	BEDataType getType() const;
protected:
	std::wstring	m_wsName;
	gtc::variant	m_varValue;
	BEParameterDirection	m_beParamDirection;
};


//////////////////////////////////////////////////////////////////////////
// dataSet�� 2014-08-24
// ���ݼ�¼����װ��
//////////////////////////////////////////////////////////////////////////
class dataSet
{
public:
	dataSet() {}
	virtual ~dataSet() {}

	virtual bool eof() = 0;
	virtual void nextRow() = 0;
	virtual void finalize() = 0;

	virtual int getCols() const = 0;
	virtual int fieldIndex(const std::wstring &wsFieldName) = 0;
	virtual std::wstring fieldName(int col) = 0;

	virtual std::wstring fieldDeclType(int col) = 0;
	virtual int fieldType(int col) = 0;

	virtual gtc::variant getValue(int col) = 0;
	virtual gtc::variant getValue(const std::wstring &wsFieldName) = 0;

	virtual int32_t	getInt(int col) = 0;
	virtual int32_t getInt(const std::wstring &wsFieldName) = 0;
	virtual int64_t	getInt64(int col) = 0;
	virtual int64_t getInt64(const std::wstring &wsFieldName) = 0;
	virtual double getDouble(int col) = 0;
	virtual double getDouble(const std::wstring &wsFieldName) = 0;
	virtual std::wstring getString(int col) = 0;
	virtual std::wstring getString(const std::wstring &wsFieldName) = 0;
	virtual SBDataType getBlob(int col) = 0;
	virtual SBDataType getBlob(const std::wstring &wsFieldName) = 0;
	virtual gtc::datetime getDatetime(int col) = 0;
	virtual gtc::datetime getDatetime(const std::wstring &wsFieldName) = 0;
	virtual bool isNull(int col) = 0;
	virtual bool isNull(const std::wstring &wsFieldName) = 0;

};

////////////////////////////////////////////////////////////////////////////////////////////////////////
//	command  ��    2015-9-28
//	���ݿ��������
////////////////////////////////////////////////////////////////////////////////////////////////////////
class command
{
private:
	command();
	command(const command &cmd);
	command& operator=(const command &cmd);
public:
	command(database *pdb);
	virtual ~command();

	// ����֧��
	virtual void beginTransaction();
	virtual void commitTransaction();
	virtual void rollbackTransaction();

public:
	// �����������ݿ�ṹ���������޸ı����Ե�
	virtual int exec(const std::wstring &ssql) = 0;
	// ִ�У����������ʽΪ��@<name>
	// ִ��sql��䣬�������Ӱ�����������
	virtual int executeNonQuery(const std::wstring &ssql, bool clearParams = true) = 0;
	virtual int executeNonQuery(PCWSTR psql, bool clearParams = true) = 0;

	// ִ��sql��䣬�Żز�ѯ����ĵ�0��0��ֵ
	virtual gtc::variant executeScalar(const std::wstring &ssql, bool clearParams = true) = 0;
	virtual gtc::variant executeScalar(PCWSTR psql, bool clearParams = true) = 0;
	// ִ��sql��䣬�Żز�ѯ���
	virtual dataSet* executeReader(const std::wstring &ssql, bool clearParams = true) = 0;
	virtual dataSet* executeReader(PCWSTR psql, bool clearParams = true) = 0;
	/****************************************************************************************
		<< --- executeInsertByParameter		2014-10-21 --- >>         
		˵�������ݲ���ִ�жԱ�ptable�Ĳ���������ٶ����������Ƕ�Ӧ����ֶ���
		������
			ptable	= ���������ݱ�����
		����ֵ���ɹ�����ļ�¼����
	*****************************************************************************************/
	virtual int executeInsertByParameter(PCWSTR ptable);
	/****************************************************************************************
		<< --- executeUpdateByParameter		2014-10-21 --- >>         
		˵�������ݲ���ִ�жԱ�ptable���޸Ĳ������ٶ����������Ƕ�Ӧ����ֶ���
		������
			ptable	= ���������ݱ�����
			pwhere	= ��������������
		����ֵ���ɹ������µļ�¼����
	*****************************************************************************************/
	virtual int executeUpdateByParameter(PCWSTR ptable, PCWSTR pwhere);
public:
	// �󶨲���
	parameter* addParameter(PCWSTR pparamName, int iValue);
	parameter* addParameter(PCWSTR pparamName, int64_t llValue);
	parameter* addParameter(PCWSTR pparamName, double dblValue);
	parameter* addParameter(PCWSTR pparamName, std::wstring &wsValue);
	parameter* addParameter(PCWSTR pparamName, const std::wstring &wsValue);
	parameter* addParameter(PCWSTR pparamName, const gtc::datetime &dtValue);
	parameter* addParameter(PCWSTR pparamName, SBDataType &sbData);
	parameter* addParameter(PCWSTR pparamName, const SBDataType &sbData);
	parameter* addParameter(PCWSTR pparamName);	// �󶨿ղ���ֵ
	parameter* addParameter(parameter *par);
	void addParameter(parameter::ArrayType &params);
	// ����ָ�����ƵĲ���
	parameter* findParameter(std::wstring wsName);
	// ���²���
	parameter* updateParameter(PCWSTR pparamName, int iValue);
	parameter* updateParameter(PCWSTR pparamName, int64_t llValue);
	parameter* updateParameter(PCWSTR pparamName, double dblValue);
	parameter* updateParameter(PCWSTR pparamName, std::wstring &wsValue);
	parameter* updateParameter(PCWSTR pparamName, const std::wstring &wsValue);
	parameter* updateParameter(PCWSTR pparamName, const gtc::datetime &dtValue);
	parameter* updateParameter(PCWSTR pparamName, SBDataType &sbData);
	parameter* updateParameter(PCWSTR pparamName, const SBDataType &sbData);
	parameter* updateParameter(PCWSTR pparamName);	//��ָ������ֵ��Ϊnull
	// �ͷŲ���ղ���
	void clearParameter();
protected:
	database				*m_pdb;				//
	std::wstring			m_wsCmdText;		// 
	parameter::ArrayType	m_vecParameter;		// 
};
//////////////////////////////////////////////////////////////////////////
// database�� 2014-08-24
// ���ݿ������
//////////////////////////////////////////////////////////////////////////
class database
{
public:
	database();
	virtual ~database();

	virtual bool open(const std::wstring &dbFile);
	virtual bool close() = 0;
	virtual std::wstring getLastErrorInfo() const;

	// ����֧��
	virtual void beginTransaction();
	virtual void commitTransaction();
	virtual void rollbackTransaction();


public:
	virtual command* createCommand() = 0;
	virtual void* getCmdSet() = 0;
	virtual void setTimeout(int iMillisecs);
protected:
	std::wstring			m_wsCnnString;
	int						m_iTimeout;		// 
	//parameter::ArrayType	m_vecParameter;


};
}