/************************************************************************
 *                      自定义通用型的插件接口 基类
 *	 使用QGenericPlugin类继承  需要加入 gui 模块
 *	 该类是一个纯虚类  需要在插件中需要有具体实现
 *	 1、定义字符串识别 PluginInterface_iid  采用公司名.插件名.版本号来命名
 *	 2、为使程序在运行时刻可查询插件是否实现了给定接口，定义宏Q_DECLARE_INTERFACE()
 *      第一个参数是这个接口的名字，第二个参数是一个确定接口的字符串。
 *   3、在模块中实现的话，会是一个单例类, 由QPluginLoader保证
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
/*                   插件中的json描述文件数据                           */
/*                                                                      */
/************************************************************************/
typedef struct ST_PropertyData
{
	QVariant module_name;			// json中定义的模块名称
	QVariant module_icon_path;		// 模块显示的图片
	QVariant serial_number;			// 序列号
	QVariant version_number;		// 版本号
	QVariant class_name;			// 导出的类名
	QVariant absolute_path;			// 模块的绝对路径
	QVariant description;			// 描 述
} PropertyData;

using PropertyDataList = QList<PropertyData>;


/************************************************************************/
/*                 模块进行服务调用时传出的参数                         */
/*                                                                      */
/************************************************************************/
typedef struct ST_ServerReturnData
{
	std::atomic<bool> bWait;
	QByteArray sBytesContent;
} ReturnData;


/************************************************************************/
/*                        模块虚基类 定义                               */
/*                                                                      */
/************************************************************************/
class IPageWindow;
class IModuleObject
{
public:
	virtual ~IModuleObject(){}

	// 用于描述模块的序列号 模块的显示名称 模块显示图片
	virtual void ModuleProperty(int& iSerialNO, QString& sModuleName, QString& sIconPath) const = 0;
	// 描述模块的类名
	virtual QString ModuleClassName() const = 0;
	// 模块功能描述
	virtual QString ModuleDescription() const = 0;
	// 模块的版本号
	virtual QString VersionString() const = 0;
	virtual int VersionNumber() const = 0;


	virtual void instanceModule(QWidget* pParent) = 0;
	virtual void destroyModule() = 0;

	virtual IPageWindow* ModuleWidget() = 0;
	virtual QObject* ModuleBackend() = 0;
	

	// 外部请求本服务的入口
	virtual bool ModuleServer(const QByteArray sByteParams, ReturnData& recvData) = 0;

};


/************************************************************************/
/*                        插件相关的json文件定义                        */
/*                                                                      */
/************************************************************************/
QT_BEGIN_NAMESPACE
// 注意该字符串中包含"IModuleObject"，与IModuleObject虚基类名要保持一致
# define Module_iid     "com.HansRobot.Chummy.IModuleObject"
//# define Module_iid    "HansRobot.IModuleObject/1.0" 


// 该宏是定义在具体的插件类实现中使用的
#define MODULE_JSON(file) Q_PLUGIN_METADATA(IID Module_iid FILE file) Q_INTERFACES(IModuleObject)

Q_DECLARE_INTERFACE(IModuleObject, Module_iid)
QT_END_NAMESPACE

 
/************************************************************************/
/*                     线程池中用到的执行任务模块                       */
/*     将引用返回的数据进行传出                                         */
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
