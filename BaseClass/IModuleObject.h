/************************************************************************
 *                      �Զ���ͨ���͵Ĳ���ӿ� ����
 *	 ʹ��QGenericPlugin��̳�  ��Ҫ���� gui ģ��
 *	 ������һ��������  ��Ҫ�ڲ������Ҫ�о���ʵ��
 *	 1�������ַ���ʶ�� PluginInterface_iid  ���ù�˾��.�����.�汾��������
 *	 2��Ϊʹ����������ʱ�̿ɲ�ѯ����Ƿ�ʵ���˸����ӿڣ������Q_DECLARE_INTERFACE()
 *      ��һ������������ӿڵ����֣��ڶ���������һ��ȷ���ӿڵ��ַ�����
 *   3����ģ����ʵ�ֵĻ�������һ��������, ��QPluginLoader��֤
 *
 ************************************************************************/
#pragma once
#include <QtCore/qglobal.h>
#include <QMetaClassInfo>		//#include <QtPlugin>
#include <QPluginLoader>
#include <QByteArray>
#include <QRunnable>
#include <QVariant>
#include <QString>

#include <functional>
#include <atomic>

/************************************************************************/
/*                   ����е�json�����ļ�����                           */
/*                                                                      */
/************************************************************************/
typedef struct ST_PropertyData
{
	QVariant module_name;			// json�ж����ģ������
	QVariant module_icon_path;		// ģ����ʾ��ͼƬ
	QVariant serial_number;			// ���к�
	QVariant version_number;		// �汾��
	QVariant class_name;			// ����������
	QVariant absolute_path;			// ģ��ľ���·��
	QVariant description;			// �� ��
} PropertyData;

using PropertyDataList = QList<PropertyData>;


/************************************************************************/
/*                 ģ����з������ʱ�����Ĳ���                         */
/*                                                                      */
/************************************************************************/
typedef struct ST_ServerReturnData
{
	std::atomic<bool> bWait;
	QByteArray sBytesContent;
} ReturnData;


/************************************************************************/
/*                        ģ������� ����                               */
/*                                                                      */
/************************************************************************/
class IPageWindow;
class IModuleObject
{
public:
	virtual ~IModuleObject(){}

	// ��������ģ������к� ģ�����ʾ���� ģ����ʾͼƬ
	virtual void ModuleProperty(int& iSerialNO, QString& sModuleName, QString& sIconPath) const = 0;
	// ����ģ�������
	virtual QString ModuleClassName() const = 0;
	// ģ�鹦������
	virtual QString ModuleDescription() const = 0;
	// ģ��İ汾��
	virtual QString VersionString() const = 0;
	virtual int VersionNumber() const = 0;


	virtual void instanceModule(QWidget* pParent) = 0;
	virtual void destroyModule() = 0;

	virtual IPageWindow* ModuleWidget() = 0;
	virtual QObject* ModuleBackend() = 0;
	

	// �ⲿ���󱾷�������
	virtual bool ModuleServer(const QByteArray sByteParams, ReturnData& recvData) = 0;

};


/************************************************************************/
/*                        �����ص�json�ļ�����                        */
/*                                                                      */
/************************************************************************/
QT_BEGIN_NAMESPACE
// ע����ַ����а���"IModuleObject"����IModuleObject�������Ҫ����һ��
# define Module_iid     "com.HansRobot.Chummy.IModuleObject"
//# define Module_iid    "HansRobot.IModuleObject/1.0" 


// �ú��Ƕ����ھ���Ĳ����ʵ����ʹ�õ�
#define MODULE_JSON(file) Q_PLUGIN_METADATA(IID Module_iid FILE file) Q_INTERFACES(IModuleObject)

Q_DECLARE_INTERFACE(IModuleObject, Module_iid)
QT_END_NAMESPACE

 
/************************************************************************/
/*                     �̳߳����õ���ִ������ģ��                       */
/*     �����÷��ص����ݽ��д���                                         */
/************************************************************************/
class ServerTask : public QRunnable
{
public:
	typedef std::function< void(ReturnData&)> Func_Request;	

	ServerTask(ReturnData& execReturn, Func_Request func)
		: m_RecvData(execReturn), Server_Func(func) { }

public:
	virtual void run()
	{
		if (nullptr == Server_Func)
		{
			m_RecvData.bWait = false;  return;
		}

		Server_Func(m_RecvData);
	}

private:
	Func_Request   Server_Func = nullptr;
	ReturnData &   m_RecvData;
};
