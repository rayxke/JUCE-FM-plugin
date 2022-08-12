//
//  SpinLockedPosInfo.cpp
//  AudioPluginDemo - All
//
//  Copyright © 2022 JUCE. All rights reserved.
//

#include "SpinLockedPosInfo.h"

SpinLockedPosInfo::SpinLockedPosInfo() { info.resetToDefault(); }

    // Wait-free, but setting new info may fail if the main thread is currently
    // calling `get`. This is unlikely to matter in practice because
    // we'll be calling `set` much more frequently than `get`.
void SpinLockedPosInfo::set (const AudioPlayHead::CurrentPositionInfo& newInfo)
{
    const juce::SpinLock::ScopedTryLockType lock (mutex);

    if (lock.isLocked())
        this->info = newInfo;
}

AudioPlayHead::CurrentPositionInfo SpinLockedPosInfo::get() const noexcept
{
    const juce::SpinLock::ScopedLockType lock (mutex);
    return this->info;
}
