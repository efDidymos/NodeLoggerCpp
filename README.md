# NodeLoggerCpp
The command line applications that monitor log files for changes. If the client part detects any changes in monitored files information is sent off via internet connection to the server part that writes data to DB server.

Used technologies: C++ STL QT 5.5 SQL

![alt tag](https://raw.githubusercontent.com/efDidymos/NodeLoggerCpp/master/Deployment%20Model.png)
---
# TODO

!I have to update the usage!

#Usage
  To start server (after compilation from NetBeans):

    ./CLI-version/Server/dist/Debug/<Your_Used_Compiler>/Server <config_file>
    
  or client:
    
    ./CLI-version/Client/dist/Debug/<Your_Used_Compiler>/Client <config_file>
    
##Legend  
  \<Your_Used_Compiler>  - CLang, GNU-Linux, ...
  
  \<config_file> - located in ./Server/config.json or ./Client/config.json


#Instructions for Ubuntu 14.04 LTS 

1. Download Qt framework as tar.gz or .zip package (the latest is 5.5 in the time of writing) and unpack it in home directory as ~/Qt/

2. For ensure connection to MySQL database there is further need to make additional changes.

  2.1. [OPTIONAL] In the Server root directory of project (NodeLoggerCpp/Server/) create soft link to the shared library of the QT database driver:
  
      ln -s ~/Qt/5.5/gcc_64/plugins/sqldrivers/libqsqlmysql.so libqsqlmysql.so

  2.2. Also based on this http://www.qtcentre.org/threads/55365-QSqlDatabase-QMYSQL-driver-not-loaded-but-available?p=264844#post264844 thread the Qt database driver was compiled against an older package libmysqlclient16 (Ubuntu 14.04 LTS contain libmysqlclient18). Therefore download the older package from:
      http://packages.ubuntu.com/

  2.3. After downloading the package install it via command:
      
      sudo dpkg -i <package_name>

  2.4. The last treatment is based on this http://stackoverflow.com/a/34431545 thread.
  
    2.4.1. The solution of problem with secure connecting to database is need to install ssl package via command lin:
      
      sudo apt-get install openssl


    2.4.2. And then create symbolic links because they are missing in distribution packages.
    
      cd /lib/x86_64-linux-gnu
      
      sudo ln -s libssl.so.1.0.0 libssl.so.10
      
      sudo ln -s libcrypto.so.1.0.0 libcrypto.so.10

3. That is all. You are ready to compile and run ;-)

---

##If you receive error in similar manner

    In file included from Thread.cpp:11:
    In file included from /usr/bin/../lib/gcc/x86_64-linux-gnu/5.3.0/../../../../include/c++/5.3.0/thread:35:/usr/bin/../lib/gcc/x86_64-linux-gnu/5.3.0/../../../../include/c++/5.3.0/bits/c++0x_warning.h:32:2: error: This file requires compiler and library support for the ISO C++ 2011 standard. This support is currently experimental, and must be enabled with the -std=c++11 or -std=gnu++11 compiler options.
    error This file requires compiler and library support for the 

You set (in NetBeans) compiler standard to C++14 and additionally you need toenable Qt compilation with new standard.

1. Right click on the project -> Properties -> Build -> Qt -> Expert -> Custom Definitions
2. Then click on three dots
3. Click Add button and type 

    CONFIG += c++14
4. Press OK, OK, OK
