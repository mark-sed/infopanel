#!/usr/bin/env python3

import connexion
import threading

from swagger_server import encoder
from sys import path
path.append("../")
import request_handler

def r():
    print("AAA")
    app.run(port=8080)

def main():
    request_handler.initPanel()
    th_panel = threading.Thread(target=request_handler.runPanel)
    #th_panel.setDaemon(True)
    app = connexion.App(__name__, specification_dir='./swagger/')
    app.app.json_encoder = encoder.JSONEncoder
    app.add_api('swagger.yaml', arguments={'title': 'Stock Panel'})
    #app.run(port=8080)
    th_server = threading.Thread(target=app.run, args=(8080,))
    #th_server.setDaemon(True)
    th_server.start()
    while True:
        request_handler.runPanel()
    th_server.join()
    #th_panel.join()


if __name__ == '__main__':
    main()
