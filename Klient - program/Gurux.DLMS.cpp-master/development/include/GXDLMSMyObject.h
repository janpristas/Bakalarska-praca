/**
 *
 **/

#ifndef GXDLMSMYOBJECT_H
#define GXDLMSMYOBJECT_H

#include "GXDLMSObject.h"

class CGXDLMSMyObject : public CGXDLMSObject 
{

	protected:
		std::string m_Value;

		// SN Constructor
		// CGXDLMSMyObject(DLMS_OBJECT_TYPE type, std::string ln, unsigned short sn);

	public:
		// Constructor
		CGXDLMSMyObject(void);

		// SN Constructor
		// CGXDLMSMyObject(std::string ln, unsigned short sn);

		// LN Constructor
		// CGXDLMSMyObject(std::string ln);

		std::string GetValue();

		void SetValue(std::string value);

		void Reset();

		int GetAttributeCount();

		int GetMethodCount();

		void GetValues(std::vector<std::string>& values);

		int GetDataType(int index, DLMS_DATA_TYPE& type);

		virtual int GetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e);

		virtual int SetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e);

		virtual int Invoke(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e);

		void GetAttributeIndexToRead(std::vector<int>& attributes);

};
#endif //GXDLMSMY_OBJECT_H
