# coding: utf-8

from __future__ import absolute_import

from flask import json
from six import BytesIO

from swagger_server.models.curr_settings import CurrSettings  # noqa: E501
from swagger_server.models.int_value import IntValue  # noqa: E501
from swagger_server.models.scheduler import Scheduler  # noqa: E501
from swagger_server.test import BaseTestCase


class TestGetController(BaseTestCase):
    """GetController integration test stubs"""

    def test_get_brightness(self):
        """Test case for get_brightness

        Current brightness value
        """
        response = self.client.open(
            '/sedlacek/StockPanel/1.0.0/get/brightness',
            method='GET')
        self.assert200(response,
                       'Response body is : ' + response.data.decode('utf-8'))

    def test_get_scheduler(self):
        """Test case for get_scheduler

        Current scheduler settings
        """
        response = self.client.open(
            '/sedlacek/StockPanel/1.0.0/get/scheduler',
            method='GET')
        self.assert200(response,
                       'Response body is : ' + response.data.decode('utf-8'))

    def test_get_settings(self):
        """Test case for get_settings

        Current panel settings
        """
        response = self.client.open(
            '/sedlacek/StockPanel/1.0.0/get/settings',
            method='GET')
        self.assert200(response,
                       'Response body is : ' + response.data.decode('utf-8'))


if __name__ == '__main__':
    import unittest
    unittest.main()
