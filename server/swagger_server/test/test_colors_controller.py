# coding: utf-8

from __future__ import absolute_import

from flask import json
from six import BytesIO

from swagger_server.test import BaseTestCase


class TestColorsController(BaseTestCase):
    """ColorsController integration test stubs"""

    def test_set_color_gain(self):
        """Test case for set_color_gain

        Color setup
        """
        response = self.client.open(
            '/sedlacek/StockPanel/1.0.0/colors/gain/{hex_code}'.format(hex_code='hex_code_example'),
            method='GET')
        self.assert200(response,
                       'Response body is : ' + response.data.decode('utf-8'))

    def test_set_color_loss(self):
        """Test case for set_color_loss

        Color setup
        """
        response = self.client.open(
            '/sedlacek/StockPanel/1.0.0/colors/loss/{hex_code}'.format(hex_code='hex_code_example'),
            method='GET')
        self.assert200(response,
                       'Response body is : ' + response.data.decode('utf-8'))

    def test_set_color_neutral(self):
        """Test case for set_color_neutral

        Color setup
        """
        response = self.client.open(
            '/sedlacek/StockPanel/1.0.0/colors/neutral/{hex_code}'.format(hex_code='hex_code_example'),
            method='GET')
        self.assert200(response,
                       'Response body is : ' + response.data.decode('utf-8'))

    def test_set_color_price(self):
        """Test case for set_color_price

        Color setup
        """
        response = self.client.open(
            '/sedlacek/StockPanel/1.0.0/colors/price/{hex_code}'.format(hex_code='hex_code_example'),
            method='GET')
        self.assert200(response,
                       'Response body is : ' + response.data.decode('utf-8'))

    def test_set_color_symbol(self):
        """Test case for set_color_symbol

        Color setup
        """
        response = self.client.open(
            '/sedlacek/StockPanel/1.0.0/colors/symbol/{hex_code}'.format(hex_code='hex_code_example'),
            method='GET')
        self.assert200(response,
                       'Response body is : ' + response.data.decode('utf-8'))


if __name__ == '__main__':
    import unittest
    unittest.main()
