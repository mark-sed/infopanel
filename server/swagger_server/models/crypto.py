# coding: utf-8

from __future__ import absolute_import
from datetime import date, datetime  # noqa: F401

from typing import List, Dict  # noqa: F401

from swagger_server.models.base_model_ import Model
from swagger_server import util


class Crypto(Model):
    """NOTE: This class is auto generated by the swagger code generator program.

    Do not edit the class manually.
    """

    def __init__(self, active: bool=None, tickers: List[str]=None, show_price: bool=None, show_percentage: bool=None):  # noqa: E501
        """Crypto - a model defined in Swagger

        :param active: The active of this Crypto.  # noqa: E501
        :type active: bool
        :param tickers: The tickers of this Crypto.  # noqa: E501
        :type tickers: List[str]
        :param show_price: The show_price of this Crypto.  # noqa: E501
        :type show_price: bool
        :param show_percentage: The show_percentage of this Crypto.  # noqa: E501
        :type show_percentage: bool
        """
        self.swagger_types = {
            'active': bool,
            'tickers': List[str],
            'show_price': bool,
            'show_percentage': bool
        }

        self.attribute_map = {
            'active': 'active',
            'tickers': 'tickers',
            'show_price': 'show_price',
            'show_percentage': 'show_percentage'
        }

        self._active = active
        self._tickers = tickers
        self._show_price = show_price
        self._show_percentage = show_percentage

    @classmethod
    def from_dict(cls, dikt) -> 'Crypto':
        """Returns the dict as a model

        :param dikt: A dict.
        :type: dict
        :return: The Crypto of this Crypto.  # noqa: E501
        :rtype: Crypto
        """
        return util.deserialize_model(dikt, cls)

    @property
    def active(self) -> bool:
        """Gets the active of this Crypto.


        :return: The active of this Crypto.
        :rtype: bool
        """
        return self._active

    @active.setter
    def active(self, active: bool):
        """Sets the active of this Crypto.


        :param active: The active of this Crypto.
        :type active: bool
        """

        self._active = active

    @property
    def tickers(self) -> List[str]:
        """Gets the tickers of this Crypto.


        :return: The tickers of this Crypto.
        :rtype: List[str]
        """
        return self._tickers

    @tickers.setter
    def tickers(self, tickers: List[str]):
        """Sets the tickers of this Crypto.


        :param tickers: The tickers of this Crypto.
        :type tickers: List[str]
        """

        self._tickers = tickers

    @property
    def show_price(self) -> bool:
        """Gets the show_price of this Crypto.


        :return: The show_price of this Crypto.
        :rtype: bool
        """
        return self._show_price

    @show_price.setter
    def show_price(self, show_price: bool):
        """Sets the show_price of this Crypto.


        :param show_price: The show_price of this Crypto.
        :type show_price: bool
        """

        self._show_price = show_price

    @property
    def show_percentage(self) -> bool:
        """Gets the show_percentage of this Crypto.


        :return: The show_percentage of this Crypto.
        :rtype: bool
        """
        return self._show_percentage

    @show_percentage.setter
    def show_percentage(self, show_percentage: bool):
        """Sets the show_percentage of this Crypto.


        :param show_percentage: The show_percentage of this Crypto.
        :type show_percentage: bool
        """

        self._show_percentage = show_percentage
