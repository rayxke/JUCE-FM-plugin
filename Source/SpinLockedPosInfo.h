//
//  SpinLockedPosInfo.hpp
//  AudioPluginDemo - All
//
//  Copyright © 2022 JUCE. All rights reserved.
//

#pragma once

#include <JuceHeader.h>

class SpinLockedPosInfo
{
public:
    SpinLockedPosInfo();
    void set (const AudioPlayHead::CurrentPositionInfo& newInfo);
    AudioPlayHead::CurrentPositionInfo get() const noexcept;

private:
    juce::SpinLock mutex;
    AudioPlayHead::CurrentPositionInfo info;
};
