//
// --------------------------------------------------------------------------
//  Gurux Ltd
//
//
//
// Filename:        $HeadURL$
//
// Version:         $Revision$,
//                  $Date$
//                  $Author$
//
// Copyright (c) Gurux Ltd
//
//---------------------------------------------------------------------------
//
//  DESCRIPTION
//
// This file is a part of Gurux Device Framework.
//
// Gurux Device Framework is Open Source software; you can redistribute it
// and/or modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; version 2 of the License.
// Gurux Device Framework is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
//
// More information of Gurux products: http://www.gurux.org
//
// This code is licensed under the GNU General Public License v2.
// Full text may be retrieved at http://www.gnu.org/licenses/gpl-2.0.txt
//---------------------------------------------------------------------------

#include "../include/GXDLMSData.h"

//Constructor.
CGXDLMSData::CGXDLMSData() :
    CGXDLMSData("", 0)
{
}

//SN Constructor.
CGXDLMSData::CGXDLMSData(std::string ln, unsigned short sn) :
    CGXDLMSObject(DLMS_OBJECT_TYPE_DATA, ln, sn)
{

}

//LN Constructor.
CGXDLMSData::CGXDLMSData(std::string ln) :
    CGXDLMSData(ln, 0)
{

}

// Get value of COSEM Data object.
CGXDLMSVariant CGXDLMSData::GetValue()
{
    return m_Value;
}

// Set value of COSEM Data object.
void CGXDLMSData::SetValue(CGXDLMSVariant& value)
{
    m_Value = value;
}

// Returns amount of attributes.
int CGXDLMSData::GetAttributeCount()
{
    return 2;
}

// Returns amount of methods.
int CGXDLMSData::GetMethodCount()
{
    return 0;
}

void CGXDLMSData::GetValues(std::vector<std::string>& values)
{
    values.clear();
    std::string ln;
    GetLogicalName(ln);
    values.push_back(ln);
    values.push_back(m_Value.ToString());
}

void CGXDLMSData::GetAttributeIndexToRead(std::vector<int>& attributes)
{
    //LN is static and read only once.
    if (CGXDLMSObject::IsLogicalNameEmpty(m_LN))
    {
        attributes.push_back(1);
    }
    //Value
    if (CanRead(2))
    {
        attributes.push_back(2);
    }
}

int CGXDLMSData::GetDataType(int index, DLMS_DATA_TYPE& type)
{
    if (index == 1)
    {
        type = DLMS_DATA_TYPE_OCTET_STRING;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 2)
    {
        return CGXDLMSObject::GetDataType(index, type);
    }
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

// Returns value of given attribute.
int CGXDLMSData::GetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
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
    if (e.GetIndex() == 2) // Zmenena podmienka - Jan Pristas FIT VUT (Marec 2018)
    {
	// Hodnoty prveho citania su generovane automaticky funkciou rand(), citanie prebieha az od druheho
        if (count++ > 1) {
	    // Kontrola, ci preslo od posledneho citania aspon 10 sekund, aby sa mohla hodnota zmenit
            if (x < (std::time(nullptr) / 10)) {
                x = std::time(nullptr) / 10;

                bool random = false;
                std::ifstream confFile;
                std::ifstream inputFile;
                int pos = 0;
                int range = 1000;
                std::string tmp_string;
                std::string str;
                std::vector<std::string> conf;
                std::vector<std::string> message;

                tmp_string.clear();
                str.clear();
                conf.clear();
                message.clear();

                confFile.open("../../conf");
                // citanie konfiguracneho suboru
                getline(confFile, str);
                while (!confFile.fail()) {
                    conf.push_back(str);
                    getline(confFile, str);
                }
                confFile.close();

                // Nacitanie suboru s hodnotami / rozsahu nahodne generovanych cisiel
                std::cout << conf[0] << std::endl;
                if ((conf[0].find("file")) != std::string::npos) {
                    random = false;
                    for (unsigned int i = 0; i < conf[0].length(); i++) {
                        if (conf[0][i] != ' ') {
                            tmp_string += conf[0][i];
                        }
                    }

                    pos = tmp_string.find("=");
                    tmp_string.erase(0, pos + 1);

                    inputFile.open(tmp_string);
                    str.clear();

                    getline(inputFile, str);
                    while (!inputFile.fail()) {
                        message.push_back(str);
                        getline(inputFile, str);
                    }
                    confFile.close();
                    tmp_string.clear();

                } else if ((conf[0].find("rand")) != std::string::npos) {
                    random = true;
                    for (unsigned int i = 0; i < conf[0].length(); i++) {
                        if (conf[0][i] != ' ') {
                            tmp_string += conf[0][i];
                        }
                    }

                    pos = tmp_string.find("=");
                    tmp_string.erase(0, pos + 1);

                    range = std::stoi(tmp_string);

                    tmp_string.clear();
                }
		
		// Zmena hodnoty
                if (random == false) {
                    m_Value = std::stoi(message[rand() % message.size()]);
                } else {
                    m_Value = rand() % range;
                }
            }
        }
        e.SetValue(m_Value);
        return DLMS_ERROR_CODE_OK;
    }
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

// Set value of given attribute.
int CGXDLMSData::SetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
{
    if (e.GetIndex() == 1)
    {
        return SetLogicalName(this, e.GetValue());
    }
    else if (e.GetIndex() == 2)
    {
        SetValue(e.GetValue());
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}
