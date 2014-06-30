## Build the UI for the target ##

##Overview##

This article demonstrates the capability of QT framework on Toradex computer modules.

##Automotive Cluster Display Demo##

The instrument cluster is used to display status of the vehicle systems, information and drive conditions. This includes gauges for various parameters, indicators and status lights but also displays and acoustical effects.

##Steps to run the demo##

Please follow this article to setup Qt development environment.

http://developer.toradex.com/how-to/how-to-set-up-qt-creator-to-cross-compile-for-embedded-linux

Download source code from here.

##OpenEmbedded

That example is included on meta-toradex-extra on:

https://github.com/toradex

To add that packege you have to add on local.conf

IMAGE_INSTALL_append = " qt-automotive-cluster-demo "

By default that recipe configure the screen size to 1024x600.

You have also the option to use 800x480, to do it change the file:

vi meta-toradex-extra/recipes-qt/qt-automotive-cluster-demo/qt-automotive-cluster-demo_0.1.bb

--EXTRA_QMAKEVARS_PRE += "CONFIG+=no-webcam DEFINES+=RESOLUTION_1024x600"
++EXTRA_QMAKEVARS_PRE += "CONFIG+=no-webcam"
