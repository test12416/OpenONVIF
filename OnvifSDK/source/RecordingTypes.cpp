
#include "OnvifSDK.h"
#include "commonTypes.h"
#include "soapRecordingBindingProxy.h"

#define EXTRA_CONSTRUCT() \
{\
    if (d->RecordingConfiguration != NULL) \
        return; \
    d->RecordingConfiguration = soap_new_tt__RecordingConfiguration (d->soap); \
    d->RecordingConfiguration->Source = soap_new_tt__RecordingSourceInformation (d->soap); \
}

CLASS_CTORS(trc, Rec, CreateRecording)

void
RecCreateRecording::setSource (const std::string & id, const std::string & address)
{
    d->RecordingConfiguration->Source->SourceId = id;
    d->RecordingConfiguration->Source->Address = address;
}

void
RecCreateRecording::getSource (std::string & id, std::string & address) const
{
    id = d->RecordingConfiguration->Source->SourceId;
    address = d->RecordingConfiguration->Source->Address;
}

#define EXTRA_CONSTRUCT() {}

CLASS_CTORS(trc, Rec, CreateRecordingResponse)

const std::string &
RecCreateRecordingResponse::getToken() const { return d->RecordingToken; }

void
RecCreateRecordingResponse::setToken (const std::string & str) { d->RecordingToken = str; }

/////////////////////////////////////////////////////////////////////////////////////
CLASS_CTORS(trc, Rec, DeleteRecording)

const std::string &
RecDeleteRecording::getToken() const { return d->RecordingToken; }

void
RecDeleteRecording::setToken (const std::string & str) { d->RecordingToken = str; }

CLASS_CTORS(trc, Rec, DeleteRecordingResponse)
/////////////////////////////////////////////////////////////////////////////////////
#define EXTRA_CONSTRUCT() \
{\
    if (d->JobConfiguration != NULL) \
        return; \
    d->JobConfiguration = soap_new_tt__RecordingJobConfiguration( d->soap ); \
    d->JobConfiguration->Source.push_back( soap_new_tt__RecordingJobSource( d->soap ) ); \
    d->JobConfiguration->Source[0]->SourceToken = NULL; \
    d->JobConfiguration->Source[0]->AutoCreateReceiver = new bool[1]; \
}

CLASS_CTORS(trc, Rec, CreateRecordingJob)

const std::string &
RecCreateRecordingJob::getRecording() const { return d->JobConfiguration->RecordingToken; }
void
RecCreateRecordingJob::setRecording(const std::string & token) { d->JobConfiguration->RecordingToken = token; }
bool
RecCreateRecordingJob::getMode() const { return d->JobConfiguration->Mode == "Active"; }
void
RecCreateRecordingJob::setMode(bool b) { d->JobConfiguration->Mode = b ? "Active" : "Idle";  }

#define EXTRA_CONSTRUCT() {}
CLASS_CTORS(trc, Rec, CreateRecordingJobResponse)

const std::string &
RecCreateRecordingJobResponse::getToken() const { return d->JobToken; }
void
RecCreateRecordingJobResponse::setToken (const std::string & str) { d->JobToken = str; }

/////////////////////////////////////////////////////////////////////////////////////
CLASS_CTORS(trc, Rec, DeleteRecordingJob)

const std::string &
RecDeleteRecordingJob::getToken() const { return d->JobToken; }

void
RecDeleteRecordingJob::setToken (const std::string & str) { d->JobToken = str; }

CLASS_CTORS(trc, Rec, DeleteRecordingJobResponse)
/////////////////////////////////////////////////////////////////////////////////////
