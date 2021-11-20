import connexion
import six

from swagger_server.models.curr_settings import CurrSettings  # noqa: E501
from swagger_server.models.int_value import IntValue  # noqa: E501
from swagger_server.models.scheduler import Scheduler  # noqa: E501
from swagger_server import util

from sys import path
path.append("../")
import request_handler

import json


def get_brightness():  # noqa: E501
    """Current brightness value

    Returns current brightness value # noqa: E501


    :rtype: IntValue
    """
    return json.loads(request_handler.getBrightness())


def get_scheduler():  # noqa: E501
    """Current scheduler settings

    Returns current scheduler settings # noqa: E501


    :rtype: Scheduler
    """
    return json.loads(request_handler.getScheduler())


def get_settings():  # noqa: E501
    """Current panel settings

    Returns current panel settings # noqa: E501


    :rtype: CurrSettings
    """
    return json.loads(request_handler.getSettings())
