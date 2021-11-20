import connexion
import six

from swagger_server import util
from sys import path
path.append("../")
import request_handler


def ping():  # noqa: E501
    """Ping

    Connection check # noqa: E501


    :rtype: None
    """
    return request_handler.hello()
