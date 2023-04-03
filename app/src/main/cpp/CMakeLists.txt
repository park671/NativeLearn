
# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.22.1)

# Declares and names the project.

set(ANDROID_STL "none")
enable_language(ASM)
set(CMAKE_ASM_SOURCE_FILE_EXTENSIONS s)

project("native_learn")

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.
#add_library(native_add SHARED )

add_library( # Sets the name of the library.
             native_learn

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             native_learn.cpp
             native_add.s)

add_library(native_gl SHARED native_gl.cpp)
add_library(empty STATIC empty.cpp)
add_library(native_activity SHARED native_activity_impl.cpp native_gl.cpp)
add_library(native_app_glue STATIC android_app_glue/android_native_app_glue.c)
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -u ANativeActivity_onCreate")

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
                       native_learn

                       # Links the target library to the log library
                       # included in the NDK.
        )

target_link_libraries( # Specifies the target library.
        native_gl

        # Links the target library to the log library
        # included in the NDK.
        ${log-lib}
        GLESv2)


target_link_libraries(
        native_activity
        # Links the target library to the log library
        # included in the NDK.
        log android EGL GLESv2 native_app_glue)
