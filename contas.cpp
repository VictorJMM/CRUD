#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

#include "Headers/Conta.h"

std::vector<User> users;

void create() {
    User newUser;

    std::cout << "Name: ";
    std::cin >> newUser.name;

    if (UserExist(newUser.name)) {
        std::cout << "\nEste usuario já existe!\n";
    }
    else {
        std::cout << "Password: ";
        std::cin >> newUser.passwd;

        newUser.saldo = 0.0;
        newUser.id = users.size() + 1;
        newUser.IsADM = false;

        users.push_back(newUser);
        std::cout << "Usuario cadastrado com sucesso!" << std::endl;
    }
}

void listUsers() {
    std::cout << "\nLista de Usuarios\n";
    for (const auto& user : users) {
        std::cout << "ID: " << user.id << " | Nome: " << user.name
            << " | Senha: " << user.passwd << " | Saldo: " << user.saldo << "\n";
    }
}

void login() {
    std::string LOGuser, LOGpasswd;
    std::string userpasswd = "";

    std::cout << "LOGAR\n";
    std::cout << "User: ";
    std::cin >> LOGuser;

    std::cout << "Senha: ";
    std::cin >> LOGpasswd;

    for (const auto& user : users) {
        if (user.name == LOGuser) {
            userpasswd = user.passwd;
            break;
        }
    }

    if (UserExist(LOGuser) && LOGpasswd == userpasswd) {
        std::cout << "Logado com sucesso!" << std::endl;
    }
    else {
        std::cout << "Usuario ou senha incorretos" << std::endl;
    }
}

void DeletUser() {
    int IDforDelet;
    listUsers();
    std::cout << "\nID do usuario a ser removido: ";
    std::cin >> IDforDelet;

    auto it = std::remove_if(users.begin(), users.end(),
        [IDforDelet](const User& user) {
            return user.id == IDforDelet;
        });

    if (it != users.end()) {
        users.erase(it, users.end());
        std::cout << "\nUsuario removido com sucesso!\n";
    }
    else if (IDforDelet == 00) {
        Menu();
    }
    else
    {
        std::cout << "\nID nao encontrado!\n";
    }

    listUsers();
}

void SaveUser(const std::vector<User>& users, const std::string& filename) {
    std::ofstream file(filename, std::ios::out);
    if (!file) {
        std::cerr << "Erro ao abrir o arquivo para salvar!\n";
        return;
    }

    for (const auto& user : users) {
        file << user.id << "|" << user.name << "|" << user.passwd << "|" << user.saldo << "\n";
    }

    file.close();
    std::cout << "Usuarios salvos em '" << filename << "' com sucesso!\n";
}

std::vector<User> CarregarUser(const std::string& filename) {
    std::vector<User> users;
    std::ifstream file(filename, std::ios::in);

    if (!file) {
        std::cerr << "Erro ao abrir o arquivo para carregar!\n";
        return users;  
    }

    User user;
    std::string linha;
    while (getline(file, linha)) {
        size_t pos1 = linha.find("|");
        size_t pos2 = linha.find("|", pos1 + 1);
        size_t pos3 = linha.find("|", pos2 + 1);

        if (pos1 == std::string::npos || pos2 == std::string::npos || pos3 == std::string::npos) {
            std::cerr << "Formato inválido na linha: " << linha << std::endl;
            continue;  
        }

       
        user.id = std::stoi(linha.substr(0, pos1));
        user.name = linha.substr(pos1 + 1, pos2 - pos1 - 1);
        user.passwd = linha.substr(pos2 + 1, pos3 - pos2 - 1);
        user.saldo = std::stod(linha.substr(pos3 + 1));

        users.push_back(user);  
    }

    file.close();  
    std::cout << "Usuarios carregados de '" << filename << "' com sucesso!\n";
    return users;  
}

void carregar() {
    std::string filename = "C:/Program Files/VKdatabase/Dbsalvas.dbvk";
    users = CarregarUser(filename);
}

void Save() {
    std::string path = "C:/Program Files/VKdatabase";

    if (std::filesystem::create_directory(path)) {
    }
    else
    {
        std::cout << "Falha ao criar o path." << std::endl;
    }

    std::string filename = "C:/Program Files/VKdatabase/Dbsalvas.dbvk";
    SaveUser(users, filename);
}

void Menu() {
    int escolha;
    while (true) {
        std::cout << "\n1 | Cadastrar\n2 | Listar\n3 | Logar\n4 | Deletar\n5 | Salvar\n6 | Carregar\nEscolha: ";
        std::cin >> escolha;

        switch (escolha) {
        case 1:
            create();
            break;
        case 2:
            listUsers();
            break;
        case 3:
            login();
            break;
        case 4:
            DeletUser();
            break;
        case 5:
            Save();
            break;
        case 6:
            carregar();
            break;
        default:
            std::cout << "Opção inválida, tente novamente." << std::endl;
            break;
        }
    }
}

bool UserExist(const std::string& name) {
    for (const auto& user : users) {
        if (user.name == name) {
            return true;
        }
    }
    return false;
}
