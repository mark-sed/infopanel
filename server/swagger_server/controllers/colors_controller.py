import connexion
import six

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
