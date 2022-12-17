from mbedtls import cipher

import pandas as pd
import copy

BLOCK_SIZE = 16  # Bytes


def add_credential(json_credentials, connection, key):
    if len(json_credentials) >= 100:
        print("[ERROR] Cannot add credentials: PassChain is full.")
        return

    print('\nInsert new credentials...')

    while True:
        print('Please insert Application Name: ')
        name = input()
        print(f"Is '{name}' correct? [Y/n]")

        option = input()
        if option.casefold() == 'y':
            while True:
                print('\nPlease insert Username: ')
                username = input()
                print(f"Is '{username}' correct? [Y/n]")

                option = input()
                if option.casefold() == 'y':
                    while True:
                        print('\nPlease insert Password: ')
                        password = input()
                        print(f"Is '{password}' correct? [Y/n]")

                        option = input()
                        if option.casefold() == 'y':
                            entry_enc = {'name': name, 'username': '**************', 'password': '**************'}

                            json_credentials.append(entry_enc)
                            connection.sendall(b'1-' + name.encode('utf-8') + b'-' + username.encode('utf-8') + b'-' +
                                               password.encode('utf-8'))
                            return

                        elif option.casefold() == 'n':
                            continue

                        else:
                            while True:
                                print("Option not valid. Retry [Y/n]")
                                select = input()

                                if select.casefold() == 'y':
                                    break
                                elif select.casefold() == 'n':
                                    return

                elif option.casefold() == 'n':
                    continue

                else:
                    while True:
                        print("Option not valid. Retry [Y/n]")
                        select = input()

                        if select.casefold() == 'y':
                            break
                        elif select.casefold() == 'n':
                            return

        elif option.casefold() == 'n':
            continue

        else:
            while True:
                print("Option not valid. Retry [Y/n]")
                select = input()

                if select.casefold() == 'y':
                    break
                elif select.casefold() == 'n':
                    return


def update_credential(json_credentials, connection):
    print('\nUpdate credentials...')

    while True:
        print('Select the index that do you want update?')
        index = int(input())

        if len(json_credentials) > 0 and 0 < index < len(json_credentials):
            print('a')


def delete_credential(json_credentials, connection):
    print('a')


def set_fingerprints(json_credentials, connection):
    print('a')


def exitcode():
    print('a')


def decrypt_credentials(json_credentials, key):
    json_credentials_tmp = copy.deepcopy(json_credentials)
    c = cipher.AES.new(key, cipher.MODE_ECB, b"sssssssss")
    print(key)

    for entry in json_credentials_tmp:
        entry['username'] = c.decrypt(entry['username'].encode()).decode('utf-8'),
        entry['password'] = c.decrypt(entry['password'].encode()).decode('utf-8'),

    print(pd.DataFrame(data=json_credentials_tmp))

