/**
 *
 **/

#include "../include/GXDLMSClient.h"
#include "../include/GXDLMSMyObject.h"

CGXDLMSMyObject::CGXDLMSMyObject() : 
	CGXDLMSObject(DLMS_OBJECT_TYPE_MY_OBJECT)
{
}

// CGXDLMSMyObject::CGXDLMSMyObject(DLMS_OBJECT_TYPE type, std::string ln, unsigned short sn) : 
// 	CGXDLMSObject(type, ln, sn)
// {
// } 

// CGXDLMSMyObject::CGXDLMSMyObject(std::string ln, unsigned short sn) :
// 	CGXDLMSObject(DLMS_OBJECT_TYPE_MY_OBJECT, ln, sn)
// {
// }

// CGXDLMSMyObject::CGXDLMSMyObject(std::string ln) : 
// 	CGXDLMSMyObject(ln, 0)
// {
// }

std::string CGXDLMSMyObject::GetValue() 
{
	return m_Value;
}

void CGXDLMSMyObject::SetValue(std::string value)
{
	m_Value = value;
}

/*
 * Reset value.
 */
void CGXDLMSMyObject::Reset()
{
    m_Value = "";
}

// Returns amount of attributes.
int CGXDLMSMyObject::GetAttributeCount()
{
    return 2;
}

// Returns amount of methods.
int CGXDLMSMyObject::GetMethodCount()
{
    return 0;
}

void CGXDLMSMyObject::GetValues(std::vector<std::string>& values)
{
    values.clear();
    std::string ln;
    GetLogicalName(ln);
    values.push_back(ln);
    values.push_back(m_Value);
}

int CGXDLMSMyObject::GetDataType(int index, DLMS_DATA_TYPE& type)
{
    if (index == 1)
    {
        type = DLMS_DATA_TYPE_OCTET_STRING;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 2)
    {
        type = DLMS_DATA_TYPE_OCTET_STRING;
        return DLMS_ERROR_CODE_OK;
    }
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

int CGXDLMSMyObject::GetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
{
    if (e.GetIndex() == 1)
    {
        int ret;
        CGXDLMSVariant tmp;
        if ((ret = GetLogicalName(this, tmp)) != 0)
        {
            return ret;
        }
        e.SetValue(tmp);
        return DLMS_ERROR_CODE_OK;
    }
    if (e.GetIndex() == 2)
    {
        // e.SetByteArray(true);
        // std::string add = GetValue();
        // GXHelpers::Replace(add, ":", ".");
        // CGXByteBuffer data;
        // CGXDLMSVariant tmp = add;
        // int ret = GXHelpers::SetData(data, DLMS_DATA_TYPE_OCTET_STRING, tmp);
        // e.SetValue(data);
        // return ret;
    	std::string tmp;
    	tmp = GetValue();
    	e.SetValue(tmp);
    	return DLMS_ERROR_CODE_OK;
    }
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

// Set value of given attribute.
int CGXDLMSMyObject::SetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
{
    if (e.GetIndex() == 1)
    {
        return SetLogicalName(this, e.GetValue());
    }
    else if (e.GetIndex() == 2)
    {
        CGXDLMSVariant newValue;
        int ret = CGXDLMSClient::ChangeType(e.GetValue(), DLMS_DATA_TYPE_OCTET_STRING, newValue);
        if (ret != DLMS_ERROR_CODE_OK)
        {
            return ret;
        }
        std::string add = e.GetValue().ToString();
        SetValue(add);
        return DLMS_ERROR_CODE_OK;

    }
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

int CGXDLMSMyObject::Invoke(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
{
    if (e.GetIndex() == 1)
    {
        Reset();
        return DLMS_ERROR_CODE_OK;
    }
    e.SetError(DLMS_ERROR_CODE_READ_WRITE_DENIED);
    return DLMS_ERROR_CODE_OK;
}

void CGXDLMSMyObject::GetAttributeIndexToRead(std::vector<int>& attributes)
{
    // LN is static and read only once.
    if (CGXDLMSObject::IsLogicalNameEmpty(m_LN))
    {
        attributes.push_back(1);
    }
    // Value
    if (!IsRead(2))
    {
        attributes.push_back(2);
    }
}
