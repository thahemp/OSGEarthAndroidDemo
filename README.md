# OSGEarthAndroidDemo

1) Edit OSGEarthAndroidDemo/Map/app/src/osgearth/jni/build_for_project.sh and set the BASE_PATH variable to the proper location.

2) Edit OSGEarthAndroidDemo/Map/app/src/osgearth/jni/Android.mk paths (NDK_ROOT, OSG_ANDROID_DIR, OSGEARTH_ANDROID_DIR, THIRDPARTY_ANDROID_DIR) to point to the proper locations.

3) Run the "build_for_project.sh" script to build the native library code. This script will copy the generated library files to the appropriate Android Studio folder.

4) Open the project in Android Studio and run the example.
