#ifndef Credential_h
#define Credential_h

#include "Arduino.h"

class Credential {
  private:
            String _name;
            String _username;
            String _password;
            String _ivUser;
            String _ivPassword;

    public:
            Credential(String name, String username, String password, String ivUser, String ivPassword);
            Credential(String name, String username, String password);
            Credential(String name, String password);
            Credential();

            String getName();
            String getUsername();
            String getPassword();
            String getIVUser();
            String getIVPassword();

            void setName(String name);
            void setUsername(String username);
            void setPassword(String password);
            void setIVUser(String ivUser);
            void setIVPassword(String ivPassword);

};

#endif
