# NodeLoggerCpp
Application for transferring information from a logs to server. The logs are watched for any changes.

Used technologies: C++ STL QT 5.5

---

#Instructions for Ubuntu 14.04 LTS 

1. Download Qt framework as tar.gz or .zip package (the latest is 5.5 in the time of writing) and unpack it in home directory as ~/Qt/

2. For ensure connection to MySQL database there is further need to make additional changes.

  2.1. [OPTIONAL] In the Server root directory of project (NodeLoggerCpp/Server/) create soft link to the shared library of the QT database driver:
      `ln -s ~/Qt/5.5/gcc_64/plugins/sqldrivers/libqsqlmysql.so libqsqlmysql.so`

  2.2. Also based on this http://www.qtcentre.org/threads/55365-QSqlDatabase-QMYSQL-driver-not-loaded-but-available?p=264844#post264844 thread the Qt database driver was compiled against an older package libmysqlclient16 (Ubuntu 14.04 LTS contain libmysqlclient18). Therefore download the older package from:
      http://packages.ubuntu.com/

  2.3. After downloading the package install it via command:
      `sudo dpkg -i <package_name>`

  2.4. The last treatment is based on this http://stackoverflow.com/a/34431545 thread.
  
    2.4.1. The solution of problem with secure connecting to database is need to install ssl package via command lin:
      `sudo apt-get install openssl`


    2.4.2. And then create symbolic links because they are missing in distribution packages.
    
      cd /lib/x86_64-linux-gnu
      
      sudo ln -s libssl.so.1.0.0 libssl.so.10
      
      sudo ln -s libcrypto.so.1.0.0 libcrypto.so.10

3. That is all. You are ready to compile and run ;-)
