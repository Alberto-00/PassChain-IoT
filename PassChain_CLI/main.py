from actions import *
from server import *

import pyfiglet
import pandas as pd
import copy


def select_actions(json_credentials, connection, key):
    enc_or_dec_print = True

    while True:
        print("\n\n##################################\n"
              "# Select an action:              #\n"
              "# 1. Add                         #\n"
              "# 2. Update                      #\n"
              "# 3. Delete                      #\n"
              "# 4. Set Finger Prints           #\n"
              "# 5. Set HotSpot credentials     #\n"
              "#                                #\n"                       
              "# 6. Show decrypted credentials  #\n"
              "# 7. Show encrypted credentials  #\n"
              "# 'quit' to Exit                 #\n"
              "##################################\n")

        if enc_or_dec_print:
            json_credentials_enc_tmp = copy.deepcopy(json_credentials)
            for entry in json_credentials_enc_tmp:
                entry['username'] = '**************'
                entry['password'] = '**************'

            print(pd.DataFrame(data=json_credentials_enc_tmp))
        else:
            decrypt_credentials(json_credentials, key)

        print("\nInsert action: ")

        option = input()

        match option:
            case '1':
                add_credential(json_credentials, connection, key)
            case '2':
                update_credential(json_credentials, connection)
            case '3':
                delete_credential(json_credentials, connection)
            case '4':
                set_fingerprints(json_credentials, connection)
            case '6':
                enc_or_dec_print = False
            case '7':
                enc_or_dec_print = True
            case 'quit':
                exitcode()
            case _:
                while True:
                    print("Option not valid. Retry [Y/n]")
                    select = input()

                    if select.casefold() == 'y':
                        break
                    elif select.casefold() == 'n':
                        return


if __name__ == '__main__':
    print('##########################################################')
    print(pyfiglet.figlet_format("Welcome    to\nPassChain"))
    print('##########################################################\n\n')

    # try:
    init_server()
    # except:
    # print("\n[ERROR] Something was wrong: connection refused.")
