# coding: utf-8

from __future__ import absolute_import

from flask import json
from six import BytesIO

from swagger_server.models.lamp_status import LampStatus  # noqa: E501
from swagger_server.test import BaseTestCase


class TestControllerController(BaseTestCase):
    """ControllerController integration test stubs"""

    def test_set_brightness(self):
        """Test case for set_brightness

        Set panel's brightness
        """
        response = self.client.open(
            '/sedlacek/StockPanel/1.0.0/controller/brightness/{value}'.format(value=56),
            method='GET')
        self.assert200(response,
                       'Response body is : ' + response.data.decode('utf-8'))

    def test_show_clock(self):
        """Test case for show_clock

        Shows wall clock
        """
        response = self.client.open(
            '/sedlacek/StockPanel/1.0.0/controller/showClock/{time_sec}'.format(time_sec=56),
            method='GET')
        self.assert200(response,
                       'Response body is : ' + response.data.decode('utf-8'))

    def test_show_stocks(self):
        """Test case for show_stocks

        Scrolls stocks and crypto on the panel
        """
        response = self.client.open(
            '/sedlacek/StockPanel/1.0.0/controller/showStocks',
            method='GET')
        self.assert200(response,
                       'Response body is : ' + response.data.decode('utf-8'))

    def test_toggle_display(self):
        """Test case for toggle_display

        Toggles the display on or off
        """
        response = self.client.open(
            '/sedlacek/StockPanel/1.0.0/controller/toggleDisplay',
            method='GET')
        self.assert200(response,
                       'Response body is : ' + response.data.decode('utf-8'))

    def test_toggle_lamp(self):
        """Test case for toggle_lamp

        Toggles lamp mode
        """
        response = self.client.open(
            '/sedlacek/StockPanel/1.0.0/controller/toggleLamp',
            method='GET')
        self.assert200(response,
                       'Response body is : ' + response.data.decode('utf-8'))


if __name__ == '__main__':
    import unittest
    unittest.main()
