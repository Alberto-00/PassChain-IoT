#include "Credential.h"
#include "Arduino.h"

Credential::Credential(String name, String username, String password, String ivUser, String ivPassword){
  this->_name = name;
  this->_username = username;
  this->_password = password;
  this->_ivUser = ivUser;
  this->_ivPassword = ivPassword;
};

Credential::Credential(String name, String username, String password){
  this->_name = name;
  this->_username = username;
  this->_password = password;
};

Credential::Credential(String name, String password){
  this->_name = name;
  this->_password = password;
};

Credential::Credential(){

};

String Credential::getName(){
  return this->_name;
}

String Credential::getUsername(){
  return this->_username;
}

String Credential::getPassword(){
  return this->_password;
}

String Credential::getIVUser(){
  return this->_ivUser;
}

String Credential::getIVPassword(){
  return this->_ivPassword;
}

void Credential::setName(String name){
 this->_name = name;
}

void Credential::setUsername(String username){
  this->_username = username;
}

void Credential::setPassword(String password){
  this->_password = password;
}

void Credential::setIVUser(String ivUser){
  this->_ivUser = ivUser;
}

void Credential::setIVPassword(String ivPassword){
  this->_ivPassword = ivPassword;
}
