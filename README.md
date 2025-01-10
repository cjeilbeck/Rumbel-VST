# Rumbel-VST

# Rumbel Audio Plugin

Rumbel is an open-source audio plugin offering customizable distortion effects with a minimalist interface, prioritizing ease of workflow and an emphasis on mixing by ear.


## Getting Started

### Prerequisites
To build and use this project, you’ll need:
- [JUCE Framework](https://juce.com/)
- An IDE (e.g., Visual Studio 2022 for Windows or Xcode for macOS)
- C++17 or later.

### Folder Structure
- **Source/**: Contains the plugin source code (`PluginProcessor.cpp`, `PluginProcessor.h`, `PluginEditor.cpp`, `PluginEditor.h`).
- **Resources/**: Contains the image files used for the plugin's UI (e.g., `Sagebrush.png`, `RIVERORANGE.png`, `flatbackground.png`).

### Building the Plugin
1. Clone this repository:
   ```bash
   git clone https://github.com/cjeilbeck/Rumbel-Audio-Plugin.git
Install JUCE.
Open the Rumbel.jucer file in Projucer.
In Projucer:
Add the files in the Resources/ folder (flatbackground.png, Sagebrush.png, RIVERORANGE.png) to the project.
Ensure the "Add to Binary Resources" checkbox is selected for these files.
Generate project files for your IDE (e.g., Visual Studio, Xcode).
Open the project in your IDE and build the plugin in Release mode.

### Installing the Plugin

Locate the compiled .vst3 file in the Builds folder (e.g., Builds/VisualStudio2022/x64/Release/VST3/).
Copy the .vst3 file to your DAW's plugin directory:
Windows: C:\Program Files\Common Files\VST3\
macOS: /Library/Audio/Plug-Ins/VST3/
Open your DAW, rescan plugins, and load Rumbel.

### Contributing

Contributions are welcome! 

License
This project is licensed under the MIT License. See the LICENSE file for details.
