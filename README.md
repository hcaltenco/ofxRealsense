# ofxRealsense

![](./Real_sense.jpg)

Using the librealsense library in the openframeworks platform

Since there is no active addon for librealsense. This is a basic hack to get started with creative coding for the IntelRealSense Camera.

The snippet here uses the depth feed to threshold and create blobs which is then used to track the screen (as seen in the image here )

I've also added an option to send the data via Osc to have control functions in relation to the blob detector. For eg. you can have multiple gesture interactions by connecting the output (via Osc) to wekinator (http://www.wekinator.org/downloads/). 
