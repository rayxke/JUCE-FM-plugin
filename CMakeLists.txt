cmake_minimum_required(VERSION 3.22)

project(JUCE-FM-plugin VERSION 0.0.1)

set(PRODUCT_NAME "JUCE-FM-plugin")

add_subdirectory(JUCE)

juce_add_plugin(JUCE-FM-plugin VERSION 0.1.0
    IS_SYNTH TRUE
    IS_MIDI_EFFECT FALSE
    PLUGIN_MANUFACTURER_CODE Rayx
    PLUGIN_CODE Jufm
    FORMATS AU VST3 Standalone
    PRODUCT_NAME "JUCE-FM-plugin")

juce_generate_juce_header(JUCE-FM-plugin)

file(GLOB_RECURSE SourceFiles CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/Source/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Source/*.h")

target_sources(JUCE-FM-plugin
    PRIVATE
        ${SourceFiles})

target_include_directories(JUCE-FM-plugin
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/Source")

target_compile_definitions(JUCE-FM-plugin
    PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0)

target_link_libraries(JUCE-FM-plugin
    PRIVATE
        juce::juce_audio_utils
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)

if ((DEFINED ENV{CI}))
    set (env_file "${PROJECT_SOURCE_DIR}/.env")
    message ("Writing ENV file for CI: ${env_file}")

    file(WRITE  "${env_file}" "PROJECT_NAME=${PROJECT_NAME}\n")
    file(APPEND "${env_file}" "PRODUCT_NAME=${PRODUCT_NAME}\n")
    file(APPEND "${env_file}" "VERSION=${CURRENT_VERSION}\n")
    file(APPEND "${env_file}" "BUNDLE_ID=${BUNDLE_ID}\n")
    file(APPEND "${env_file}" "COMPANY_NAME=${COMPANY_NAME}\n")
endif ()
