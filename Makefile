# Target Architecture for iOS
ARCHS = arm64 arm64e
DEBUG = 0
FINALPACKAGE = 1
FOR_RELEASE = 1

# Project Name
TWEAK_NAME = KAZU_PRO

include $(THEOS)/makefiles/common.mk

# Automatically find all source files in the root directory
KAZU_PRO_FILES = PubgLoad.mm metalbiew.mm Tools.cpp $(wildcard *.mm) $(wildcard *.cpp)

# Required Frameworks for Metal and ESP
KAZU_PRO_FRAMEWORKS = UIKit Foundation Security QuartzCore CoreGraphics CoreText AVFoundation Metal MetalKit IOKit Accelerate

# Compiler Flags for C++17 and Performance
KAZU_PRO_CCFLAGS = -w -std=c++17 -fno-rtti -fno-exceptions -DNDEBUG -Wno-module-import-in-extern-c
KAZU_PRO_CFLAGS = -w -fobjc-arc -Wno-deprecated-declarations -Wno-unused-variable -Wno-unused-value
KAZU_PRO_LDFLAGS = -lstdc++

include $(THEOS_MAKE_PATH)/tweak.mk
