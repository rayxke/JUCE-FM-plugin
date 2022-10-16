# JUCE-FM Plugin
  
This is an FM Synthesizer that can be run as a plugin or as a Standalone app. It supports basic aspects of FM Synthesis.   
    
## Installation
### Mac OS
Step 1: Installations

- Install [JUCE](https://juce.com) from source
- Install [XCode](https://developer.apple.com/xcode/)

Step 2: Clone The Repo
```
git clone https://github.com/rayxke/JUCE-FM-plugin
```


Step 3: Using the Projucer open the "FM Plugin.jucer" file.


Step 4: Click the export button in the [Projucer](https://juce.com/discover/projucer)

Step 5: Click the build button in XCode

Step 6: Find the build file
- Find build file in this subdirectory within your project folder:
```
cd JUCE\ Projects/JUCE-FM-plugin/Builds/MacOSX/build/Debug/
```
- The file should be named "FM Plugin.component" (AU Format for DAWS)
- "FM Plugin.app" is the standalone version of the app

Step 7: Copy this file into:
```
/Library/Audio/Plug-Ins/Components
```
Step 8: Open Logic or garage band. (Restart if already open)
- Check available plugins for "3rd party" plugins. Open this for testing of plugin.

[Walk thru link](https://producersociety.com/plug-ins-garageband/) for step 8 

### Windows

Step 1: Installations

- Install [JUCE](https://juce.com) from source
- Install Visual Studio (Not Visual Studio Code!)

Step 2: Download Code

```
git clone https://github.com/rayxke/JUCE-FM-plugin
```

Step 3: Creating Project

- Open Visual Studio
- continue without code --> file --> new --> project from existing code
- Select the folder in which your code is located in
- Build or press the green play arrow (this should throw an error at first, but we need to have a build file)

Step 4: Open in JUCE

- Open JUCE
- Click "Open"
- Select a file from your project folder
- Set "Selected exporter" to Visual Studio 
- Click the Visual Studio icon

Step 5: Run code

- Click the green play arrow

### Linux

TBD


## FM Synthesizer Links

[FM SYNTHS in under 4 minutes](https://www.youtube.com/watch?v=vvBl3YUBUyY)

[Logic Pro Guide to Frequency Modulation](https://support.apple.com/guide/logicpro/frequency-modulation-fm-synthesis-lgsife418213/mac)
