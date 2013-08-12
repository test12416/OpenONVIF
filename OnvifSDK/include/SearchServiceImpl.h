#ifndef SearchServiceImpl_H
#define SearchServiceImpl_H

#include "WebSearchBindingService.h"
class BaseServer;
namespace Web {
class SearchServiceImpl : public SearchBindingService
{
private:
    BaseServer * m_pBaseServer;
public:
    SearchServiceImpl(BaseServer * pBaseServer, struct soap * pData):
        m_pBaseServer(pBaseServer),
        SearchBindingService(pData)
    {
    }

    virtual	SearchBindingService *copy() { return SOAP_OK; }

    /// Web service operation 'GetServiceCapabilities' (returns error code or SOAP_OK)
    virtual	int GetServiceCapabilities(_tse__GetServiceCapabilities *tse__GetServiceCapabilities, _tse__GetServiceCapabilitiesResponse *tse__GetServiceCapabilitiesResponse) { return SOAP_OK; }

    /// Web service operation 'GetRecordingSummary' (returns error code or SOAP_OK)
    virtual	int GetRecordingSummary(_tse__GetRecordingSummary *tse__GetRecordingSummary, _tse__GetRecordingSummaryResponse *tse__GetRecordingSummaryResponse) { return SOAP_OK; }

    /// Web service operation 'GetRecordingInformation' (returns error code or SOAP_OK)
    virtual	int GetRecordingInformation(_tse__GetRecordingInformation *tse__GetRecordingInformation, _tse__GetRecordingInformationResponse *tse__GetRecordingInformationResponse) { return SOAP_OK; }

    /// Web service operation 'GetMediaAttributes' (returns error code or SOAP_OK)
    virtual	int GetMediaAttributes(_tse__GetMediaAttributes *tse__GetMediaAttributes, _tse__GetMediaAttributesResponse *tse__GetMediaAttributesResponse) { return SOAP_OK; }

    /// Web service operation 'FindRecordings' (returns error code or SOAP_OK)
    virtual	int FindRecordings(_tse__FindRecordings *tse__FindRecordings, _tse__FindRecordingsResponse *tse__FindRecordingsResponse) { return SOAP_OK; }

    /// Web service operation 'GetRecordingSearchResults' (returns error code or SOAP_OK)
    virtual	int GetRecordingSearchResults(_tse__GetRecordingSearchResults *tse__GetRecordingSearchResults, _tse__GetRecordingSearchResultsResponse *tse__GetRecordingSearchResultsResponse) { return SOAP_OK; }

    /// Web service operation 'FindEvents' (returns error code or SOAP_OK)
    virtual	int FindEvents(_tse__FindEvents *tse__FindEvents, _tse__FindEventsResponse *tse__FindEventsResponse) { return SOAP_OK; }

    /// Web service operation 'GetEventSearchResults' (returns error code or SOAP_OK)
    virtual	int GetEventSearchResults(_tse__GetEventSearchResults *tse__GetEventSearchResults, _tse__GetEventSearchResultsResponse *tse__GetEventSearchResultsResponse) { return SOAP_OK; }

    /// Web service operation 'FindPTZPosition' (returns error code or SOAP_OK)
    virtual	int FindPTZPosition(_tse__FindPTZPosition *tse__FindPTZPosition, _tse__FindPTZPositionResponse *tse__FindPTZPositionResponse) { return SOAP_OK; }

    /// Web service operation 'GetPTZPositionSearchResults' (returns error code or SOAP_OK)
    virtual	int GetPTZPositionSearchResults(_tse__GetPTZPositionSearchResults *tse__GetPTZPositionSearchResults, _tse__GetPTZPositionSearchResultsResponse *tse__GetPTZPositionSearchResultsResponse) { return SOAP_OK; }

    /// Web service operation 'GetSearchState' (returns error code or SOAP_OK)
    virtual	int GetSearchState(_tse__GetSearchState *tse__GetSearchState, _tse__GetSearchStateResponse *tse__GetSearchStateResponse) { return SOAP_OK; }

    /// Web service operation 'EndSearch' (returns error code or SOAP_OK)
    virtual	int EndSearch(_tse__EndSearch *tse__EndSearch, _tse__EndSearchResponse *tse__EndSearchResponse) { return SOAP_OK; }

    /// Web service operation 'FindMetadata' (returns error code or SOAP_OK)
    virtual	int FindMetadata(_tse__FindMetadata *tse__FindMetadata, _tse__FindMetadataResponse *tse__FindMetadataResponse) { return SOAP_OK; }

    /// Web service operation 'GetMetadataSearchResults' (returns error code or SOAP_OK)
    virtual	int GetMetadataSearchResults(_tse__GetMetadataSearchResults *tse__GetMetadataSearchResults, _tse__GetMetadataSearchResultsResponse *tse__GetMetadataSearchResultsResponse) { return SOAP_OK; }
};
} // namespace Web
#endif // SearchServiceImpl
