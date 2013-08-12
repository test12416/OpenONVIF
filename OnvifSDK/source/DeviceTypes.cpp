
#include "OnvifSDK.h"
#include "commonTypes.h"
#include "WebDeviceBindingProxy.h"

namespace Web {
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#define EXTRA_CONSTRUCT() \
{\
    if(this->d->UTCDateTime == 0) this->d->UTCDateTime = soap_new_tt__DateTime(this->d->soap, -1);\
    if(this->d->UTCDateTime->Time == 0) this->d->UTCDateTime->Time = soap_new_tt__Time(this->d->soap, -1);\
    if(this->d->UTCDateTime->Date == 0) this->d->UTCDateTime->Date = soap_new_tt__Date(this->d->soap, -1);\
}

CLASS_CTORS(tds, Dev, SetSystemDateAndTime)


int DevSetSystemDateAndTime::SetUTCDateAndTime(int year, int month, int day, int hour, int min, int sec)
{
	this->d->UTCDateTime->Date->Year = year;
	this->d->UTCDateTime->Date->Month = month;
	this->d->UTCDateTime->Date->Day = day;

	this->d->UTCDateTime->Time->Hour = hour;
	this->d->UTCDateTime->Time->Minute = min;
	this->d->UTCDateTime->Time->Second = sec;

    this->d->DateTimeType = tt__SetDateTimeType__Manual;

	return 0;
}

int DevSetSystemDateAndTime::GetUTCDateAndTime(int & year, int & month, int & day, int & hour, int & min, int & sec) const
{
	year = this->d->UTCDateTime->Date->Year;
	month = this->d->UTCDateTime->Date->Month;
	day = this->d->UTCDateTime->Date->Day;

	hour = this->d->UTCDateTime->Time->Hour;
	min = this->d->UTCDateTime->Time->Minute;
	sec = this->d->UTCDateTime->Time->Second;

	return 0;
}

////////////////////////////////////////////////////////////////////////////////

#define EXTRA_CONSTRUCT() \
{\
}

CLASS_CTORS(tds, Dev, SetSystemDateAndTimeResponse)


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#define EXTRA_CONSTRUCT() \
{\
}

CLASS_CTORS(tds, Dev, GetSystemDateAndTime)


////////////////////////////////////////////////////////////////////////////////

#define EXTRA_CONSTRUCT() \
{\
    if(this->d->SystemDateAndTime == 0) this->d->SystemDateAndTime = soap_new_tt__SystemDateTime(this->d->soap, -1);\
    if(this->d->SystemDateAndTime->UTCDateTime == 0) this->d->SystemDateAndTime->UTCDateTime = soap_new_tt__DateTime(this->d->soap, -1);\
    if(this->d->SystemDateAndTime->UTCDateTime->Time == 0) this->d->SystemDateAndTime->UTCDateTime->Time = soap_new_tt__Time(this->d->soap, -1);\
    if(this->d->SystemDateAndTime->UTCDateTime->Date == 0) this->d->SystemDateAndTime->UTCDateTime->Date = soap_new_tt__Date(this->d->soap, -1);\
}

CLASS_CTORS(tds, Dev, GetSystemDateAndTimeResponse)


int DevGetSystemDateAndTimeResponse::SetUTCDateAndTime(int year, int month, int day, int hour, int min, int sec)
{
	this->d->SystemDateAndTime->UTCDateTime->Date->Year = year;
	this->d->SystemDateAndTime->UTCDateTime->Date->Month = month;
	this->d->SystemDateAndTime->UTCDateTime->Date->Day = day;

	this->d->SystemDateAndTime->UTCDateTime->Time->Hour = hour;
	this->d->SystemDateAndTime->UTCDateTime->Time->Minute = min;
	this->d->SystemDateAndTime->UTCDateTime->Time->Second = sec;

	return 0;
}

int DevGetSystemDateAndTimeResponse::GetUTCDateAndTime(int & year, int & month, int & day, int & hour, int & min, int & sec) const
{
	year = this->d->SystemDateAndTime->UTCDateTime->Date->Year;
	month = this->d->SystemDateAndTime->UTCDateTime->Date->Month;
	day = this->d->SystemDateAndTime->UTCDateTime->Date->Day;

	hour = this->d->SystemDateAndTime->UTCDateTime->Time->Hour;
	min = this->d->SystemDateAndTime->UTCDateTime->Time->Minute;
	sec = this->d->SystemDateAndTime->UTCDateTime->Time->Second;

	return 0;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#define EXTRA_CONSTRUCT() \
{\
}

CLASS_CTORS(tds, Dev, GetUsers)


////////////////////////////////////////////////////////////////////////////////

#define EXTRA_CONSTRUCT() \
{\
}

CLASS_CTORS(tds, Dev, GetUsersResponse)


int DevGetUsersResponse::AddUser(std::vector<std::string> user)
{
	tt__User * pUser = soap_new_tt__User(this->d->soap,-1);
	pUser->Password = soap_new_std__string(this->d->soap,-1);

	pUser->Username = user[0];
	*(pUser->Password) = user[1];
	pUser->UserLevel = user[2] == "Administrator" ? tt__UserLevel__Administrator :
						user[2] == "Operator" ? tt__UserLevel__Operator :
						user[2] == "User" ? tt__UserLevel__User :
						user[2] == "Anonymous" ? tt__UserLevel__Anonymous : tt__UserLevel__Extended;

	this->d->User.push_back(pUser);

	return 0;
}

int DevGetUsersResponse::GetUsers(std::vector<std::string> & users) const
{
	for(size_t i = 0; i < this->d->User.size(); ++i)
	{
		users.push_back(this->d->User[i]->Username);
		users.push_back(*(this->d->User[i]->Password));

		std::string strUserLevel = tt__UserLevel__Administrator ? "Administrator" :
									tt__UserLevel__Operator ? "Operator" :
									tt__UserLevel__User ? "User" :
									tt__UserLevel__Anonymous ? "Anonymous" : "Extended";

		
		users.push_back(strUserLevel);
	}

	return 0;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#define EXTRA_CONSTRUCT() \
{\
}

CLASS_CTORS(tds, Dev, GetDeviceInformation)


////////////////////////////////////////////////////////////////////////////////

#define EXTRA_CONSTRUCT() \
{\
}

CLASS_CTORS(tds, Dev, GetDeviceInformationResponse)


int DevGetDeviceInformationResponse::SetDeviceInfo(std::string strManufacturer, std::string strModel, 
					std::string strFirmwareVersion, std::string strSerialNumber, std::string strHardwareId)
{
	this->d->Manufacturer = strManufacturer;
	this->d->Model = strModel;
	this->d->FirmwareVersion = strFirmwareVersion;
	this->d->SerialNumber = strSerialNumber;
	this->d->HardwareId = strHardwareId;

	return 0;
}

int DevGetDeviceInformationResponse::GetDeviceInfo(std::string & strManufacturer, std::string & strModel,
					std::string & strFirmwareVersion, std::string & strSerialNumber, std::string & strHardwareId) const
{
	strManufacturer = this->d->Manufacturer;
	strModel = this->d->Model;
	strFirmwareVersion = this->d->FirmwareVersion;
	strSerialNumber = this->d->SerialNumber;
	strHardwareId = this->d->HardwareId;

	return 0;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#define EXTRA_CONSTRUCT() \
{\
}

CLASS_CTORS(tds, Dev, GetCapabilities)


////////////////////////////////////////////////////////////////////////////////

#define EXTRA_CONSTRUCT() \
{\
    this->d->Capabilities = soap_new_tt__Capabilities(this->d->soap,-1);\
    this->d->Capabilities->Device = soap_new_tt__DeviceCapabilities(this->d->soap,-1);\
}

CLASS_CTORS(tds, Dev, GetCapabilitiesResponse)


int DevGetCapabilitiesResponse::SetCapsDevice(std::string xaddr)
{
	this->d->Capabilities->Device->XAddr = xaddr;

	return 0;
}

int DevGetCapabilitiesResponse::GetCapsDevice(std::string & xaddr) const
{
	xaddr = this->d->Capabilities->Device->XAddr;

	return 0;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#define EXTRA_CONSTRUCT() \
{\
}

CLASS_CTORS(tds, Dev, GetServices)


////////////////////////////////////////////////////////////////////////////////

#define EXTRA_CONSTRUCT() \
{\
}

CLASS_CTORS(tds, Dev, GetServicesResponse)


int DevGetServicesResponse::AddService(std::string & nameSpace, std::string & xaddr)
{
	tds__Service * pServiceEntry = soap_new_tds__Service(this->d->soap);
	pServiceEntry->Namespace = nameSpace;
	pServiceEntry->XAddr = xaddr;
	this->d->Service.push_back(pServiceEntry);
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
} // namespace Web
