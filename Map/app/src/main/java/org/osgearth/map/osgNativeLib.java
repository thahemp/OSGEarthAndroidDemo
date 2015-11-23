package org.osgearth.map;

public class osgNativeLib {
    public static native void 		init(int width, int height);
    public static native void 		step();
    public static native void 		touchBeganEvent(int touchid, float x,float y);
    public static native void 		touchMovedEvent(int touchid, float x,float y);
    public static native void       touchZoomEvent(double delta);
    public static native void 		touchEndedEvent(int touchid, float x,float y, int tapcount);
    public static native void 		clearEventQueue();
    public static native void 		setDataFilePath(String dataPath, String packagePath);
}