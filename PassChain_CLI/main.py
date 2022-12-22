#!/usr/bin/python
from actions import *
from server import *

import pyfiglet
import pandas as pd
import copy


def select_actions(json_credentials, hotspot, num_fingerprint, connection):
    new_hotspot = hotspot
    new_finger = num_fingerprint

    while True:
        print("\n\n##################################\n"
              "# Select an action:              #\n"
              "# 1. Add                         #\n"
              "# 2. Update                      #\n"
              "# 3. Delete                      #\n"
              "# 4. Set Finger Prints           #\n"
              "# 5. Set HotSpot credentials     #\n"
              "#                                #\n"                       
              "# 'quit' to Exit                 #\n"
              "##################################\n")

        json_credentials_enc_tmp = copy.deepcopy(json_credentials)
        for entry in json_credentials_enc_tmp:
            entry['username'] = '**************'
            entry['password'] = '**************'

        print(pd.DataFrame(data=json_credentials_enc_tmp))
        print("\nInsert action: ")

        option = input()

        match option:
            case '1':
                add_credential(json_credentials, connection)
            case '2':
                update_credential(json_credentials, connection)
            case '3':
                delete_credential(json_credentials, connection)
            case '4':
                new_finger = set_fingerprints(new_finger, connection)
            case '5':
                new_hotspot = set_hotspot(new_hotspot, connection)
            case 'quit':
                exitcode(connection)
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

    try:
        init_server()
    except Exception:
        print(f"\n[ERROR] Something was wrong: connection refused or "
              f"address already in use (kill the port '{get_ip()}:11111').")
        sys.exit()
