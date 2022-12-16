from Crypto.Cipher import AES
from Crypto.Util.Padding import pad
BLOCK_SIZE = 32  # Bytes


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
                            cipher = AES.new(key, AES.MODE_ECB)
                            entry = {'name': name.encode('utf-8'),
                                     'username': cipher.encrypt(pad(username.encode('utf-8'), BLOCK_SIZE)),
                                     'password': cipher.encrypt(pad(password.encode('utf-8'), BLOCK_SIZE))}

                            json_credentials.append(entry)
                            connection.sendall(b'1-' + entry['name'] + b'-' +
                                               entry['username'] + b'-' + entry['password'])
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
    print('a')


def delete_credential(json_credentials, connection):
    print('a')


def set_fingerprints(json_credentials, connection):
    print('a')


def exitcode():
    print('a')
