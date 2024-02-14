<<<<<<< HEAD
# This is a sample Python script.

# Press Shift+F10 to execute it or replace it with your code.
# Press Double Shift to search everywhere for classes, files, tool windows, actions, and settings.


def print_hi(name):
    # Use a breakpoint in the code line below to debug your script.
    print(f'Hi, {name}')  # Press Ctrl+F8 to toggle the breakpoint.


# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    print_hi('PyCharm')

# See PyCharm help at https://www.jetbrains.com/help/pycharm/
=======
import os, sys, logging, yaml

logger = logging.getLogger(__name__)

import maya.cmds as cmds
from maya import standalone



def readConfig(config_path):
    with open(config_path, 'r') as stream:
        data = yaml.safe_load(stream)

    return data


def loadTestPlugin(pluginPath):
    if not os.path.exists(pluginPath):
        logging.exception(f"Plugin path: {pluginPath} not found.")
        raise FileNotFoundError(f"Plugin path: {pluginPath} not found.")
    loaded = cmds.loadPlugin(pluginPath)

    logging.info(f"Successfully loaded plugin '{loaded}'")
    return




def spawnNode(nodeName):
    try:
        nodeName = cmds.createNode(nodeName)
    except Exception as e:
        logger.error(e)

    return nodeName

def createTestTransform(name):
    nodeName = cmds.createNode('transform', name)
    return nodeName

def initilaizeStandalone():
    standalone.initialize()

def main():
    initilaizeStandalone()
    config = readConfig("parameters.yaml")
    plugin = config.get("plugin-path")
    nodeName = config.get("node-name")

    loadTestPlugin(plugin)
    spawnNode(nodeName)

    inputText = ""
    while inputText != "EXIT":
        inputText = input(">>>")
        try:
            result = eval(inputText)
            print(">",result)
        except Exception as e:
            logging.error(e)

if __name__ == "__main__":
    main()
>>>>>>> main
