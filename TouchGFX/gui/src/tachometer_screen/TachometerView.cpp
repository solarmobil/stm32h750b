#include <gui/tachometer_screen/TachometerView.hpp>
#include <touchgfx/Color.hpp>
#include <cmath>

uint16_t min;
uint16_t SoCmax;
uint16_t motorMax;
uint16_t rpmMax;
uint16_t speedMax;
uint16_t distanceMax;
uint16_t speedValue;
uint16_t distanceValue;
uint16_t tickCounter;
uint16_t digitalHours;
uint16_t digitalMinutes;
uint16_t digitalSeconds;

TachometerView::TachometerView()
{

}

void TachometerView::setupScreen()
{
    //DigitalClock.setVisible(false);
    TachometerViewBase::setupScreen();

    min = 0;
    SoCmax = 100;
    motorMax = 42;
    rpmMax = 800;
    speedMax = 99;
    distanceMax = 5000;
    speedValue = min;
    distanceValue = min;
    digitalHours = 8;

    Unicode::snprintf(SpeedValBuffer, SPEEDVAL_SIZE, "%d", min);
    Unicode::snprintf(DistanceValBuffer, DISTANCEVAL_SIZE, "%d", min);
}

void TachometerView::tearDownScreen()
{
    TachometerViewBase::tearDownScreen();
}

void TachometerView::handleTickEvent()
{
    uint16_t rpmValue = RpmProgress.getValue();
    if (rpmValue == min)
        rpmIncrease = true;
    else if (rpmValue == rpmMax)
        rpmIncrease = false;
    uint16_t nextRpmValue = rpmIncrease == true ? rpmValue + 5 : rpmValue - 5;
    RpmProgress.setValue(nextRpmValue);
    RpmBar.clearMoveAnimationEndedAction();
    uint16_t progressX = RpmProgress.getProgress() * 4.5;

    if (progressX <= 70)
        RpmBar.startMoveAnimation(progressX - 15, -progressX * 1.1 + 130, 1, touchgfx::EasingEquations::quartEaseOut, touchgfx::EasingEquations::quintEaseIn);
    else
    {
        if (progressX <= 260)
            RpmBar.startMoveAnimation(progressX - 10, 33, 1, touchgfx::EasingEquations::quartEaseOut, touchgfx::EasingEquations::linearEaseNone);
        else
            RpmBar.startMoveAnimation(progressX, 33, 1, touchgfx::EasingEquations::quartEaseOut, touchgfx::EasingEquations::linearEaseNone);
    }
    Unicode::snprintf(RpmValBuffer, RPMVAL_SIZE, "%d", nextRpmValue * 10);
    RpmVal.invalidate();

    uint16_t socValue = SocProgress.getValue();
    if (socValue == min)
        SoCincrease = true;
    else if (socValue == SoCmax)
        SoCincrease = false;
    uint16_t nextSoCValue = SoCincrease == true ? socValue + 1 : socValue - 1;
    SocProgress.setValue(nextSoCValue);
    SocBar.clearMoveAnimationEndedAction();
    SocBar.startMoveAnimation(SocProgress.getProgress() * 4.4, 217, 1, touchgfx::EasingEquations::linearEaseNone, touchgfx::EasingEquations::linearEaseNone);
    Unicode::snprintf(SocValBuffer, SOCVAL_SIZE, "%d", nextSoCValue);
    SocVal.invalidate();

    uint16_t motorValue = MotorProgress.getValue();
    if (motorValue == min)
        motorIncrease = true;
    else if (motorValue == motorMax)
        motorIncrease = false;
    uint16_t nextMotorValue = motorIncrease == true ? motorValue + 1 : motorValue - 1;
    MotorProgress.setValue(nextMotorValue);
    Unicode::snprintf(MotorValBuffer, MOTORVAL_SIZE, "%d", nextMotorValue);
    MotorVal.invalidate();

    tickCounter++;

    if (tickCounter % 60 == 0)
    {
        if (++digitalSeconds >= 60)
        {
            digitalSeconds = 0;
            if (++digitalMinutes >= 60)
            {
                digitalMinutes = 0;
                if (++digitalHours >= 24)
                {
                    digitalHours = 0;
                }
            }
        }

        if (speedValue <= speedMax)
        {
            Unicode::snprintf(SpeedValBuffer, SPEEDVAL_SIZE, "%d", ++speedValue);
            SpeedVal.invalidate();
        }

        if (distanceValue <= distanceMax)
        {
            Unicode::snprintf(DistanceValBuffer, DISTANCEVAL_SIZE, "%d", ++distanceValue);
            DistanceVal.invalidate();
        }

        // Update the clock
        DigitalClock.setTime24Hour(digitalHours, digitalMinutes, digitalSeconds);
        // DigitalClock.setVisible(true);
        // presenter->saveTime(digitalHours, digitalMinutes, digitalSeconds);

    }

    if (tickCounter % 7 == 0)
    {
        OvertakingBackground.setBorderColor(touchgfx::Color::getColorFromRGB(0, 255, 0));
        OvertakingBackground.invalidate();
    }
    else if (tickCounter % 12 == 0)
    {
        OvertakingBackground.setBorderColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
        OvertakingBackground.invalidate();
    }
}