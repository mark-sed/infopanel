import connexion
import six

from swagger_server.models.lamp_status import LampStatus  # noqa: E501
from swagger_server import util
from sys import path
path.append("../")
import request_handler


def set_brightness(value):  # noqa: E501
    """Set panel&#39;s brightness

    Sets brightness for each led in the panel. Allowed values are &lt;0; 255&gt; # noqa: E501

    :param value: New brightness value
    :type value: int

    :rtype: None
    """
    return 200 if request_handler.setBrightness(value) else 400


def show_clock(time_sec):  # noqa: E501
    """Shows wall clock

    Interupts current widget and shows wall clock for set amount of time # noqa: E501

    :param time_sec: How many seconds will be the wall clock shown for
    :type time_sec: int

    :rtype: None
    """
    return 200 if request_handler.showClock(time_sec) else 400


def show_stocks():  # noqa: E501
    """Scrolls stocks and crypto on the panel

    Interupts current widget and scrolls one time through all the stocks and crypto # noqa: E501


    :rtype: None
    """
    return 200 if request_handler.showStocks() else 400


def toggle_display():  # noqa: E501
    """Toggles the display on or off

    Toggles display on or off # noqa: E501


    :rtype: LampStatus
    """
    return LampStatus(request_handler.toggleDisplay())


def toggle_lamp():  # noqa: E501
    """Toggles lamp mode

    Interupts current widget and toggle lamp (ON-&gt;OFF; OFF-&gt;ON) and returns current state of the lamp # noqa: E501


    :rtype: LampStatus
    """
    return LampStatus(request_handler.toggleLamp())
