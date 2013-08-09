#include "wsa.hpp"
//#include <wsaapi.h>

namespace {

/** Anonymous Reply/To endpoint address */
static const std::string ANONYMOUS_URI = "http://schemas.xmlsoap.org/ws/2004/08/addressing/role/anonymous";
/** Specifies no Reply endpoint address (no reply) */
static const std::string NONE_URI = "addressing/none not supported";
static const std::string FAULT_ACTION = "http://schemas.xmlsoap.org/ws/2004/08/addressing/fault";

int wsaError(soap * s, wsa__FaultSubcodeValues fault)
{
    const char * code = soap_wsa__FaultSubcodeValues2s(s, fault);
    switch (fault) {
    case wsa__FaultSubcodeValues__wsa__InvalidMessageInformationHeader:
        return soap_sender_fault_subcode(s, code, "A message information header is not valid and the message cannot be processed. The validity failure can be either structural or semantic, e.g. a [destination] that is not a URI or a [relationship] to a [message id] that was never issued.", "Invalid header");
    case wsa__FaultSubcodeValues__wsa__MessageInformationHeaderRequired:
        return soap_sender_fault_subcode(s, code, "A required message information header, To, MessageID, or Action, is not present.", "Missing Header QName");
    case wsa__FaultSubcodeValues__wsa__DestinationUnreachable:
        return soap_sender_fault_subcode(s, code, "No route can be determined to reach the destination role defined by the WS-Addressing To.", NULL);
    case wsa__FaultSubcodeValues__wsa__ActionNotSupported:
        return soap_sender_fault_subcode(s, code, "The [action] cannot be processed at the receiver.", s->action);
    case wsa__FaultSubcodeValues__wsa__EndpointUnavailable:
        return soap_sender_fault(s, code, "The endpoint is unable to process the message at this time.");
    default:
        break;
    }

    return SOAP_FAULT;
}

} // anonymous namespace


Wsa::Wsa(struct soap * soap) :
    soap_(soap)
{
    sequence_.soap_default(soap);
}

Wsa::~Wsa()
{
    soap_destroy(soap_);
    soap_end(soap_);
}

uint & Wsa::instanceId()
{
    static uint rv = time(nullptr);
    return rv;
}

std::string & Wsa::sequenceId()
{
    static std::string  rv;
    return rv;
}

uint & Wsa::messageNumber()
{
    static uint rv = 0;
    ++rv;
    return rv;
}

std::string Wsa::randUuid()
{
    char rv[48];
    int r1, r2, r3, r4;
#ifdef WITH_OPENSSL
    r1 = soap_random;
    r2 = soap_random;
#else
    static int k = 0xFACEB00B;
    int lo = k % 127773;
    int hi = k / 127773;
# ifdef HAVE_GETTIMEOFDAY
    struct timeval tv;
    gettimeofday(&tv, NULL);
    r1 = 10000000 * tv.tv_sec + tv.tv_usec;
#else
    r1 = (int)time(NULL);
# endif
    k = 16807 * lo - 2836 * hi;
    if (k <= 0)
        k += 0x7FFFFFFF;
    r2 = k;
    k &= 0x8FFFFFFF;
    r2 += *(int*)soap_->buf;
#endif
    r3 = soap_random;
    r4 = soap_random;
    std::sprintf(rv, "uuid:%8.8x-%4.4hx-4%3.3hx-%4.4hx-%4.4hx%8.8x",
            r1, (short)(r2 >> 16), (short)r2 >> 4,
            ((short)(r3 >> 16) & 0x3FFF) | 0x8000, (short)r3, r4);

    return rv;
}

int Wsa::allocHeader()
{
    soap_header(soap_);
    if (soap_->header != nullptr)
        return SOAP_OK;

    return (soap_->error = SOAP_EOM);
}

int Wsa::check() const
{
    if (soap_->header == nullptr || soap_->header->SOAP_WSA(Action).empty())
        return wsaError(soap_, wsa__FaultSubcodeValues__wsa__MessageInformationHeaderRequired);

    return SOAP_OK;
}

int Wsa::addFrom(const std::string & from)
{
    if (soap_->header == nullptr)
        return SOAP_ERR;

    soap_->header->SOAP_WSA(From) = new wsa__EndpointReferenceType;
    soap_->header->SOAP_WSA(From)->soap_default(soap_);
    soap_->header->SOAP_WSA(From)->Address->__item = from;
    return SOAP_OK;
}

int Wsa::addNoReply()
{
    return addReplyTo(NONE_URI);
}

int Wsa::addReplyTo(const std::string & replyTo)
{
    if (soap_->header == nullptr)
        return SOAP_ERR;

    if (!replyTo.empty()) {
        soap_->header->SOAP_WSA(ReplyTo) = new wsa__EndpointReferenceType;
        soap_->header->SOAP_WSA(ReplyTo)->soap_default(soap_);
        soap_->header->SOAP_WSA(ReplyTo)->Address->__item = replyTo;
    }

    return SOAP_OK;
}

int Wsa::addFaultTo(const std::string & faultTo)
{
    if (soap_->header == nullptr)
        return SOAP_ERR;

    if (!faultTo.empty()) {
        soap_->header->SOAP_WSA(FaultTo) = new wsa__EndpointReferenceType;
        soap_->header->SOAP_WSA(FaultTo)->soap_default(soap_);
        soap_->header->SOAP_WSA(FaultTo)->Address->__item = faultTo;
    }

    return SOAP_OK;
}

int Wsa::addRelatesTo(const std::string & relatesTo)
{
    if (soap_->header == nullptr)
        return SOAP_ERR;

    if (!relatesTo.empty()) {
        soap_->header->SOAP_WSA(RelatesTo) = new wsa__Relationship;
        soap_->header->SOAP_WSA(RelatesTo)->soap_default(soap_);
        soap_->header->SOAP_WSA(RelatesTo)->__item = relatesTo;
    }

    return SOAP_OK;
}

