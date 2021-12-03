import connexion
import six

from swagger_server.models.scheduler import Scheduler  # noqa: E501
from swagger_server import util
from sys import path
path.append("../")
import request_handler


def set_color_gain(hex_code):  # noqa: E501
    """Color setup

    Color setup. Color code should be uppercase hexadecimal string with 0x prefix. E.g. \&quot;0x4200FF\&quot; # noqa: E501

    :param hex_code: Hexadecimal color value (with 0x prefix in uppercase)
    :type hex_code: str

    :rtype: None
    """
    return 200 if request_handler.setColorGain(hex_code) else 400


def set_color_loss(hex_code):  # noqa: E501
    """Color setup

    Color setup. Color code should be uppercase hexadecimal string with 0x prefix. E.g. \&quot;0x4200FF\&quot; # noqa: E501

    :param hex_code: Hexadecimal color value (with 0x prefix in uppercase)
    :type hex_code: str

    :rtype: None
    """
    return 200 if request_handler.setColorLoss(hex_code) else 400


def set_color_neutral(hex_code):  # noqa: E501
    """Color setup

    Color setup. Color code should be uppercase hexadecimal string with 0x prefix. E.g. \&quot;0x4200FF\&quot; # noqa: E501

    :param hex_code: Hexadecimal color value (with 0x prefix in uppercase)
    :type hex_code: str

    :rtype: None
    """
    return 200 if request_handler.setColorNeutral(hex_code) else 400


def set_color_price(hex_code):  # noqa: E501
    """Color setup

    Color setup. Color code should be uppercase hexadecimal string with 0x prefix. E.g. \&quot;0x4200FF\&quot; # noqa: E501

    :param hex_code: Hexadecimal color value (with 0x prefix in uppercase)
    :type hex_code: str

    :rtype: None
    """
    return 200 if request_handler.setColorPrice(hex_code) else 400


def set_color_symbol(hex_code):  # noqa: E501
    """Color setup

    Color setup. Color code should be uppercase hexadecimal string with 0x prefix. E.g. \&quot;0x4200FF\&quot; # noqa: E501

    :param hex_code: Hexadecimal color value (with 0x prefix in uppercase)
    :type hex_code: str

    :rtype: None
    """
    return 200 if request_handler.setColorSymbol(hex_code) else 400


def set_currency(name):  # noqa: E501
    """Sets up prefered currency

    Sets up prefered currency # noqa: E501

    :param name: Currency name (eg. usd/czk/eur)
    :type name: str

    :rtype: None
    """
    return 200 if request_handler.setCurrency(name) else 400


def set_finhub_key(key):  # noqa: E501
    """Sets up Finhub key

    Sets up Finhub key # noqa: E501

    :param key: Finhub API key
    :type key: str

    :rtype: None
    """
    return 200 if request_handler.setFinhubKey(key) else 400


def set_polygon_key(key):  # noqa: E501
    """Sets up Finhub key

    Sets up Finhub key # noqa: E501

    :param key: Polygon API key
    :type key: str

    :rtype: None
    """
    return 200 if request_handler.setPolygonKey(key) else 400


def set_scheduler(scheduler):  # noqa: E501
    """Sets up scheduler

    Sets up scheduler # noqa: E501

    :param scheduler: 
    :type scheduler: dict | bytes

    :rtype: None
    """
    if connexion.request.is_json:
        scheduler = Scheduler.from_dict(connexion.request.get_json())  # noqa: E501
    else:
        return 400
    return 200 if request_handler.setScheduler(scheduler) else 400
