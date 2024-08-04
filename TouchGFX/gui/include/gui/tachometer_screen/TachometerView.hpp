#ifndef TACHOMETERVIEW_HPP
#define TACHOMETERVIEW_HPP

#include <gui_generated/tachometer_screen/TachometerViewBase.hpp>
#include <gui/tachometer_screen/TachometerPresenter.hpp>

class TachometerView : public TachometerViewBase
{
public:
    TachometerView();
    virtual ~TachometerView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void handleTickEvent();
protected:
    bool SoCincrease = true;
    bool motorIncrease = true;
    bool rpmIncrease = true;
};

#endif // TACHOMETERVIEW_HPP
