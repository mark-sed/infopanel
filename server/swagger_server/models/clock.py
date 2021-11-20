# coding: utf-8

from __future__ import absolute_import
from datetime import date, datetime  # noqa: F401

from typing import List, Dict  # noqa: F401

from swagger_server.models.base_model_ import Model
from swagger_server import util


class Clock(Model):
    """NOTE: This class is auto generated by the swagger code generator program.

    Do not edit the class manually.
    """

    def __init__(self, active: bool=None, format24hr: bool=None, font: str=None, type: str=None):  # noqa: E501
        """Clock - a model defined in Swagger

        :param active: The active of this Clock.  # noqa: E501
        :type active: bool
        :param format24hr: The format24hr of this Clock.  # noqa: E501
        :type format24hr: bool
        :param font: The font of this Clock.  # noqa: E501
        :type font: str
        :param type: The type of this Clock.  # noqa: E501
        :type type: str
        """
        self.swagger_types = {
            'active': bool,
            'format24hr': bool,
            'font': str,
            'type': str
        }

        self.attribute_map = {
            'active': 'active',
            'format24hr': 'format24hr',
            'font': 'font',
            'type': 'type'
        }

        self._active = active
        self._format24hr = format24hr
        self._font = font
        self._type = type

    @classmethod
    def from_dict(cls, dikt) -> 'Clock':
        """Returns the dict as a model

        :param dikt: A dict.
        :type: dict
        :return: The Clock of this Clock.  # noqa: E501
        :rtype: Clock
        """
        return util.deserialize_model(dikt, cls)

    @property
    def active(self) -> bool:
        """Gets the active of this Clock.


        :return: The active of this Clock.
        :rtype: bool
        """
        return self._active

    @active.setter
    def active(self, active: bool):
        """Sets the active of this Clock.


        :param active: The active of this Clock.
        :type active: bool
        """

        self._active = active

    @property
    def format24hr(self) -> bool:
        """Gets the format24hr of this Clock.


        :return: The format24hr of this Clock.
        :rtype: bool
        """
        return self._format24hr

    @format24hr.setter
    def format24hr(self, format24hr: bool):
        """Sets the format24hr of this Clock.


        :param format24hr: The format24hr of this Clock.
        :type format24hr: bool
        """

        self._format24hr = format24hr

    @property
    def font(self) -> str:
        """Gets the font of this Clock.


        :return: The font of this Clock.
        :rtype: str
        """
        return self._font

    @font.setter
    def font(self, font: str):
        """Sets the font of this Clock.


        :param font: The font of this Clock.
        :type font: str
        """

        self._font = font

    @property
    def type(self) -> str:
        """Gets the type of this Clock.


        :return: The type of this Clock.
        :rtype: str
        """
        return self._type

    @type.setter
    def type(self, type: str):
        """Sets the type of this Clock.


        :param type: The type of this Clock.
        :type type: str
        """

        self._type = type
