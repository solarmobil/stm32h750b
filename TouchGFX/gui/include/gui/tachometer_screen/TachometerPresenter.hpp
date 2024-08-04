#ifndef TACHOMETERPRESENTER_HPP
#define TACHOMETERPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class TachometerView;

class TachometerPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    TachometerPresenter(TachometerView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~TachometerPresenter() {}

private:
    TachometerPresenter();

    TachometerView& view;
};

#endif // TACHOMETERPRESENTER_HPP
