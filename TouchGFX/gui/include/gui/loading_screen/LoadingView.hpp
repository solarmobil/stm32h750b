#ifndef LOADINGVIEW_HPP
#define LOADINGVIEW_HPP

#include <gui_generated/loading_screen/LoadingViewBase.hpp>
#include <gui/loading_screen/LoadingPresenter.hpp>

class LoadingView : public LoadingViewBase
{
public:
    LoadingView();
    virtual ~LoadingView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // LOADINGVIEW_HPP
