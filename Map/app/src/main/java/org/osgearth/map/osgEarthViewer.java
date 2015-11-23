package org.osgearth.map;

import android.app.Activity;
import android.content.Context;
import android.os.Bundle;
import android.view.Window;
import android.view.WindowManager;
import android.util.Log;


public class osgEarthViewer extends Activity {
	
	private static final String TAG = "OSG Activity";
    EGLview mView;

    //Main Android Activity life cycle
    @Override protected void onCreate(Bundle icicle) {
    	
    	//load our native lib
        System.loadLibrary("osgNativeLib");

        super.onCreate(icicle);
        
        //set window style
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);

        //set the data dirs string for android platform
        Context context = getApplicationContext(); // or other way of getting current context
        String dir = context.getFilesDir().getPath();
        String packageDir = context.getPackageResourcePath();
        osgNativeLib.setDataFilePath(dir, packageDir);
        
        // Create our GLSurfaceview EGLView which calls our native libs init and frame/update functions  
        mView = new EGLview(this);
        setContentView(mView);
    }

    @Override
    protected void onPause() {
        super.onPause();
        mView.onPause();
    }
    @Override protected void onResume() {
        super.onResume();
        mView.onResume();
    }
}