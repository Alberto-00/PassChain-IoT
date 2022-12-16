from actions import *
from server import *

import pyfiglet
import pandas as pd


def select_actions(json_credentials, connection, key):
    while True:
        print("\n\n###############################\n"
              "# Select an action:           #\n"
              "# 1. Add                      #\n"
              "# 2. Update                   #\n"
              "# 3. Delete                   #\n"
              "# 4. Set Finger Prints        #\n"
              "# 5. Set HotSpot credentials  #\n"
              "# 'quit' to Exit              #\n"
              "###############################\n")
        print(pd.DataFrame(data=json_credentials))
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
