
#include "sigrlog.h"
#include "OnvifSDK.h"
#include "commonTypes.h"
#include "WebDisplayBindingProxy.h"

namespace Web {
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#define EXTRA_CONSTRUCT() \
{\
}

CLASS_CTORS(tls, Disp, GetLayout)

int DispGetLayout::SetLayout(const std::string & str)
{
	this->d->VideoOutput = str;
	return 0;
}

int DispGetLayout::GetLayout(std::string & str) const
{
	str = this->d->VideoOutput;
	return 0;
}

////////////////////////////////////////////////////////////////////////////////
#define EXTRA_CONSTRUCT() \
{\
    if(this->d->Layout == 0) this->d->Layout = soap_new_tt__Layout(this->d->soap);\
}

CLASS_CTORS(tls, Disp, GetLayoutResponse)

int DispGetLayoutResponse::SetLayout(const std::string & str)
{
	tt__PaneLayout * paneLayout = soap_new_tt__PaneLayout(this->d->soap);
	
	paneLayout->Pane = str.c_str();
	paneLayout->Area = soap_new_tt__Rectangle(this->d->soap);
	paneLayout->Area->bottom = new float(0.0f);
	paneLayout->Area->top = new float(0.0f);
	paneLayout->Area->left = new float(1.0f);
	paneLayout->Area->right = new float(1.0f);

	this->d->Layout->PaneLayout.push_back(paneLayout);
	
	return 0;
}

int DispGetLayoutResponse::GetLayout(std::string & str) const
{
	str = this->d->Layout->PaneLayout[0]->Pane;
	return 0;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#define EXTRA_CONSTRUCT() \
{\
}

CLASS_CTORS(tls, Disp, GetDisplayOptions)


int DispGetDisplayOptions::GetVO(std::string & str) const
{
	str = d->VideoOutput;
	return 0;
}


int DispGetDisplayOptions::SetVO(const std::string & str)
{
	d->VideoOutput = str;
	return 0;
}


////////////////////////////////////////////////////////////////////////////////

#define EXTRA_CONSTRUCT() \
{\
    if(this->d->LayoutOptions == 0) this->d->LayoutOptions = soap_new_tt__LayoutOptions(this->d->soap);\
    if(this->d->CodingCapabilities == 0) this->d->CodingCapabilities = soap_new_tt__CodingCapabilities(this->d->soap);\
}

CLASS_CTORS(tls, Disp, GetDisplayOptionsResponse)

inline tt__Rectangle * makeSoapRectangle(soap * s, float bottom, float top, float left, float right) __attribute__((always_inline));

inline tt__Rectangle * makeSoapRectangle(soap * s, float bottom, float top, float left, float right)
{
    float * pbot    = new float(bottom);
    float * ptop    = new float(top);
    float * pleft   = new float(left);
    float * pright  = new float(right);

    return soap_new_set_tt__Rectangle(s, pbot, ptop, pright, pleft);
}

int DispGetDisplayOptionsResponse::Set4FixedLayouts(const float flayout1[1*4], const float flayout4[4*4], const float flayout9[9*4], const float flayout16[16*4])
{
    // bottom = -1.0
    // top = 1.0
    // left = -1.0
    // tight = 1.0

    // panes counted from left to right from top to bottom

    // 1 pane layout
    tt__PaneLayoutOptions * layout1 = soap_new_tt__PaneLayoutOptions(d->soap, -1);

    layout1->Area.push_back(makeSoapRectangle(d->soap, flayout1[0], flayout1[1], flayout1[2], flayout1[3]));

    d->LayoutOptions->PaneLayoutOptions.push_back(layout1);

    // 4 pane layout
    tt__PaneLayoutOptions * layout4 = soap_new_tt__PaneLayoutOptions(d->soap, -1);

    for(int i = 0; i < 4; i++)
    {
        layout4->Area.push_back(makeSoapRectangle(d->soap, flayout4[i*4+0], flayout4[i*4+1], flayout4[i*4+2], flayout4[i*4+3]));
    }

    d->LayoutOptions->PaneLayoutOptions.push_back(layout4);

    // 9 pane layout
    tt__PaneLayoutOptions * layout9 = soap_new_tt__PaneLayoutOptions(d->soap, -1);

    for(int i = 0; i < 9; i++)
    {
        layout9->Area.push_back(makeSoapRectangle(d->soap, flayout9[i*4+0], flayout9[i*4+1], flayout9[i*4+2], flayout9[i*4+3]));
    }

    d->LayoutOptions->PaneLayoutOptions.push_back(layout9);

    // 16 pane layout
    tt__PaneLayoutOptions * layout16 = soap_new_tt__PaneLayoutOptions(d->soap, -1);

    for(int i = 0; i < 16; i++)
    {
        layout16->Area.push_back(makeSoapRectangle(d->soap, flayout16[i*4+0], flayout16[i*4+1], flayout16[i*4+2], flayout16[i*4+3]));
    }

    d->LayoutOptions->PaneLayoutOptions.push_back(layout16);
}

int DispGetDisplayOptionsResponse::GetLayoutOptions(std::vector< std::vector<DispRectangle> > & layoutOptions) const
{
    for(size_t i = 0; i < d->LayoutOptions->PaneLayoutOptions.size(); ++i)
    {
        std::vector<DispRectangle> area;
        for(size_t j = 0; j < d->LayoutOptions->PaneLayoutOptions[i]->Area.size(); j++)
        {
            DispRectangle rect;
            rect.bot = *d->LayoutOptions->PaneLayoutOptions[i]->Area[j]->bottom;
            rect.top = *d->LayoutOptions->PaneLayoutOptions[i]->Area[j]->top;
            rect.left = *d->LayoutOptions->PaneLayoutOptions[i]->Area[j]->left;
            rect.right = *d->LayoutOptions->PaneLayoutOptions[i]->Area[j]->right;
            area.push_back(rect);
        }
        layoutOptions.push_back(area);
    }


    return 0;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#define EXTRA_CONSTRUCT() \
{\
    if(this->d->Layout == 0) this->d->Layout = soap_new_tt__Layout(this->d->soap);\
}

CLASS_CTORS(tls, Disp, SetLayout)

int DispSetLayout::GetVO(std::string & vo)
{
    vo = d->VideoOutput;

    return 0;
}

int DispSetLayout::GetLayout(std::vector<std::pair <std::string, DispRectangle > > & panelayouts)
{
    for(size_t i = 0; i < d->Layout->PaneLayout.size(); ++i)
    {
        std::string token = d->Layout->PaneLayout[i]->Pane;
        DispRectangle rect;
        rect.bot = *d->Layout->PaneLayout[i]->Area->bottom;
        rect.top = *d->Layout->PaneLayout[i]->Area->top;
        rect.left = *d->Layout->PaneLayout[i]->Area->left;
        rect.right = *d->Layout->PaneLayout[i]->Area->right;

        panelayouts.push_back(std::pair<std::string, DispRectangle >(token, rect));
    }

    return 0;
}

int DispSetLayout::SetVO(const std::string & vo)
{
    d->VideoOutput = vo;

    return 0;
}

int DispSetLayout::SetLayout(const std::vector< std::pair<std::string, DispRectangle > > & panelayouts)
{
    std::vector< std::pair<std::string, DispRectangle > >::const_iterator itr;

    for(itr = panelayouts.begin(); itr != panelayouts.end(); ++itr)
    {
        tt__PaneLayout * pl = soap_new_tt__PaneLayout(d->soap, -1);

        pl->Area = makeSoapRectangle(d->soap, (*itr).second.bot, (*itr).second.top, (*itr).second.left, (*itr).second.right);
        pl->Pane = (*itr).first;

        d->Layout->PaneLayout.push_back(pl);
    }

    return 0;
}

////////////////////////////////////////////////////////////////////////////////

#define EXTRA_CONSTRUCT() \
{\
}

CLASS_CTORS(tls, Disp, SetLayoutResponse)

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#define EXTRA_CONSTRUCT() \
{\
}

CLASS_CTORS(tls, Disp, CreatePaneConfiguration)

int DispCreatePaneConfiguration::GetPaneConfig(std::string & videoOutput, std::string & paneToken, std::string & receiverToken) const
{
    videoOutput = d->VideoOutput;
    paneToken = d->PaneConfiguration->Token;
    receiverToken = *d->PaneConfiguration->ReceiverToken;

    return 0;
}

int DispCreatePaneConfiguration::SetPaneConfig(const std::string & videoOutput, const std::string & paneToken, const std::string & receiverToken)
{
    d->PaneConfiguration = soap_new_tt__PaneConfiguration(d->soap, -1);
    d->PaneConfiguration->ReceiverToken = soap_new_std__string(d->soap, -1);

    d->VideoOutput = videoOutput;
    d->PaneConfiguration->Token = paneToken;
    *d->PaneConfiguration->ReceiverToken = receiverToken;

    return 0;
}

////////////////////////////////////////////////////////////////////////////////

#define EXTRA_CONSTRUCT() \
{\
}

CLASS_CTORS(tls, Disp, CreatePaneConfigurationResponse)

int DispCreatePaneConfigurationResponse::SetPaneConfigToken(const std::string & paneConfigToken)
{
    d->PaneToken = paneConfigToken;

    return 0;
}

int DispCreatePaneConfigurationResponse::GetPaneConfigToken(std::string & paneConfigToken) const
{
    paneConfigToken = d->PaneToken;

    return 0;
}
} // namespace Web
