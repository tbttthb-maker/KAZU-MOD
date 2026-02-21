ARCHS = arm64
DEBUG = 0
FINALPACKAGE = 1
FOR_RELEASE = 1

TWEAK_NAME = KAZU_PRO

include $(THEOS)/makefiles/common.mk

KAZU_PRO_FILES = Tweak.xm $(wildcard ESP/*.mm) $(wildcard ESP/*.cpp) $(wildcard SDK/*.cpp) $(wildcard imgui/*.mm) $(wildcard imgui/*.cpp) $(wildcard KittyMemory/*.cpp) $(wildcard Dobby/*.cpp)
KAZU_PRO_FRAMEWORKS = IOKit UIKit Foundation Security QuartzCore CoreGraphics CoreText AVFoundation Accelerate GLKit SystemConfiguration GameController
KAZU_PRO_CCFLAGS = -w -std=c+-+-17 -fno-rtti -fno-exceptions -DNDEBUG -Wno-module-import-in-extern-c
KAZU_PRO_CFLAGS = -w -fobjc-arc -Wno-deprecated-declarations -Wno-unused-variable -Wno-unused-value
KAZU_PRO_LDFLAGS = -lstdc+-+-

include $(THEOS_MAKE_PATH)/tweak.mk
