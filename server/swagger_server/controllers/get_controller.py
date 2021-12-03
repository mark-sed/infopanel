import connexion
import six

from swagger_server.models.curr_settings import CurrSettings  # noqa: E501
from swagger_server.models.int_value import IntValue  # noqa: E501
from swagger_server.models.lamp_status import LampStatus  # noqa: E501
from swagger_server.models.list_of_strings import ListOfStrings  # noqa: E501
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


def get_clock_types():  # noqa: E501
    """Available fonts

    Returns available fonts # noqa: E501


    :rtype: ListOfStrings
    """
    return ["Simple", "Classic"]


def get_currencies():  # noqa: E501
    """Available fonts

    Returns available fonts # noqa: E501


    :rtype: ListOfStrings
    """
    return ["USD", "CZK", "EUR"]


def get_display_status():  # noqa: E501
    """Available fonts

    Returns available fonts # noqa: E501


    :rtype: LampStatus
    """
    return LampStatus(request_handler.getDisplayStatus())


def get_fonts():  # noqa: E501
    """Available fonts

    Returns available fonts # noqa: E501


    :rtype: ListOfStrings
    """
    return ["Ascii", "Pixelated"]


def get_lamp_status():  # noqa: E501
    """Available fonts

    Returns available fonts # noqa: E501


    :rtype: LampStatus
    """
    return LampStatus(request_handler.getLampStatus())


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
