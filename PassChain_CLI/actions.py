import sys

from mbedtls import cipher

import pandas as pd
import copy


def add_credential(json_credentials, connection):
    if len(json_credentials) >= 100:
        print("[ERROR] Cannot add credentials: PassChain is full.")
        return

    print('\nInsert new credentials...')

    while True:
        print('Please insert Application Name: ')
        name = input().strip()
        print(f"Is '{name}' correct? [Y/n]")

        option = input()
        if option.casefold() == 'y':
            if name == "":
                print("[ERROR] The name is empty.\n")
                continue

            flag = False
            for entry_name in json_credentials:
                if entry_name['name'] == name:
                    print("[ERROR] Add failed: this name already exist.\n")
                    flag = True
                    break

            if not flag:
                while True:
                    print('\nPlease insert Username: ')
                    username = input().strip()
                    print(f"Is '{username}' correct? [Y/n]")

                    option = input()
                    if option.casefold() == 'y':
                        if username == "":
                            print("[ERROR] The username is empty.\n")
                            continue

                        while True:
                            print('\nPlease insert Password: ')
                            password = input().strip()
                            print(f"Is '{password}' correct? [Y/n]")

                            option = input()
                            if option.casefold() == 'y':
                                if password == "":
                                    print("[ERROR] The password is empty.\n")
                                    continue

                                entry_enc = {'name': name, 'username': '**************', 'password': '**************'}

                                json_credentials.append(entry_enc)
                                connection.sendall(b'1' + '\xC6'.encode('utf-8') + name.encode('utf-8') +
                                                   '\xC6'.encode('utf-8') + username.encode('utf-8') +
                                                   '\xC6'.encode('utf-8') + password.encode('utf-8'))
                                return

                            elif option.casefold() == 'n':
                                continue

                            else:
                                if not option_invalid():
                                    return

                    elif option.casefold() == 'n':
                        continue

                    else:
                        if not option_invalid():
                            return

        elif option.casefold() == 'n':
            continue

        else:
            if not option_invalid():
                return


