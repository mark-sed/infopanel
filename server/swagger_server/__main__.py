#!/usr/bin/env python3

import connexion
import threading

from swagger_server import encoder
from sys import path
path.append("../")
import request_handler


def main():
    dummy = request_handler.is_dummy()
    if dummy:
        print("WARNING: Running in DUMMY mode.")	
    if not dummy:
    	request_handler.initPanel()
    app = connexion.App(__name__, specification_dir='./swagger/')
    app.app.json_encoder = encoder.JSONEncoder
    app.add_api('swagger.yaml', arguments={'title': 'Stock Panel'})
    th_server = threading.Thread(target=app.run, args=(8080,))
    th_server.setDaemon(True)
    th_server.start()
    while not dummy:
        request_handler.runPanel()
    th_server.join()


if __name__ == '__main__':
    main()
