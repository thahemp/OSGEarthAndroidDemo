#ifndef DEBUG_H_
#define DEBUG_H_

#include <android/log.h>

#include <osg/Notify>

#include <string>

class OSG_EXPORT DebugAndroid : public osg::NotifyHandler
{
private:
    std::string _tag;
public:
    void setTag(std::string tag);
    void notify(osg::NotifySeverity severity, const char *message);
};

#endif /* DEBUG_H_ */