def update_credential(json_credentials, connection):
    print('\nUpdate credentials...')

    while True:
        print('Select the name that do you want update: ')
        old_name = input().strip()
        print(f"Is '{old_name}' correct? [Y/n]")

        option = input()
        if option.casefold() == 'y':
            for entry_name in json_credentials:
                if entry_name['name'] == old_name:
                    while True:
                        print('\nDo you want update name? [Y/n]')
                        option = input()

                        if option.casefold() == 'y':
                            while True:
                                print('Please insert name: ')
                                new_name = input().strip()
                                print(f"Is '{new_name}' correct? [Y/n]")

                                option = input()
                                if option.casefold() == 'y':
                                    if new_name == "":
                                        print("[ERROR] The name is empty.\n")
                                        continue

                                    while True:
                                        print('\nDo you want update username? [Y/n]')
                                        option = input()

                                        if option.casefold() == 'y':
                                            while True:
                                                print('Please insert username: ')
                                                new_username = input().strip()
                                                print(f"Is '{new_username}' correct? [Y/n]")

                                                option = input()
                                                if option.casefold() == 'y':
                                                    if new_username == "":
                                                        print("[ERROR] The username is empty.\n")
                                                        continue

                                                    while True:
                                                        print('\nDo you want update password? [Y/n]')
                                                        option = input()

                                                        if option.casefold() == 'y':
                                                            while True:
                                                                print('Please insert password: ')
                                                                new_password = input().strip()
                                                                print(f"Is '{new_password}' correct? [Y/n]")

                                                                option = input()
                                                                if option.casefold() == 'y':
                                                                    if new_password == "":
                                                                        print("[ERROR] The password is empty.\n")
                                                                        continue

                                                                    entry_name['name'] = new_name
                                                                    entry_name['username'] = new_username
                                                                    entry_name['password'] = new_password
                                                                    connection.sendall(b'2' + '\xC6'.encode('utf-8') +
                                                                                       old_name.encode('utf-8') +
                                                                                       '\xC6'.encode('utf-8') +
                                                                                       new_name.encode('utf-8') +
                                                                                       '\xC6'.encode('utf-8') +
                                                                                       new_username.encode('utf-8') +
                                                                                       '\xC6'.encode('utf-8') +
                                                                                       new_password.encode('utf-8'))
                                                                    return
                                                                elif option.casefold() == 'n':
                                                                    continue
                                                                else:
                                                                    if not option_invalid():
                                                                        return
                                                        elif option.casefold() == 'n':
                                                            entry_name['name'] = new_name
                                                            entry_name['username'] = new_username
                                                            connection.sendall(b'2' + '\xC6'.encode('utf-8') +
                                                                               old_name.encode('utf-8') +
                                                                               '\xC6'.encode('utf-8') +
                                                                               new_name.encode('utf-8') +
                                                                               '\xC6'.encode('utf-8') +
                                                                               new_username.encode('utf-8') +
                                                                               '\xC6'.encode('utf-8') + b'NULL')
                                                            return
                                                        else:
                                                            if not option_invalid():
                                                                return
                                                elif option.casefold() == 'n':
                                                    continue
                                                else:
                                                    if not option_invalid():
                                                        return
                                        elif option.casefold() == 'n':
                                            while True:
                                                print('\nDo you want update password? [Y/n]')
                                                option = input()

                                                if option.casefold() == 'y':
                                                    while True:
                                                        print('Please insert password: ')
                                                        new_password = input().strip()
                                                        print(f"Is '{new_password}' correct? [Y/n]")

                                                        option = input()
                                                        if option.casefold() == 'y':
                                                            if new_password == "":
                                                                print("[ERROR] The password is empty.\n")
                                                                continue

                                                            entry_name['name'] = new_name
                                                            entry_name['password'] = new_password
                                                            connection.sendall(b'2' + '\xC6'.encode('utf-8') +
                                                                               old_name.encode('utf-8') +
                                                                               '\xC6'.encode('utf-8') +
                                                                               new_name.encode('utf-8') +
                                                                               '\xC6'.encode('utf-8') + b'NULL' +
                                                                               '\xC6'.encode('utf-8') +
                                                                               new_password.encode('utf-8'))
                                                            return
                                                        elif option.casefold() == 'n':
                                                            continue
                                                        else:
                                                            if not option_invalid():
                                                                return
                                                elif option.casefold() == 'n':
                                                    entry_name['name'] = new_name
                                                    connection.sendall(b'2' + '\xC6'.encode('utf-8') +
                                                                       old_name.encode('utf-8') +
                                                                       '\xC6'.encode('utf-8') +
                                                                       new_name.encode('utf-8') +
                                                                       '\xC6'.encode('utf-8') + b'NULL' +
                                                                       '\xC6'.encode('utf-8') + b'NULL')
                                                    return
                                                else:
                                                    if not option_invalid():
                                                        return
                                        else:
                                            if not option_invalid():
                                                return
                                elif option.casefold() == 'n':
                                    continue
                                else:
                                    if not option_invalid():
                                        return
                        elif option.casefold() == 'n':
                            print('\nDo you want update username? [Y/n]')
                            option = input()

                            if option.casefold() == 'y':
                                while True:
                                    print('Please insert username: ')
                                    new_username = input().strip()
                                    print(f"Is '{new_username}' correct? [Y/n]")

                                    option = input()
                                    if option.casefold() == 'y':
                                        if new_username == "":
                                            print("[ERROR] The username is empty.\n")
                                            continue

                                        print('\nDo you want update password? [Y/n]')
                                        option = input()

                                        if option.casefold() == 'y':
                                            print('Please insert password: ')
                                            new_password = input().strip()
                                            print(f"Is '{new_password}' correct? [Y/n]")

                                            if option.casefold() == 'y':
                                                if new_password == "":
                                                    print("[ERROR] The password is empty.\n")
                                                    continue

                                                entry_name['username'] = new_username
                                                entry_name['password'] = new_password
                                                connection.sendall(b'2' + '\xC6'.encode('utf-8') +
                                                                   old_name.encode('utf-8') +
                                                                   '\xC6'.encode('utf-8') + b'NULL' +
                                                                   '\xC6'.encode('utf-8') +
                                                                   new_username.encode('utf-8') +
                                                                   '\xC6'.encode('utf-8') +
                                                                   new_password.encode('utf-8'))
                                                return
                                            elif option.casefold() == 'n':
                                                continue
                                            else:
                                                if not option_invalid():
                                                    return
                                        elif option.casefold() == 'n':
                                            entry_name['username'] = new_username
                                            connection.sendall(b'2' + '\xC6'.encode('utf-8') +
                                                               old_name.encode('utf-8') +
                                                               '\xC6'.encode('utf-8') + b'NULL' +
                                                               '\xC6'.encode('utf-8') +
                                                               new_username.encode('utf-8') +
                                                               '\xC6'.encode('utf-8') + b'NULL')
                                            return
                                        else:
                                            if not option_invalid():
                                                return
                                    elif option.casefold() == 'n':
                                        continue
                                    else:
                                        if not option_invalid():
                                            return
                            elif option.casefold() == 'n':
                                print('\nDo you want update password? [Y/n]')
                                option = input()

                                if option.casefold() == 'y':
                                    print('Please insert password: ')
                                    new_password = input().strip()
                                    print(f"Is '{new_password}' correct? [Y/n]")

                                    if option.casefold() == 'y':
                                        if new_password == "":
                                            print("[ERROR] The password is empty.\n")
                                            continue

                                        entry_name['password'] = new_password
                                        connection.sendall(b'2' + '\xC6'.encode('utf-8') + old_name.encode('utf-8') +
                                                           '\xC6'.encode('utf-8') + b'NULL' + '\xC6'.encode('utf-8') +
                                                           b'NULL' + '\xC6'.encode('utf-8') +
                                                           new_password.encode('utf-8'))
                                        return
                                    elif option.casefold() == 'n':
                                        continue
                                    else:
                                        if not option_invalid():
                                            return
                                elif option.casefold() == 'n':
                                    return
                                else:
                                    if not option_invalid():
                                        return
                            else:
                                if not option_invalid():
                                    return
                        else:
                            if not option_invalid():
                                return

            print("[ERROR] Name not found.")
            print("Do you want to try again? [Y/n]")
            option = input()

            if option.casefold() == 'y':
                continue
            elif option.casefold() == 'n':
                return
            else:
                if not option_invalid():
                    return
        elif option.casefold() == 'n':
            continue
        else:
            if not option_invalid():
                return


