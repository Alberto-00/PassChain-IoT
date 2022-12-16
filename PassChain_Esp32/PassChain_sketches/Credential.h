#ifndef Credential_h
#define Credential_h

#include "Arduino.h"

class Credential {
  private:
            String _name;
            String _username;
            String _password;

    public:
            Credential(String name, String username, String password);
            Credential(String name, String password);
            Credential();

            String getName();
            String getUsername();
            String getPassword();

            void setName(String name);
            void setUsername(String username);
            void setPassword(String password);
};

#endif
