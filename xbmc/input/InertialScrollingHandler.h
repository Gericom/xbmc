/*
 *  Copyright (C) 2011-2018 Team Kodi
 *  This file is part of Kodi - https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include <deque>

#include "utils/Geometry.h"
#include "utils/Vector.h"

class CApplication;
class CAction;

class CInertialScrollingHandler
{
  friend class CApplication;
  public:
    CInertialScrollingHandler();

    bool IsScrolling(){return m_bScrolling;}

  private:
    bool CheckForInertialScrolling(const CAction* action);
    bool ProcessInertialScroll(float frameTime);

    //-------------------------------------------vars for inertial scrolling animation with gestures
    bool          m_bScrolling = false;        //flag indicating that we currently do the inertial scrolling emulation
    bool          m_bAborting = false;         //flag indicating an abort of scrolling
    CVector       m_iFlickVelocity;

    struct PanPoint
    {
      unsigned int time;
      CVector velocity;
      PanPoint(unsigned int time, CVector velocity)
        : time(time), velocity(velocity) {}
      unsigned int TimeElapsed() const;
    };
    std::deque<PanPoint> m_panPoints;
    CPoint        m_iLastGesturePoint;
    CVector       m_inertialDeacceleration;
    unsigned int  m_inertialStartTime = 0;
};
