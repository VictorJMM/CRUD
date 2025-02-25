#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <filesystem>

struct User {
    std::string name;
    std::string passwd;
    double saldo;
    int id;
    bool IsADM;
    bool logado;
};

extern std::vector<User> users;

void create();
void listUsers();
void login();
void DeletUser();
void Menu();
void Save();
void SaveUser(const std::vector<User>& users, const std::string& filename);
std::vector<User> CarregarUser(const std::string& filename);
bool UserExist(const std::string& name);
