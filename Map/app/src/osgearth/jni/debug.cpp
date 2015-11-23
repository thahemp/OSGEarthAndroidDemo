#include "debug.h"
#include <iostream>

void DebugAndroid::setTag(std::string tag){
    _tag = tag;
}
void DebugAndroid::notify(osg::NotifySeverity severity, const char *message){

    switch ( severity ) {
        case osg::DEBUG_FP:
            __android_log_write(ANDROID_LOG_VERBOSE,_tag.c_str(),message);
          break;
        case osg::DEBUG_INFO:
            __android_log_write(ANDROID_LOG_DEBUG,_tag.c_str(),message);
          break;
        case osg::NOTICE:
        case osg::INFO:
            __android_log_write(ANDROID_LOG_INFO,_tag.c_str(),message);
          break;
        case osg::WARN:
            __android_log_write(ANDROID_LOG_WARN,_tag.c_str(),message);
          break;
        case osg::FATAL:
        case osg::ALWAYS:
            __android_log_write(ANDROID_LOG_ERROR,_tag.c_str(),message);
          break;
        default:
            __android_log_write(ANDROID_LOG_DEBUG,_tag.c_str(),message);
          break;
    }
}
