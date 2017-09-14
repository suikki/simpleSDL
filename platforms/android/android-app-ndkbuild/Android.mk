LOCAL_PATH := $(call my-dir)

#
# Path to a the directory containing SDL sources
#
EXTERNAL_LIB_PATH := ../../../contrib

#
# Build app using SDL
#

include $(CLEAR_VARS)
LOCAL_MODULE := libSimpleExample


# Includes
LOCAL_C_INCLUDES +=  \
  $(LOCAL_PATH)/$(EXTERNAL_LIB_PATH)/SDL/include \
  $(LOCAL_PATH)/$(EXTERNAL_LIB_PATH)/SDL_image \
  $(LOCAL_PATH)/../../../source


# Source files
LOCAL_SRC_FILES :=  \
  $(LOCAL_PATH)/../../../source/main.c

  
# Linking options
LOCAL_SHARED_LIBRARIES := SDL2
#LOCAL_SHARED_LIBRARIES := SDL2 SDL2_image
#LOCAL_STATIC_LIBRARIES := SDL2main
LOCAL_LDLIBS := -lz -llog -landroid -lGLESv1_CM -lGLESv2


# Build app as a shared library
include $(BUILD_SHARED_LIBRARY)


#
# External modules.
#
$(call import-add-path,$(EXTERNAL_LIB_PATH))
$(call import-module,SDL)
#$(call import-module,SDL_image)
