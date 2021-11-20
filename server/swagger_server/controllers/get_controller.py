import connexion
import six

from swagger_server.models.curr_settings import CurrSettings  # noqa: E501
from swagger_server.models.int_value import IntValue  # noqa: E501
from swagger_server.models.scheduler import Scheduler  # noqa: E501
from swagger_server import util


def get_brightness():  # noqa: E501
    """Current brightness value

    Returns current brightness value # noqa: E501


    :rtype: IntValue
    """
    return 'do some magic!'


def get_scheduler():  # noqa: E501
    """Current scheduler settings

    Returns current scheduler settings # noqa: E501


    :rtype: Scheduler
    """
    return 'do some magic!'


def get_settings():  # noqa: E501
    """Current panel settings

    Returns current panel settings # noqa: E501


    :rtype: CurrSettings
    """
    return 'do some magic!'
