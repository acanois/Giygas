cmake_minimum_required(VERSION 3.31)

set(PROJECT_NAME "Giygas")
set(FORMATS AU Standalone)

file(STRINGS VERSION CURRENT_VERSION)

project(${PROJECT_NAME} VERSION ${CURRENT_VERSION})

set(CMAKE_XCODE_GENERATE_SCHEME OFF)

set(CMAKE_OSX_DEPLOYMENT_TARGET "10.13" CACHE STRING "Support macOS down to High Sierra")

set_property(GLOBAL PROPERTY USE_FOLDERS YES)

option(JUCE_ENABLE_MODULE_SOURCE_GROUPS "Show all module sources in IDE projects" ON)

add_subdirectory(JUCE)

juce_add_plugin("${PROJECT_NAME}"
    # VERSION ...
    # ICON_BIG ...
    # ICON_SMALL ...
    COMPANY_NAME acanois
    BUNDLE_ID com.acanois.acanois
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    # NEEDS_MIDI_OUTPUT TRUE/FALSE
    # IS_MIDI_EFFECT TRUE/FALSE
    # EDITOR_WANTS_KEYBOARD_FOCUS TRUE/FALSE
    COPY_PLUGIN_AFTER_BUILD TRUE
    PLUGIN_MANUFACTURER_CODE Acan
    PLUGIN_CODE P001
    FORMATS "${FORMATS}"
    PRODUCT_NAME "${PROJECT_NAME}"
)

target_compile_features("${PROJECT_NAME}" PRIVATE cxx_std_20)

set(SourceFiles
    Source/GiygasEditor.h
    Source/GiygasProcessor.h
    Source/GiygasEditor.cpp
    Source/GiygasProcessor.cpp
    Source/CustomOscillator.h
    Source/SynthSound.h
    Source/SynthVoice.h
    Source/SynthVoice.cpp
)
target_sources("${PROJECT_NAME}" PRIVATE ${SourceFiles})

set_target_properties("${PROJECT_NAME}" PROPERTIES FOLDER "")

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/Source PREFIX "" FILES ${SourceFiles})

# Setup our binary data as a target
#juce_add_binary_data(Assets SOURCES pamplejuce.png)

# Required for Linux happiness:
# See https://forum.juce.com/t/loading-pytorch-model-using-binarydata/39997/2
#set_target_properties(Assets PROPERTIES POSITION_INDEPENDENT_CODE TRUE)
#set_target_properties(Assets PROPERTIES FOLDER "Targets")

target_compile_definitions("${PROJECT_NAME}"
    PUBLIC
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
    JUCE_VST3_CAN_REPLACE_VST2=0)

target_link_libraries("${PROJECT_NAME}"
    PRIVATE
    #    Assets
    PUBLIC
    juce::juce_audio_utils
    juce::juce_audio_processors
    juce::juce_recommended_config_flags
    juce::juce_recommended_lto_flags
    juce::juce_recommended_warning_flags
    juce::juce_dsp
)

#if(WIN32)
#    find_package(IPP)
#    if(IPP_FOUND)
#        target_link_libraries("${PROJECT_NAME}" PUBLIC IPP::ipps IPP::ippcore IPP::ippi IPP::ippcv)
#        message("IPP LIBRARIES FOUND")
#        target_compile_definitions("${PROJECT_NAME}" PUBLIC PAMPLEJUCE_IPP=1)
#    else()
#        message("IPP LIBRARIES *NOT* FOUND")
#    endif()
#endif()
#
#enable_testing()
#
#file(GLOB_RECURSE TestFiles CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/Tests/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/Tests/*.h")
#source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/Tests PREFIX "" FILES ${TestFiles})

#Include(FetchContent)
#FetchContent_Declare(
#    Catch2
#    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
#    GIT_PROGRESS TRUE
#    GIT_SHALLOW TRUE
#    GIT_TAG v3.3.2)
#FetchContent_MakeAvailable(Catch2)

# Setup the test executable, again C++ 20 please
#add_executable(Tests ${TestFiles})
#target_compile_features(Tests PRIVATE cxx_std_20)

# Our test executable also wants to know about our plugin code...
#target_include_directories(Tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Source)
#target_link_libraries(Tests PRIVATE Catch2::Catch2WithMain "${PROJECT_NAME}")

# We can't link again to the shared juce target without ODL violations
# However, we can steal its include dirs and compile definitions to use in tests!
#target_compile_definitions(Tests INTERFACE $<TARGET_PROPERTY:${PROJECT_NAME},INTERFACE_COMPILE_DEFINITIONS>)
#target_include_directories(Tests INTERFACE $<TARGET_PROPERTY:${PROJECT_NAME},INCLUDE_DIRECTORIES>)

# Make an Xcode Scheme for the test executable so we can run tests in the IDE
#set_target_properties(Tests PROPERTIES XCODE_GENERATE_SCHEME ON)

# Organize the test source in the Tests/ folder in the IDE
#source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/Tests PREFIX "" FILES ${TestFiles})

# Load and use the .cmake file provided by Catch2
# https://github.com/catchorg/Catch2/blob/devel/docs/cmake-integration.md
# We have to manually provide the source directory here for now
#include(${Catch2_SOURCE_DIR}/extras/Catch.cmake)
#catch_discover_tests(Tests)

# Color our warnings and errors
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    add_compile_options (-fdiagnostics-color=always)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    add_compile_options (-fcolor-diagnostics)
endif ()