int Wsa::addAppSequence(std::string * id)
{
    sequence_.SequenceId = id;
    sequence_.InstanceId = instanceId();
    sequence_.MessageNumber = messageNumber();
    soap_->header->wsd__AppSequence = &sequence_;
}


int Wsa::reply(const std::string & id, const std::string & action)
{
//    struct SOAP_ENV__Header * oldheader = soap_->header;
//    soap_->header = nullptr;

//    /* if endpoint address for reply is 'none' return immediately */
//    if (oldheader != nullptr && oldheader->SOAP_WSA(ReplyTo) && oldheader->SOAP_WSA(ReplyTo)->Address
//            && !strcmp(oldheader->SOAP_WSA(ReplyTo)->Address, NONE_URI))
//    {
//        return soap_send_empty_response(soap_, SOAP_OK);
//    }

//    /* allocate a new header */
//    if (alloHeader() != 0)
//        return soap_->error;

//    struct SOAP_ENV__Header * newheader = soap_->header;
//    if (oldheader != nullptr)
//        *newheader = *oldheader;

//    newheader->SOAP_WSA(MessageID) = id;
//    newheader->SOAP_WSA(Action) = action;
//    newheader->SOAP_WSA(RelatesTo) = nullptr;
//    newheader->SOAP_WSA(From) = nullptr;
//    newheader->SOAP_WSA(To) = nullptr;
//    newheader->SOAP_WSA(ReplyTo) = nullptr;
//    newheader->SOAP_WSA(FaultTo) = nullptr;


//    if (oldheader && oldheader->SOAP_WSA(MessageID)) {
//        newheader->SOAP_WSA(RelatesTo) = (SOAP_WSA_(,RelatesTo)*)soap_malloc(soap, sizeof(SOAP_WSA_(,RelatesTo)));
//        SOAP_WSA_(soap_default_,RelatesTo)(soap, newheader->SOAP_WSA(RelatesTo));
//        newheader->SOAP_WSA(RelatesTo)->__item = oldheader->SOAP_WSA(MessageID);
//    }

//    if (oldheader && oldheader->SOAP_WSA(ReplyTo) && oldheader->SOAP_WSA(ReplyTo)->Address && strcmp(oldheader->SOAP_WSA(ReplyTo)->Address, soap_wsa_anonymousURI)) {
//        newheader->SOAP_WSA(To) = oldheader->SOAP_WSA(ReplyTo)->Address;
//        /* (re)connect to ReplyTo endpoint if From != ReplyTo */
//        if (!oldheader->SOAP_WSA(From) || !oldheader->SOAP_WSA(From)->Address || strcmp(oldheader->SOAP_WSA(From)->Address, oldheader->SOAP_WSA(ReplyTo)->Address)) {
//            struct soap *reply_soap = soap_copy(soap);
//            if (reply_soap) {
//                soap_copy_stream(reply_soap, soap);
//                soap_clr_omode(reply_soap, SOAP_ENC_MIME | SOAP_ENC_DIME | SOAP_ENC_MTOM);
//                soap_free_stream(soap); /* prevents close in soap_connect() below */
//                newheader->SOAP_WSA(FaultTo) = oldheader->SOAP_WSA(FaultTo);
//                soap->header = newheader;
//                if (soap_connect(soap, newheader->SOAP_WSA(To), newheader->SOAP_WSA(Action))) {
//                    int err;
//                    soap_copy_stream(soap, reply_soap);
//#if defined(SOAP_WSA_2005)
//                    err = soap_wsa_error(soap, SOAP_WSA(DestinationUnreachable), newheader->SOAP_WSA(To));
//#elif defined(SOAP_WSA_2003)
//                    err = soap_wsa_error(soap, "WS-Addessing destination unreachable");
//#else
//                    err = soap_wsa_error(soap, SOAP_WSA(DestinationUnreachable));
//#endif
//                    soap_free_stream(reply_soap);
//                    soap_end(reply_soap);
//                    soap_free(reply_soap);
//                    soap->header = NULL;
//                    return err;
//                }
//                if (soap_valid_socket(reply_soap->socket)) {
//                    soap_send_empty_response(reply_soap, SOAP_OK);	/* HTTP ACCEPTED */
//                    soap_closesock(reply_soap);
//                }
//                soap_free_stream(reply_soap);
//                soap_end(reply_soap);
//                soap_free(reply_soap);
//                data->fresponse = soap->fresponse;
//                soap->fresponse = soap_wsa_response;	/* response will be a POST */
//            }
//        }
//    } else if (oldheader && oldheader->SOAP_WSA(From))
//        newheader->SOAP_WSA(To) = oldheader->SOAP_WSA(From)->Address;
//    else
//        newheader->SOAP_WSA(To) = (char*)soap_wsa_anonymousURI;

//    soap->header = newheader;
//    soap->action = newheader->SOAP_WSA(Action);

    return SOAP_OK;
}


int Wsa::request(const std::string & to, const std::string & action)
{
    if (allocHeader() != 0)
        return soap_->error;
    soap_->header->SOAP_WSA(MessageID) = randUuid();
    soap_->header->SOAP_WSA(To) = to.empty() ? ANONYMOUS_URI : to;
    soap_->header->SOAP_WSA(Action) = action;
    soap_->header->SOAP_WSA(RelatesTo) = nullptr;
    soap_->header->SOAP_WSA(From) = nullptr;
    soap_->header->SOAP_WSA(ReplyTo) = nullptr;
    soap_->header->SOAP_WSA(FaultTo) = nullptr;
    return check();
}