def delete_credential(json_credentials, connection):
    print('\nDelete credentials...')

    if len(json_credentials) <= 0:
        print('[ERROR] Credentials list is empty.\n')
        return

    while True:
        print("Select the credential's name that do you want delete: ")
        name = input().strip()
        print(f"Is '{name}' correct? [Y/n]")

        option = input()
        if option.casefold() == 'y':
            for i in range(len(json_credentials)):
                if json_credentials[i]['name'] == name:
                    del json_credentials[i]
                    connection.sendall(b'3' + '\xC6'.encode('utf-8') + name.encode('utf-8'))
                    return

            print("[ERROR] Name not found.")
            print("Do you want to try again? [Y/n]")

            option = input()
            if option.casefold() == 'y':
                continue
            elif option.casefold() == 'n':
                return
            else:
                if not option_invalid():
                    return
        elif option.casefold() == 'n':
            continue
        else:
            if not option_invalid():
                return


def set_fingerprints(json_credentials, connection):
    print('a')


def set_hotspot(hotspot, connection):
    print('\nSetup HotSpot credentials...')

    cred = hotspot.split('\xC6')
    cred[0] = cred[0][0:len(cred[0]) - 1]
    cred[1] = cred[1][0:len(cred[1]) - 1]
    print('Actual credentials: [SSID: ' + cred[0] + ", password: " + cred[1] + "]\n")

    while True:
        print('Do you want update SSID? [Y/n]')

        option = input()
        if option.casefold() == 'y':
            while True:
                print('Please insert SSID: ')
                ssid = input().strip()
                print(f"Is '{ssid}' correct? [Y/n]")

                option = input()
                if option.casefold() == 'y':
                    if ssid == "":
                        print("[ERROR] The SSID is empty.\n")
                        continue

                    while True:
                        print('\nDo you want update Password? [Y/n]')
                        option = input()

                        if option.casefold() == 'y':
                            while True:
                                print('Please insert password: ')
                                password = input().strip()
                                print(f"Is '{password}' correct? [Y/n]")

                                option = input()
                                if option.casefold() == 'y':
                                    if password == "":
                                        print("[ERROR] The password is empty.\n")
                                        continue

                                    if len(password) < 8:
                                        print("[ERROR] The password must be at least 8 characters.\n")
                                        continue

                                    connection.sendall(b'5' + '\xC6'.encode('utf-8') + ssid.encode('utf-8') +
                                                       '\xC6'.encode('utf-8') + password.encode('utf-8'))
                                    return ssid + '\xC6' + password
                                elif option.casefold() == 'n':
                                    continue
                                else:
                                    if not option_invalid():
                                        return
                        elif option.casefold() == 'n':
                            connection.sendall(b'5' + '\xC6'.encode('utf-8') +
                                               ssid.encode('utf-8') + '\xC6'.encode('utf-8') + b'NULL')
                            return ssid + '\xC6' + cred[1]
                        else:
                            if not option_invalid():
                                return
                elif option.casefold() == 'n':
                    continue
                else:
                    if not option_invalid():
                        return
        elif option.casefold() == 'n':
            while True:
                print('\nDo you want update Password? [Y/n]')
                option = input()

                if option.casefold() == 'y':
                    while True:
                        print('Please insert password: ')
                        password = input().strip()
                        print(f"Is '{password}' correct? [Y/n]")

                        option = input()
                        if option.casefold() == 'y':
                            if password == "":
                                print("[ERROR] The password is empty.\n")
                                continue

                            if len(password) < 8:
                                print("[ERROR] The password must be at least 8 characters.\n")
                                continue

                            connection.sendall(b'5' + '\xC6'.encode('utf-8') + b'NULL' + '\xC6'.encode('utf-8') +
                                               password.encode('utf-8'))
                            return cred[0] + '\xC6' + password
                        elif option.casefold() == 'n':
                            continue
                        else:
                            if not option_invalid():
                                return
                elif option.casefold() == 'n':
                    return
                else:
                    if not option_invalid():
                        return
        else:
            if not option_invalid():
                return


def exitcode(connection):
    connection.close()
    sys.exit()


def decrypt_credentials(json_credentials, key):
    json_credentials_tmp = copy.deepcopy(json_credentials)
    c = cipher.AES.new(key, cipher.MODE_ECB, b"sssssssss")
    print(key)

    for entry in json_credentials_tmp:
        entry['username'] = c.decrypt(entry['username'].encode()).decode('utf-8'),
        entry['password'] = c.decrypt(entry['password'].encode()).decode('utf-8'),

    print(pd.DataFrame(data=json_credentials_tmp))


def option_invalid():
    while True:
        print("Option not valid. Retry [Y/n]")
        select = input()

        if select.casefold() == 'y':
            return True
        elif select.casefold() == 'n':
            return False
