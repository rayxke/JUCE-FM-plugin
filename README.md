# JUCE-FM Plugin
[![](https://github.com/rayxke/JUCE-FM-plugin/actions/workflows/build.yml/badge.svg)](https://github.com/rayxke/JUCE-FM-plugin/actions)
  
## Overview

This is an FM Synthesizer that can be run as a plugin or as a Standalone app. It supports basic aspects of FM Synthesis. 
<div align="center">
<img align="center" src="https://github.com/user-attachments/assets/bba66f2a-84b9-46ba-b879-09f8decf96a0" border-radius="50%" width="800px" height="600px"/>
</div>

## Build

[CMake](https://cmake.org) is required to build. Please download if not already installed.

Clone the repo

```
git clone https://github.com/rayxke/JUCE-FM-plugin
```

Change to project directory

```
cd JUCE-FM-plugin
```

Populate [JUCE](https://juce.com)

```
git submodule update --init
```

Then build with CMake

```
cmake -Bbuild -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```
This will result in a release build in the build directory.

For more detailed instructions please refer to the [JUCE CMake API](https://github.com/juce-framework/JUCE/blob/master/docs/CMake%20API.md)

## Contributing
- Fork the repository
- Make your changes in a separate branch
- Open a pull request

## FM Synthesizer Links

[FM SYNTHS in under 4 minutes](https://www.youtube.com/watch?v=vvBl3YUBUyY)

[Logic Pro Guide to Frequency Modulation](https://support.apple.com/guide/logicpro/frequency-modulation-fm-synthesis-lgsife418213/mac)
